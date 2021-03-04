#pragma once

#include <iostream>
#include <random>
#include <time.h>
#include <chrono>

using namespace std;

constexpr auto MAX = 100;

void RandomData(int data[], int nLen);

void PrintData(int data[], int nLen);

void StartClock(int data[], int nLen);

void EndClock(const char* name, int data[], int nLen);

void Swap(int& a, int&b);

void BubleSort(int data[], int nLen);
