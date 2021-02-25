#pragma once

template <typename T>
class BaseObject {
public:
	template<typename ...Args>
	static T* NewObj(Args ... args) {
		T* obj = new T(args...);
		return obj;
	}

	static void DeleteObject(T* obj) {
		delete obj;
	}
};