// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <random>
#include <sys/timeb.h>
#include <list>
#include <chrono>

using namespace std;

constexpr int MAX = 100000;

chrono::steady_clock::time_point start;

void randData(int a[], int num) {
	for (int i = 0; i < num; i++) {
		a[i] = rand() % 100;
		//a[i] = i;
	}
}

void initSort(int a[], int num) {
	randData(a, num);
	start = chrono::steady_clock::now();
}

void printData(int a[], int num) {
	for (int i = 0; i < num; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void endSort(const char* ch, int a[], int num) {
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	chrono::steady_clock::duration d = end - start;
	chrono::milliseconds md = chrono::duration_cast<chrono::milliseconds>(d);
	//chrono::seconds md = chrono::duration_cast<chrono::seconds>(d);
	cout << ch << " " << md.count() << endl;
	if (MAX <= 100)
		printData(a, num);
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void bubleSort2(int a[], int num) {
	initSort(a, num);
	for (bool sorted = false; sorted = !sorted; num--) {
		for (int j = 1; j < num; j++) {
			if (a[j - 1] > a[j]) {
				swap(a[j - 1], a[j]);
				sorted = false;
			}
		}
	}
	endSort("Buble Sort2", a, MAX);
}

void bubleSort4(int a[], int num) {
	initSort(a, num);
	while (num > 0) {
		int last = 0;
		int lo = 0;
		while (++lo < num) {
			if (a[lo - 1] > a[lo]) {
				last = lo;
				swap(a[lo - 1], a[lo]);
			}
		}
		num = last;
	}
	endSort("Bubble Sort4", a, MAX);
}

static void merge2(int a[], int start, int mid, int end, int temp[]) {
	int leftStart = start; int leftEnd = mid; int rightStart = mid + 1; int rightEnd = end;
	int index = 0;
	while (leftStart <= leftEnd && rightStart <= rightEnd) {
		if (a[leftStart] < a[rightStart]) {
			temp[index++] = a[leftStart++];
		}
		else {
			temp[index++] = a[rightStart++];
		}
	}

	while (leftStart <= leftEnd) {
		temp[index++] = a[leftStart++];
	}
	while (rightStart <= rightEnd) {
		temp[index++] = a[rightStart++];
	}
	memcpy(a + start, temp, index * sizeof(int));
}

static void merge3(int a[], int lo, int mi, int hi, int B[]) {
	int lb = mi - lo;
	int lc = hi - mi;
	int* A = a + lo;
	int* C = a + mi;
	memcpy(B, A, lb * sizeof(int));
	for (int i = 0, j = 0, k = 0; (j <= lb) || (k <= lc);) {
		if ((j <= lb) && (lc <= k || B[j] <= C[k])) {
			A[i++] = B[j++];
		}
		if ((k <= lc) && (lb <= j || C[k] <= B[j])) {
			A[i++] = C[k++];
		}
	}
	//printData(a, MAX);
}

static void mergeSort2(int a[], int start, int end, int temp[]) {
	if (start >= end) {
		return;
	}
	int mid = (start + end) >> 1;
	mergeSort2(a, start, mid, temp);
	mergeSort2(a, mid + 1, end, temp);
	merge2(a, start, mid, end, temp);
}

static void selectSort(int a[], int num) {
	initSort(a, num);
	for (int i = 0; i < num; i++) {
		int selectId = i;
		for (int j = i + 1; j < num; j++) {
			if (a[selectId] > a[j]) {
				selectId = j;
			}
		}
		if (i != selectId)
			swap(a[selectId], a[i]);
	}
	endSort("select sort*", a, num);
}

static void insertSort(int a[], int num) {
	initSort(a, num);
	for (int i = 1; i < num; i++) {
		int j = i - 1;
		int tmp = a[i];
		for (; j >= 0 && tmp < a[j]; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
	endSort("insert Sort", a, num);
}

static void shellSort(int a[], int num) {
	initSort(a, num);
	int increasement = num;
	do {
		increasement = increasement / 3 + 1;
		for (int i = 0; i < increasement; i++) {
			for (int j = i + increasement; j < num; j += increasement)
			{
				int tmp = a[j];
				int k = j - increasement;
				for (; k >= 0 && tmp < a[k]; k -= increasement) {
					a[k + increasement] = a[k];
				}
				a[k + increasement] = tmp;
			}
		}
	} while (increasement > 1);
	endSort("Shell Sort", a, num);
}

static void quickSort2(int a[], int low, int high) {
	if (low >= high) {
		return;
	}

	int lowId = low;
	int highId = high;
	bool backward = true;
	int tmp = a[lowId];
	while (lowId < highId) {
		if (backward) {
			if (a[highId] < tmp) {
				a[lowId++] = a[highId];
				backward = false;
			}
			else {
				highId--;
			}
		}
		else {
			if (tmp < a[lowId]) {
				a[highId--] = a[lowId];
				backward = true;
			}
			else {
				lowId++;
			}
		}
	}
	a[lowId] = tmp;
	quickSort2(a, low, lowId - 1);
	quickSort2(a, lowId + 1, high);
}

static void adjustHeap2(int a[], int index, int len) {
	int maxId = index;
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;
	if (leftChild < len && a[leftChild] > a[maxId]) {
		maxId = leftChild;
	}
	if (rightChild < len && a[rightChild] > a[maxId]) {
		maxId = rightChild;
	}
	if (maxId != index) {
		swap(a[maxId], a[index]);
		adjustHeap2(a, maxId, len);
	}
}

static void heapSort2(int a[], int len) {
	initSort(a, len);
	for (int i = len / 2; i >= 0; i--) {
		adjustHeap2(a, i, len);
	}
	for (int i = len - 1; i >= 0; i--) {
		swap(a[i], a[0]);
		adjustHeap2(a, 0, i);
	}
	endSort("Heap Sort", a, len);
}

static void bucketSort2(int a[], int len, int factor, list<int> b[]) {
	for (int k = 0; k < len; k++) {
		int value = a[k];
		int i = value / (factor) % 10;
		b[i].push_back(value);
	}

	int j = 0;
	for (int i = 0; i < 10; i++) {
		while (!b[i].empty()) {
			a[j++] = b[i].front();
			b[i].pop_front();
		}
	}
}

static void bucketSort(int a[], int len) {
	list<int> lists[10];
	initSort(a, len);
	for (int i = 1; i <= len; i *= 10) {
		bucketSort2(a, len, i, lists);
	}

	endSort("Radio Sort2", a, len);
}

int main()
{
	srand(time(NULL));

	int* a = new int[MAX];

	//bubleSort2(a, MAX);//49.7     //MAX = 100000

	//bubleSort4(a, MAX);//49.6

	initSort(a, MAX); //0.01
	int* temp = new int[MAX];
	mergeSort2(a, 0, MAX - 1, temp);
	endSort("Merge Sort", a, MAX);

	//selectSort(a, MAX);//7.9

	insertSort(a, MAX);//3.9

	shellSort(a, MAX);//0.009

	initSort(a, MAX);
	quickSort2(a, 0, MAX - 1); //0.068
	endSort("Quick Sort", a, MAX);

	heapSort2(a, MAX);// 0.048

	bucketSort(a, MAX);

	delete[] temp;
	delete[] a;
	std::cout << "Hello World!\n";
}