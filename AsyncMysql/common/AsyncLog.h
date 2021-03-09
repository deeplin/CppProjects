#pragma once

#include <chrono>
#include "AsyncTaskServer.h"

using namespace std;
using namespace chrono;

class CellLog
{
private:
	AsyncTaskServer _asyncTaskServer;
	FILE* _logFile = nullptr;

	CellLog() {
		_asyncTaskServer.Start();
	}

	template<typename ...Args>
	static void WriteFile(const char* pFormat, Args ... args) {
		CellLog* log = &GetInstance();
		if (log->_logFile) {
			log->_asyncTaskServer.AddTask([=]() {
				auto t = system_clock::now();
				time_t rawTime = system_clock::to_time_t(t);

				struct tm now;
				gmtime_s(&now, &rawTime);
				fprintf(log->_logFile, "%s", "Info ");
				fprintf(log->_logFile, "[%d-%d-%d %d:%d:%d]", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
				fprintf(log->_logFile, pFormat, args...);
				fflush(log->_logFile);
				});
		}
	}
public:
	~CellLog() {
		_asyncTaskServer.CloseInThread();
		if (_logFile) {
			fflush(_logFile);
			fclose(_logFile);
			_logFile = nullptr;
		}
	}

	static CellLog& GetInstance() {
		static CellLog cellLog;
		return cellLog;
	}

	template<typename ...Args>
	static void Debug(const char* pFormat, Args ... args) {
		WriteFile(pFormat, args...);
		printf(pFormat, args...);
	}

	template<typename ...Args>
	static void Info(const char* pFormat, Args ... args) {
		WriteFile(pFormat, args...);
		printf(pFormat, args...);
	}

	template<typename ...Args>
	static void Warn(const char* pFormat, Args ... args) {
		WriteFile(pFormat, args...);
		printf(pFormat, args...);
	}

	template<typename ...Args>
	static void Error(const char* pFormat, Args ... args) {
		WriteFile(pFormat, args...);
		printf(pFormat, args...);
	}

	void SetLogPath(const char* pLogPath, const char* pMode) {
		if (_logFile) {
			fclose(_logFile);
		}
		int err = fopen_s(&_logFile, pLogPath, pMode);
		if (err) {
			printf("Open file error\n");
		}
	}
};