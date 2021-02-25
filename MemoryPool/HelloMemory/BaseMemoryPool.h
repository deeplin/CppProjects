#pragma once

#include <assert.h>
#include <stdlib.h>
#include <mutex>
#include "MemoryBlock.h"

class MemoryBlock;

class BaseMemoryPool
{
protected:
	//�ڴ���С
	size_t _nSize;
	//�ڴ浥Ԫ����
	size_t _nPoolSize;
	//ͷ���ڴ�danyuan
	MemoryBlock* _pHeader;
	//�ڴ�ص�ַ
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