#pragma once

#include <assert.h>
#include <stdlib.h>
#include <mutex>
#include "MemoryBlock.h"

class MemoryBlock;

class BaseMemoryPool
{
protected:
	//内存块大小
	size_t _nSize;
	//内存单元数量
	size_t _nPoolSize;
	//头部内存danyuan
	MemoryBlock* _pHeader;
	//内存池地址
	char* _pBuf;
	std::mutex _mutex;
public:
	BaseMemoryPool() :_pBuf(nullptr), _pHeader(nullptr), _nSize(0), _nPoolSize(0) {
	}

	~BaseMemoryPool() {
		if (_pBuf) {
			free(_pBuf);
		}
	}

	void* AllocMem(size_t nSize);

	void FreeMem(void* p);

	void InitMemory();
};