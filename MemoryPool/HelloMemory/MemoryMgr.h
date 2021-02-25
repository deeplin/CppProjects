#pragma once

#include <stdlib.h>
#include "MemoryPool.h"

#define MAX_MEMORY_SIZE 128

class MemoryMgr {
private:
	MemoryMgr() {
		Init(0, 64, &_mem64);
		Init(65, 128, &_mem128);
		//Init(129, 256, &_mem256);
		//Init(257, 512, &_mem512);
		//Init(513, 1024, &_mem1024);
	}
	MemoryMgr(const MemoryMgr&) = delete;
	MemoryMgr& operator=(MemoryMgr&) = delete;

	MemoryPool<64, 10000> _mem64;
	MemoryPool<128, 10000> _mem128;
	//MemoryPool<256, 100> _mem256;
	//MemoryPool<512, 100> _mem512;
	//MemoryPool<1024, 100> _mem1024;

	BaseMemoryPool* _allocArray[MAX_MEMORY_SIZE + 1];

	void Init(int nBegin, int nEnd, BaseMemoryPool* pMemAlloc) {
		for (size_t i = nBegin; i <= nEnd; i++)
		{
			_allocArray[i] = pMemAlloc;
		}
	}
public:
	static MemoryMgr& GetInstance() {
		static MemoryMgr _instance;
		return _instance;
	}

	~MemoryMgr() = default;

	void* AllocMem(size_t nSize) {
		if (nSize <= MAX_MEMORY_SIZE) {
			return _allocArray[nSize]->AllocMem(nSize);
		}
		else {
			MemoryBlock* pReturn = (MemoryBlock*)malloc(nSize + sizeof(MemoryBlock));
			pReturn->_bPool = false;
			pReturn->_nId = -1;
			pReturn->_nRef = 1;
			pReturn->_pMemoryPool = nullptr;
			pReturn->_pNext = nullptr;
			xPrintf("AlloMem:%llx,id=%d,size=%d\n", pReturn, pReturn->_nId, nSize);
			return (char*)pReturn + sizeof(MemoryBlock);
		}
	}

	void FreeMem(void* pMem) {
		MemoryBlock * pBlock = (MemoryBlock*)((char*)pMem - sizeof(MemoryBlock));
		xPrintf("FreeMem:%llx,id=%d\n", pBlock, pBlock->_nId);
		assert(1 == pBlock->_nRef);
		if (pBlock->_bPool) {
			pBlock->_pMemoryPool->FreeMem(pMem);
		}
		else {
			free(pBlock);
		}
	}
};