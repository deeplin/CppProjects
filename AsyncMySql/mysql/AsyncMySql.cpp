#include "AsyncMySql.h"
#include "AsyncLog.h"

#include "mysql.h"

bool AsyncMySql::Init()
{
	AsyncLog::GetInstance().SetLogPath("AsyncMySqlDebug.txt", "w");

	_pMysql = mysql_init(0);
	if (!_pMysql) {
		AsyncLog::Error("Init mysql failed\n");
		return false;
	}

	AsyncLog::Info("end async debug2\n");

	return true;
}

void AsyncMySql::Close()
{
	if (_pMysql) {
		mysql_close(_pMysql);
		_pMysql = nullptr;
	}
}