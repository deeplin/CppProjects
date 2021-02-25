#pragma once

#include "ObjectPool.h"

template <typename T, size_t nPoolSize>
class BaseObject {
private:
	static ObjectPool<T, nPoolSize>& GetObjectPool() {
		static ObjectPool<T, nPoolSize> objectPool;
		return objectPool;
	}
public:
	void* operator new(size_t nSize) {
		return GetObjectPool().AllocObj();
	}

	void operator delete(void *p) {
		GetObjectPool().FreeObj(p);
	}

	template<typename ...Args>
	static T* NewObj(Args ... args) {
		T* obj = new T(args...);
		return obj;
	}

	static void DeleteObject(T* obj) {
		delete obj;
	}
};