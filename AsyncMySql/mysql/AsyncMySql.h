#pragma once
#include "AsyncLog.h"

class AsyncMySql
{
public:
	void Init() {
		AsyncLog::GetInstance().SetLogPath("AsyncMySqlDebug.txt", "w");
		AsyncLog::Info("test async debug");
	}
};