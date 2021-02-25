#pragma once

#include <mutex>
#include <assert.h>
#include "ObjectBlock.h"

#ifdef _DEBUG
	#ifndef xPrintf
	#include <stdio.h>
	#define xPrintf(...) printf(__VA_ARGS__)
	#endif
#else
	#ifndef xPrintf
	#define xPrintf(...)
	#endif
#endif

template<typename T, size_t nPoolSize>
class ObjectPool {
private:
	ObjectBlock* _pHeader;
	char* _pBuf;
	std::mutex _mutex;

	void InitPool() {
		assert(nullptr == _pBuf);
		size_t realSize = sizeof(ObjectBlock) + sizeof(T);
		size_t bufSize = realSize * nPoolSize;
		_pBuf = (char*)new char[bufSize];
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
public:
	ObjectPool() {
		InitPool();
	}
	~ObjectPool() {
		if (_pBuf) {
			delete[] _pBuf;
		}
	}

	void* AllocObj() {
		std::lock_guard < std::mutex > lockGuard(_mutex);
		ObjectBlock* pReturn = nullptr;
		if (nullptr == _pHeader) {
			pReturn = (ObjectBlock*) new char[sizeof(ObjectBlock) + sizeof(T)];
			pReturn->_bPool = false;
			pReturn->_nId = -1;
			pReturn->_pNext = nullptr;
		}
		else {
			pReturn = _pHeader;
			assert(0 == pReturn->_nRef);
			_pHeader = pReturn->_pNext;
		}
		pReturn->_nRef = 1;
		//xPrintf("AlloMem:%llx,id=%d,size=%d\n", pReturn, pReturn->_nId, sizeof(T));
		return ((char*)pReturn) + sizeof(ObjectBlock);
	}

	void FreeObj(void * pMem) {
		ObjectBlock * pBlock = (ObjectBlock*)((char*)pMem - sizeof(ObjectBlock));
		assert(1 == pBlock->_nRef);

		if (pBlock->_bPool) {
			std::lock_guard<std::mutex> lockGuard(_mutex);
			pBlock->_nRef = 0;
			pBlock->_pNext = _pHeader;
			_pHeader = pBlock;
		}
		else {
			delete[] pBlock;
		}
	}
};
