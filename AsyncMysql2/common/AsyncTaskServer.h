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
	bool _isRun = false;

	void OnRun() {
		cout << "run 1: " << endl;
		while (_isRun) {
			//if (!_taskBuf.empty()) {
			//	auto id = this_thread::get_id();
			//	cout << "lock start : " << id << " " << _tasks.empty() << endl;
			//	lock_guard<mutex> lockGuard(_mutex);
			//	cout << "lock end : " << id << " " << _tasks.empty() << endl;
			//	for (auto task : _taskBuf) {
			//		_tasks.push_back(task);
			//	}
			//	_taskBuf.clear();
			//}
			cout << "run 2 : "<< " " << _isRun << endl;
			//if (_tasks.empty()) {
			//	this_thread::sleep_for(chrono::milliseconds(1000));
			//	cout << "run continure " << " " << _tasks.empty() << endl;
			//	continue;
			//}
			this_thread::sleep_for(chrono::milliseconds(100));
			//for (auto task : _tasks) {
			//	task();
			//}
			//_tasks.clear();
		}
		//for (auto task : _taskBuf) {
		//	task();
		//}
		cout << "run 3: " << endl;
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
		_isRun = true;
		_asyncThread.Start([this]() {
			OnRun();
			});
	}

	void Close() {
		_isRun = false;
		_asyncThread.Close();
	}
};