#pragma once

#include <vector>
#include <string>
#include <map>
#include "AsyncMySqlOption.h"
#include "AsyncData.h"

constexpr auto MAX_FIELD = 10;

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

		std::string GetUpdateSql(std::map<std::string, AsyncData>& sqlMap, std::string tableName, std::string where);

		//返回更新数量，错误返回-1
		int Update(std::map<std::string, AsyncData>& sqlMap, std::string tableName, std::string where);

		int UpdateBinary(std::map<std::string, AsyncData>& sqlMap, std::string tableName, std::string where);

		//事务接口
		bool StartTransaction();
		bool StopTransaction();
		bool Commmit();
		bool Roolback();

	private:
		MYSQL* _pMysql = nullptr;
		MYSQL_RES* _pResult = nullptr;
	};
}