#pragma once

#include <mutex>
#include <assert.h>
#include "ObjectBlock.h"

template<typename T, size_t nPoolSize>
class ObjectPool {
private:
	ObjectBlock* _pHeader;
	char* _pBuf;
	std::mutex _mutex;
public:
	ObjectPool() {
	}
	~ObjectPool() {
	}

	void InitPool() {
		asset(nullptr == _pBuf);
		_pBuf = new char[nPoolSize*(sizeof(ObjectBlock) + sizeof(T)];
	}
};
