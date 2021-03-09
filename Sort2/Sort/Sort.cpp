#include <list>
#include "Sort.h"

chrono::steady_clock::time_point _startTime;

void RandomData(int data[], int nLen) {
	default_random_engine random((uint32_t)time(NULL));
	for (int i = 0; i < nLen; i++) {
		uint32_t n = random();
		data[i] = n % 1000;
		//data[i] = 100 - i;
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
	if (nLen <= 100) {
		PrintData(data, nLen);
	}
}

void Swap(int& a, int&b) {
	int temp = a;
	a = b;
	b = temp;
}

void Sort(const char* name, int data[], int nLen, function<void(int*, int)> func) {
	StartClock(data, nLen);
	func(data, nLen);
	EndClock(name, data, nLen);
}

void BubleSort(int data[], int nLen) {
	for (bool sorted = false; sorted = !sorted; nLen--) {
		for (int i = 1; i < nLen; i++) {
			if (data[i - 1] > data[i]) {
				Swap(data[i - 1], data[i]);
				sorted = false;
			}
		}
	}
}

void BubleSortRecursive(int data[], int nLen) {
	if (nLen < 2) {
		return;
	}

	for (int i = 1; i < nLen; i++) {
		if (data[i - 1] > data[i]) {
			Swap(data[i - 1], data[i]);
		}
	}

	BubleSortRecursive(data, nLen - 1);
}

void SelectSort(int data[], int nLen) {
	for (int i = 0; i < nLen - 1; i++) {
		int minId = i;
		for (int j = i + 1; j < nLen; j++) {
			if (data[j] < data[minId]) {
				minId = j;
			}
		}
		if (minId != i) {
			Swap(data[minId], data[i]);
		}
	}
}

void SelectSortRecursive(int data[], int nLen) {
	if (nLen < 2) {
		return;
	}
	int maxId = nLen - 1;
	for (int i = 0; i < nLen - 1; i++) {
		if (data[maxId] < data[i]) {
			maxId = i;
		}
	}
	if (maxId != nLen - 1) {
		swap(data[maxId], data[nLen - 1]);
	}

	SelectSortRecursive(data, nLen - 1);
}

void InsertSort(int data[], int nLen)
{
	for (int i = 1; i < nLen; i++) {
		int num = data[i];
		int j = i - 1;
		while (j >= 0 && num < data[j]) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = num;
	}
}

void InsertSortRecursive(int data[], int nLen) {
	if (nLen < 2) {
		return;
	}
	InsertSortRecursive(data, nLen - 1);
	int num = data[nLen - 1];
	int j = nLen - 2;
	while (j >= 0 && num < data[j]) {
		data[j + 1] = data[j];
		j--;
	}
	data[j + 1] = num;
}

void ShellSort(int data[], int nLen)
{
	int step = nLen;
	do {
		step = step / 3 + 1;
		for (int start = 0; start < step; start++) {
			for (int i = start + step; i < nLen; i += step) {
				int num = data[i];
				int j = i - step;
				while (j >= 0 && num < data[j]) {
					data[j + step] = data[j];
					j -= step;
				}
				data[j + step] = num;
			}
		}
	} while (step > 1);
}

void QuickSort(int data[], int nLen) {
	QuickSortFunc(data, 0, nLen - 1);
}

void QuickSortFunc(int data[], int start, int end)
{
	if (start >= end) {
		return;
	}
	bool rightHand = true;
	int low = start;
	int high = end;
	int target = data[low];
	while (low < high) {
		if (rightHand) {
			if (data[high] < target) {
				data[low++] = data[high];
				rightHand = false;
			}
			else {
				high--;
			}
		}
		else {
			if (target < data[low]) {
				data[high--] = data[low];
				rightHand = true;
			}
			else {
				low++;
			}
		}
	}
	data[low] = target;
	QuickSortFunc(data, start, low - 1);
	QuickSortFunc(data, low + 1, end);
}

void MergeSort(int data[], int nLen)
{
	int* temp = new int[nLen];
	MergeSortRecursive(data, 0, nLen - 1, temp);
	delete[] temp;
}

void MergeSortRecursive(int data[], int start, int end, int temp[])
{
	if (start >= end) {
		return;
	}
	int mid = (start + end) / 2;
	MergeSortRecursive(data, start, mid, temp);
	MergeSortRecursive(data, mid + 1, end, temp);

	int lowStart = start;
	int lowEnd = mid;
	int highStart = mid + 1;
	int highEnd = end;

	int tempId = 0;
	while (lowStart <= lowEnd && highStart <= highEnd) {
		if (data[lowStart] < data[highStart]) {
			temp[tempId++] = data[lowStart++];
		}
		else {
			temp[tempId++] = data[highStart++];
		}
	}
	while (lowStart <= lowEnd) {
		temp[tempId++] = data[lowStart++];
	}
	while (highStart <= highEnd) {
		temp[tempId++] = data[highStart++];
	}

	memcpy(data + start, temp, sizeof(int) * tempId);
}

void AdjustHeap(int data[], int nLen, int nodeId) {
	int maxId = nodeId;
	int leftChildId = nodeId * 2 + 1;
	if (leftChildId < nLen && data[maxId] < data[leftChildId]) {
		maxId = leftChildId;
	}
	int rightChildId = nodeId * 2 + 2;
	if (rightChildId < nLen && data[maxId] < data[rightChildId]) {
		maxId = rightChildId;
	}
	if (maxId != nodeId) {
		Swap(data[maxId], data[nodeId]);
		AdjustHeap(data, nLen, maxId);
	}
}

void HeapSort(int data[], int nLen)
{
	for (int i = (nLen - 1) / 2; i >= 0; i--) {
		AdjustHeap(data, nLen, i);
	}

	for (int i = nLen - 1; i >= 0; i--) {
		swap(data[0], data[i]);
		AdjustHeap(data, i, 0);
	}
}

void RadixSortFunc(int data[], int nLen, list<int> buffer[], int radix) {
	for (int i = 0; i < nLen; i++) {
		int num = data[i];
		buffer[num / radix % 10].push_back(num);
	}

	int index = 0;
	for (int i = 0; i < 10; i++) {
		while (!buffer[i].empty()) {
			data[index++] = buffer[i].front();
			buffer[i].pop_front();
		}
	}
}

void RadixSort(int data[], int nLen)
{
	if (nLen <= 1) {
		return;
	}

	list<int> buffer[10];
	int max = data[0];
	for (int i = 0; i < nLen; i++) {
		if (data[i] > max) {
			max = data[i];
		}
	}

	for (int radix = 1; max / radix > 0; radix *= 10) {
		RadixSortFunc(data, nLen, buffer, radix);
	}
}
