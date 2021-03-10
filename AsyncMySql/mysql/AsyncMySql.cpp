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

		if (!mysql_real_query(_pMysql, pSql, len)) {
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
}
