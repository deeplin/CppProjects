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
		unsigned long* length = mysql_fetch_lengths(_pResult);
		for (int i = 0; i < fieldNum; i++) {
			AsyncData asyncData;
			asyncData._pData = row[i];
			asyncData._size = length[i];
			result.push_back(asyncData);
		}
		return result;
	}
	std::string AsyncMySql::GetInsertSql(std::map<std::string, AsyncData>& sqlMap, std::string tableName)
	{
		string result = "";
		if (sqlMap.empty() || tableName.empty()) {
			return result;
		}

		result = "INSERT INTO `" + tableName;

		string keys = "`(`";
		string values = "VALUES('";

		bool first = true;
		for (auto pair : sqlMap) {
			if (first) {
				first = false;
			}
			else {
				keys += ",`";
				values += ",'";
			}
			keys += pair.first + "`";
			values += pair.second._pData;
			values += "'";
		}
		keys += ")";
		values += ")";
		result += keys;
		result += values;
		return result;
	}
	bool AsyncMySql::Insert(std::map<std::string, AsyncData>& sqlMap, std::string tableName)
	{
		std::string sql = GetInsertSql(sqlMap, tableName);
		if (!Query(sql.c_str())) {
			return false;
		}
		if (mysql_affected_rows(_pMysql) <= 0) {
			return false;
		}
		return true;
	}
	bool AsyncMySql::InsertBinary(std::map<std::string, AsyncData>& sqlMap, std::string tableName)
	{
		string result = "";
		if (sqlMap.empty() || tableName.empty()) {
			return false;
		}

		result = "INSERT INTO `" + tableName;

		string keys = "`(`";
		string values = "VALUES(";

		MYSQL_BIND bind[MAX_FIELD] = { 0 };
		int fieldNum = 0;

		bool first = true;
		for (auto pair : sqlMap) {
			if (first) {
				first = false;
			}
			else {
				keys += ",`";
				values += ",";
			}
			keys += pair.first + "`";
			values += "?";

			bind[fieldNum].buffer = (char*) pair.second._pData;
			bind[fieldNum].buffer_length = pair.second._size;
			bind[fieldNum].buffer_type = (enum_field_types)pair.second._fieldType;
			fieldNum++;
		}
		keys += ")";
		values += ")";
		result += keys;
		result += values;

		MYSQL_STMT* stmt = mysql_stmt_init(_pMysql);
		if (!stmt) {
			AsyncLog::Error("Mysql init STMT failed. %s\n", mysql_error(_pMysql));
			return false;
		}

		if (mysql_stmt_prepare(stmt, result.c_str(), result.size())) {
			mysql_stmt_close(stmt);
			AsyncLog::Error("Mysql prepare STMT failed. %s\n", mysql_error(_pMysql));
			return false;
		}

		if (mysql_stmt_bind_param(stmt, bind) != 0) {
			mysql_stmt_close(stmt);
			AsyncLog::Error("Mysql bind STMT failed. %s\n", mysql_stmt_error(stmt));
			return false;
		}

		if (mysql_stmt_execute(stmt) != 0) {
			mysql_stmt_close(stmt);
			AsyncLog::Error("Mysql execute STMT failed. %s\n", mysql_stmt_error(stmt));
			return false;
		}

		mysql_stmt_close(stmt);
		return true;
	}
	std::string AsyncMySql::GetUpdateSql(std::map<std::string, AsyncData>& sqlMap, std::string tableName, std::string where)
	{
		string sql = "";
		if (sqlMap.empty() || tableName.empty()) {
			return sql;
		}

		sql = "UPDATE `" + tableName + "` SET ";

		bool first = true;
		for (auto pair : sqlMap) {
			if (first) {
				first = false;
			}
			else {
				sql += ",";
			}
			sql += "`" + pair.first + "`='" + pair.second._pData + "'";
		}
		if (!where.empty()) {
			sql += " WHERE " + where;
		}
		return sql;
	}
	int AsyncMySql::Update(std::map<std::string, AsyncData>& sqlMap, std::string tableName, std::string where)
	{
		string sql = GetUpdateSql(sqlMap, tableName, where);
		cout << sql << endl;
		if (!Query(sql.c_str())) {
			return -1;
		}
		return mysql_affected_rows(_pMysql);
	}
	int AsyncMySql::UpdateBinary(std::map<std::string, AsyncData>& sqlMap, std::string tableName, std::string where)
	{
		if (sqlMap.empty() || tableName.empty()) {
			return -1;
		}

		MYSQL_BIND bind[MAX_FIELD] = { 0 };
		int fieldNum = 0;

		string sql = "UPDATE `" + tableName + "` SET ";

		bool first = true;
		for (auto pair : sqlMap) {
			if (first) {
				first = false;
			}
			else {
				sql += ",";
			}
			sql += "`" + pair.first + "`=?";

			bind[fieldNum].buffer = (char*)pair.second._pData;
			bind[fieldNum].buffer_length = pair.second._size;
			bind[fieldNum].buffer_type = (enum_field_types)pair.second._fieldType;
			fieldNum++;
		}
		if (!where.empty()) {
			sql += " WHERE " + where;
		}

		MYSQL_STMT* stmt = mysql_stmt_init(_pMysql);
		if (!stmt) {
			AsyncLog::Error("Mysql init STMT failed. %s\n", mysql_error(_pMysql));
			return -1;
		}

		if (mysql_stmt_prepare(stmt, sql.c_str(), sql.size())) {
			mysql_stmt_close(stmt);
			AsyncLog::Error("Mysql prepare STMT failed. %s\n", mysql_error(_pMysql));
			return false;
		}

		if (mysql_stmt_bind_param(stmt, bind) != 0) {
			mysql_stmt_close(stmt);
			AsyncLog::Error("Mysql bind STMT failed. %s\n", mysql_stmt_error(stmt));
			return -1;
		}

		if (mysql_stmt_execute(stmt) != 0) {
			mysql_stmt_close(stmt);
			AsyncLog::Error("Mysql execute STMT failed. %s\n", mysql_stmt_error(stmt));
			return -1;
		}

		mysql_stmt_close(stmt);

		return mysql_stmt_affected_rows(stmt);
	}
}
