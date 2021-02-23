#pragma once
template <typename T>
class IObserver {
public:
	virtual void update(const T&) = 0;
};