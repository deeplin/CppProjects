#include "AsyncMySql.h"
#include "AsyncLog.h"

void AsyncMySql::Init()
{
	AsyncLog::GetInstance().SetLogPath("AsyncMySqlDebug.txt", "w");
	AsyncLog::Info("test async debug");
}