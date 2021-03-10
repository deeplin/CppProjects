#pragma once

#ifdef AsyncMySqlDll
#define ASYNCAPI __declspec(dllexport)
#else
#define ASYNCAPI __declspec(dllimport)
#endif

#include "AsyncMySqlOption.h"

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

	private:
		MYSQL* _pMysql = nullptr;
		MYSQL_RES* pResult = nullptr;
	};
}