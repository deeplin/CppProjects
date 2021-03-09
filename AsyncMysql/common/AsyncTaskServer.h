#pragma once
using namespace std;

#include <list>
#include <functional>
#include "AsyncThread.h"

class AsyncTaskServer {
	typedef function<void()> CellTask;
private:
	list<CellTask> _tasks;
	list<CellTask> _taskBuf;
	mutex _mutex;
	AsyncThread _asyncThread;

	void OnRun(AsyncThread* cellThread) {
		while (cellThread->IsRun()) {
			if (!_taskBuf.empty()) {
				lock_guard<mutex> lockGuard(_mutex);
				for (auto task : _taskBuf) {
					_tasks.push_back(task);
				}
				_taskBuf.clear();
			}
			if (_tasks.empty()) {
				this_thread::sleep_for(chrono::milliseconds(1));
				continue;
			}
			for (auto task : _tasks) {
				task();
			}
			_tasks.clear();
		}
		for (auto task : _taskBuf) {
			task();
		}
	}
public:
	AsyncTaskServer() {
	}

	~AsyncTaskServer() {
		Close();
	}

	void AddTask(CellTask cellTask) {
		lock_guard<mutex> lockGuard(_mutex);
		_taskBuf.push_back(cellTask);
	}

	void Start() {
		_asyncThread.Start([this](AsyncThread* cellThread) {
			OnRun(cellThread);
			});
	}

	void Close() {
		_asyncThread.Close();
	}

	void CloseInThread() {
		_asyncThread.ExitInThread();
	}
};