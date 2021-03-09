#pragma once

#include <thread>
#include <functional>
#include "AsyncSemaphore.h"

class AsyncThread {
private:
	typedef function<void(AsyncThread*)> EventCall;
	EventCall _onRun;
	AsyncSemaphore _asyncSemaphore;
	mutex _mutex;
	bool _isRun = false;

	void OnWork() {
		if (_onRun) {
			_onRun(this);
		}
		_asyncSemaphore.Notify();
	}
protected:

public:
	AsyncThread() = default;

	virtual ~AsyncThread() {
		Close();
	}

	void Start(EventCall onRun) {
		lock_guard<mutex> lock(_mutex);
		if (!_isRun) {
			_isRun = true;

			_onRun = onRun;

			thread t(&AsyncThread::OnWork, this);
			t.detach();
		}
	}

	void Close() {
		lock_guard<mutex> lock(_mutex);
		if (_isRun) {
			_isRun = false;
			_asyncSemaphore.Wait();
		}
	}

	void ExitInThread() {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_isRun) {
			_isRun = false;
		}
	}

	bool IsRun() {
		return _isRun;
	}
};
