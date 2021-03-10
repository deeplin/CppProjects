#pragma once
#include <chrono>

#include "AsyncTaskServer.h"

using namespace chrono;

class __declspec(dllexport) AsyncLog
{
private:
	AsyncTaskServer _taskServer;
	FILE* _logFile = nullptr;

	AsyncLog() {
		_taskServer.Start();
	}

	template<typename ...Args>
	static void WriteFile(const char* pLevel, const char* pFormat, Args ... args) {
		AsyncLog* log = &GetInstance();
		if (log->_logFile) {
			log->_taskServer.AddTask([=]() {
				auto t = system_clock::now();
				time_t rawTime = system_clock::to_time_t(t);

				struct tm now;
				gmtime_s(&now, &rawTime);
				fprintf(log->_logFile, "%s", pLevel);
				fprintf(log->_logFile, "[%d-%d-%d %d:%d:%d]", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
				fprintf(log->_logFile, pFormat, args...);
				fflush(log->_logFile);
				});
		}
	}
public:
	~AsyncLog() {
		_taskServer.Close();
		if (_logFile) {
			fflush(_logFile);
			fclose(_logFile);
			_logFile = nullptr;
		}
	}

	static AsyncLog& GetInstance() {
		static AsyncLog asyncLog;
		return asyncLog;
	}

	template<typename ...Args>
	static void Debug(const char* pFormat, Args ... args) {
		WriteFile("Debug", pFormat, args...);
		printf(pFormat, args...);
	}

	template<typename ...Args>
	static void Info(const char* pFormat, Args ... args) {
		WriteFile("Info", pFormat, args...);
		printf(pFormat, args...);
	}

	template<typename ...Args>
	static void Warn(const char* pFormat, Args ... args) {
		WriteFile("Warn", pFormat, args...);
		printf(pFormat, args...);
	}

	template<typename ...Args>
	static void Error(const char* pFormat, Args ... args) {
		WriteFile("Error", pFormat, args...);
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