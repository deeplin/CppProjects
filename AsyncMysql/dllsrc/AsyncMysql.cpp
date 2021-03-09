#include "AsyncMysql.h"
#include "mysql.h"
#include "AsyncLog.h"

using namespace std;

bool AsyncMysql::Init()
{
	CellLog::GetInstance().SetLogPath("AsyncMysqlDebug.txt", "w");
	CellLog::Info("hello test");
	mysql = mysql_init(0);
	if (!mysql) {

	}
	return false;
}
