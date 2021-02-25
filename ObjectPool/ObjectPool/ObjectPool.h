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
		assert(nullptr == _pBuf);
		size_t realSize = sizeof(ObjectBlock) + sizeof(T);
		size_t bufSize = realSize * nPoolSize;
		_pBuf = (char*)malloc(bufSize);
		_pHeader = (ObjectBlock*)_pBuf;
		_pHeader->_bPool = true;
		_pHeader->_nId = 0;
		_pHeader->_nRef = 0;
		_pHeader->_pNext = nullptr;
		ObjectBlock* pCurrentBlock = _pHeader;
		for (int i = 1; i < nPoolSize; i++)
		{
			ObjectBlock* pNextBlock = (ObjectBlock*)(_pBuf + realSize * i);
			pNextBlock->_bPool = true;
			pNextBlock->_nId = i;
			pNextBlock->_nRef = 0;
			pCurrentBlock->_pNext = pNextBlock;
			pNextBlock->_pNext = nullptr;
			pCurrentBlock = pNextBlock;
		}
	}
};
