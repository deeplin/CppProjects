#pragma once

#include <condition_variable>
#include <iostream>

using namespace std;

namespace Async {

	class AsyncSemaphore {
	private:
		mutex _mutex;
		condition_variable _cv;
		int _wait = 0;
		int _notify = 0;
	public:
		void Wait() {
			unique_lock <mutex> lock(_mutex);
			if (--_wait < 0) {
				cout << "wait start" << endl;
				_cv.wait(lock, [this]()->bool {return _notify > 0; });
				cout << "wait end" << endl;
				--_notify;
			}
		}

		void Notify() {
			unique_lock <mutex> lock(_mutex);
			if (++_wait <= 0) {
				++_notify;
				cout << "notify start" << endl;
				_cv.notify_one();
				cout << "notify end" << endl;
			}
		}
	};
}