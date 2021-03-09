#pragma once

#include <iostream>
#include <random>
#include <time.h>
#include <chrono>
#include <functional>

using namespace std;

void RandomData(int data[], int nLen);

void PrintData(int data[], int nLen);

void StartClock(int data[], int nLen);

void EndClock(const char* name, int data[], int nLen);

void Swap(int& a, int&b);

void Sort(const char* name, int data[], int nLen, function<void(int*, int)> func);

void BubleSort(int data[], int nLen);

void BubleSortRecursive(int data[], int nLen);

void SelectSort(int data[], int nLen);

void SelectSortRecursive(int data[], int nLen);

void InsertSort(int data[], int nLen);

void InsertSortRecursive(int data[], int nLen);

void ShellSort(int data[], int nLen);

void QuickSort(int data[], int nLen);

void QuickSortFunc(int data[], int start, int end);

void MergeSort(int data[], int nLen);

void MergeSortRecursive(int data[], int start, int end, int temp[]);

void AdjustHeap(int data[], int nLen, int nodeId);

void HeapSort(int data[], int nLen);

void RadixSort(int data[], int nLen);

