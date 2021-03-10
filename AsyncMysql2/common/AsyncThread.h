#pragma once

#include <thread>
#include <functional>
#include "AsyncSemaphore.h"
#include <iostream>

class AsyncThread {
private:
	typedef function<void()> EventCall;
	EventCall _onRun;
	AsyncSemaphore _asyncSemaphore;
	mutex _mutex;
	thread* _pthread = nullptr;

	void OnWork() {
		if (_onRun) {
			_onRun();
		}
		cout << "thread notify start" << endl;
		_asyncSemaphore.Notify();
		cout << "thread notify end" << endl;
	}
public:
	AsyncThread() = default;

	virtual ~AsyncThread() {
		//Close();
	}

	void Start(EventCall onRun) {
		lock_guard<mutex> lock(_mutex);
		if (!_pthread && onRun) {
			_onRun = onRun;
			_pthread = new thread(&AsyncThread::OnWork, this);
		}
	}

	void Close() {
		lock_guard<mutex> lock(_mutex);
		if (_pthread) {
			cout << "thread wait start" << endl;
			_asyncSemaphore.Wait();
			cout << "thread wait end" << endl;
			_pthread->join();
			delete _pthread;
			_pthread = nullptr;
		}
	}

	void ExitInThread() {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_pthread) {
			_pthread->join();
			delete _pthread;
			_pthread = nullptr;
		}
	}
};
