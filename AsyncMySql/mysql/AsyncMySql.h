#pragma once

#ifdef AsyncMySqlDll
#define ASYNCAPI __declspec(dllexport)
#else
#define ASYNCAPI __declspec(dllimport)
#endif

struct MYSQL;

class ASYNCAPI AsyncMySql
{
public:
	bool Init();

	void Close();

private:
	MYSQL* _pMysql = nullptr;
};