#pragma once

#include <chrono>

using namespace std::chrono;

class TimeStamp {
public:
	TimeStamp() {
		Update();
	}

	virtual ~TimeStamp() {
	}

	void Update() {
		_begin = high_resolution_clock::now();
	}

	double GetElapsedSecond() {
		return GetElapsedTimeInMicroSec() / 1000000.0;
	}

	double GetElapsedTimeInMilliSec() {
		return GetElapsedTimeInMicroSec() / 1000.0;
	}

	long long GetElapsedTimeInMicroSec() {
		return duration_cast<microseconds>(high_resolution_clock::now() - _begin).count();
	}
private:
	time_point<high_resolution_clock> _begin;
};