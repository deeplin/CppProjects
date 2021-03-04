#include "Sort.h"

chrono::steady_clock::time_point _startTime;

void RandomData(int data[], int nLen) {
	default_random_engine random((uint32_t)time(NULL));
	for (int i = 0; i < nLen; i++) {
		data[i] = random() % 100;
	}
}

void PrintData(int data[], int nLen) {
	for (int i = 0; i < nLen; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
}

void StartClock(int data[], int nLen) {
	RandomData(data, nLen);
	_startTime = chrono::steady_clock::now();
}

void EndClock(const char* name, int data[], int nLen) {
	chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
	chrono::steady_clock::duration eclapse = endTime - _startTime;
	chrono::milliseconds milliTime = chrono::duration_cast<chrono::milliseconds>(eclapse);

	cout << name << " " << milliTime.count() << endl;
	if (MAX <= 100) {
		PrintData(data, nLen);
	}
}

void Swap(int& a, int&b) {
	int temp = a;
	a = b;
	b = temp;
}

void BubleSort(int data[], int nLen) {
	StartClock(data, MAX);
	for (bool sorted = false; sorted = !sorted; nLen--) {
		for (int i = 1; i < nLen; i++) {
			if (data[i - 1] > data[i]) {
				Swap(data[i - 1], data[i]);
				sorted = false;
			}
		}
	}
	EndClock("Buble", data, MAX);
}
