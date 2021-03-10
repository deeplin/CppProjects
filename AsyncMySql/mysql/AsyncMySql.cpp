#include "AsyncMySql.h"
#include "AsyncLog.h"

#include "mysql.h"

namespace Async {

	bool AsyncMySql::Init()
	{
		AsyncLog::GetInstance().SetLogPath("AsyncMySqlDebug.txt", "w");

		Close();

		_pMysql = mysql_init(0);
		if (!_pMysql) {
			AsyncLog::Error("Mysql init failed\n");
			return false;
		}
		return true;
	}

	void AsyncMySql::Close()
	{
		FreeResult();
		if (_pMysql) {
			mysql_close(_pMysql);
			_pMysql = nullptr;
		}
	}

	bool AsyncMySql::Connect(const char* pHost, const char* pUser, const char* pPassword, const char* pDb,
		unsigned int port, unsigned long flag)
	{
		if (!mysql_real_connect(_pMysql, pHost, pUser, pPassword, pDb, port, nullptr, flag)) {
			AsyncLog::Error("Mysql connection failed. %s\n", mysql_error(_pMysql));
			return false;
		}
		AsyncLog::Info("Mysql connection succeed.\n");
		return true;
	}

	bool AsyncMySql::Query(const char* pSql, unsigned long len)
	{
		if (!pSql) {
			AsyncLog::Error("Mysql sql string is null.\n");
			return false;
		}
		if (len <= 0) {
			len = (unsigned long)strlen(pSql);
		}

		if (mysql_real_query(_pMysql, pSql, len)) {
			AsyncLog::Error("Mysql query failed. %s\n", mysql_error(_pMysql));
			return false;
		}
		return true;
	}

	bool AsyncMySql::Options(AsyncMysqlOption option, const void* arg)
	{
		if (mysql_options(_pMysql, (mysql_option)option, arg)) {
			AsyncLog::Error("Mysql option failed. %s\n", mysql_error(_pMysql));
			return false;
		}
		return true;
	}

	bool AsyncMySql::SetConnectionTimeout(int second)
	{
		return Options(AsyncMysqlOption::MYSQL_OPT_CONNECT_TIMEOUT, &second);
	}

	bool AsyncMySql::SetReconnect(bool isReconnect)
	{
		return Options(AsyncMysqlOption::MYSQL_OPT_RECONNECT, &isReconnect);
	}
	bool AsyncMySql::StoreResult()
	{
		FreeResult();
		_pResult = mysql_store_result(_pMysql);
		if (!_pResult) {
			AsyncLog::Error("Mysql store result failed. %s\n", mysql_error(_pMysql));
			return false;
		}
		return true;
	}
	bool AsyncMySql::UseResult()
	{
		FreeResult();
		_pResult = mysql_use_result(_pMysql);
		if (!_pResult) {
			AsyncLog::Error("Mysql use result failed. %s\n", mysql_error(_pMysql));
			return false;
		}
		return true;
	}
	void AsyncMySql::FreeResult()
	{
		if (_pResult) {
			mysql_free_result(_pResult);
			_pResult = nullptr;
		}
	}
	std::vector<AsyncData> AsyncMySql::FetchRow()
	{
		std::vector<AsyncData> result;
		if (!_pResult) {
			return result;
		}
		MYSQL_ROW row = mysql_fetch_row(_pResult);
		if (!row) {
			return result;
		}

		int fieldNum = mysql_num_fields(_pResult);
		for (int i = 0; i < fieldNum; i++) {
			AsyncData asyncData;
			asyncData.pData = row[i];
			result.push_back(asyncData);
		}
		return result;
	}
}
