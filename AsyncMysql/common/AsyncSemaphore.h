#pragma once

#include <condition_variable>

using namespace std;

class AsyncSemaphore {
public:
	void Wait() {
		unique_lock <mutex> lock(_mutex);
		if (--_wait < 0) {
			_cv.wait(lock, [this]()->bool {return _notify > 0; });
			--_notify;
		}
	}

	void Notify() {
		unique_lock <mutex> lock(_mutex);
		if (++_wait <= 0) {
			++_notify;
			_cv.notify_one();
		}
	}

private:
	mutex _mutex;
	condition_variable _cv;
	int _wait = 0;
	int _notify = 0;
};