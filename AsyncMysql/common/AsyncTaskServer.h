#pragma once
#include <list>
#include <functional>
#include "AsyncThread.h"
#include <iostream>

using namespace std;

namespace Async {

	class AsyncTaskServer {
		typedef function<void()> AsyncTask;
	private:
		list<AsyncTask> _tasks;
		list<AsyncTask> _taskBuf;
		mutex _mutex;
		AsyncThread _thread;

		void OnRun(AsyncThread* asyncThread) {
			cout << "run 1" << endl;
			while (asyncThread->IsRun()) {
				if (!_taskBuf.empty()) {
					lock_guard<mutex> lockGuard(_mutex);
					for (auto task : _taskBuf) {
						_tasks.push_back(task);
					}
					_taskBuf.clear();
				}
				cout << ".";
				if (_tasks.empty()) {
					this_thread::sleep_for(chrono::milliseconds(1000));
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
			cout << "run 3" << endl;
		}
	public:
		AsyncTaskServer() = default;

		~AsyncTaskServer() = default;

		void AddTask(AsyncTask asyncTask) {
			lock_guard<mutex> lockGuard(_mutex);
			_taskBuf.push_back(asyncTask);
		}

		void Start() {
			_thread.Start([this](AsyncThread* pThread) {
				OnRun(pThread);
				});
		}

		void Close() {
			_thread.Close();
		}
	};
}