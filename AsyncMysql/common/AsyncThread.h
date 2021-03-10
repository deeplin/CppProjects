#pragma once

#include <thread>
#include <functional>
#include "AsyncSemaphore.h"

class AsyncThread {
private:
	typedef function<void(AsyncThread*)> EventCall;
	EventCall _onRun;
	EventCall _onStart;
	EventCall _onClose;
	AsyncSemaphore _semaphore;
	mutex _mutex;
	bool _isRun = false;

	void OnWork() {
		if (_onStart) {
			_onStart(this);
		}
		if (_onRun) {
			_onRun(this);
		}
		if (_onClose) {
			_onClose(this);
		}
		_semaphore.Notify();
	}
protected:

public:
	AsyncThread() = default;

	virtual ~AsyncThread() {
		Close();
	}

	void Start(EventCall onRun, EventCall onStart = nullptr, EventCall onClose = nullptr) {
		lock_guard<mutex> lock(_mutex);
		if (!_isRun) {
			_isRun = true;

			_onRun = onRun;
			_onStart = onStart;
			_onClose = onClose;

			thread t(&AsyncThread::OnWork, this);
			t.detach();
		}
	}

	void Close() {
		lock_guard<mutex> lock(_mutex);
		if (_isRun) {
			_isRun = false;
			//todo
			//_semaphore.Wait();
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