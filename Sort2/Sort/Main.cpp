// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Sort.h"

constexpr auto MAX = 100;

int main()
{
	int data[MAX];

	Sort("Buble", data, MAX, BubleSort);

	Sort("Buble Recursive", data, MAX, BubleSortRecursive);

	Sort("Select", data, MAX, SelectSort);

	Sort("Select Recursive", data, MAX, SelectSortRecursive);

	Sort("Insert", data, MAX, InsertSort);

	Sort("Insert Recursive", data, MAX, InsertSortRecursive);

	Sort("Shell", data, MAX, ShellSort);

	Sort("Quick", data, MAX, QuickSort);

	Sort("Merge", data, MAX, MergeSort);

	Sort("Heap", data, MAX, HeapSort);

	Sort("Radix", data, MAX, RadixSort);

    std::cout << "Hello World!\n";
}