#pragma once

#include <vector>
#include <string>
#include <map>
#include "AsyncMySqlOption.h"
#include "AsyncData.h"

struct MYSQL;
struct MYSQL_RES;

namespace Async {

	class ASYNCAPI AsyncMySql
	{
	public:
		bool Init();

		void Close();

		bool Connect(const char* pHost, const char* pUser, const char* pPassword, const char* pDb,
			unsigned int port = 3306, unsigned long flag = 0);

		bool Query(const char* pSql, unsigned long len = 0);

		bool Options(AsyncMysqlOption option, const void* arg);

		bool SetConnectionTimeout(int second);

		bool SetReconnect(bool isReconnect = true);

		bool StoreResult();

		bool UseResult();

		void FreeResult();

		std::vector<AsyncData> FetchRow();

		std::string GetInsertSql(std::map<std::string, AsyncData>& sqlMap, std::string tableName);

		bool Insert(std::map<std::string, AsyncData>& sqlMap, std::string tableName);

		bool InsertBinary(std::map<std::string, AsyncData>& sqlMap, std::string tableName);

	private:
		MYSQL* _pMysql = nullptr;
		MYSQL_RES* _pResult = nullptr;
	};
}