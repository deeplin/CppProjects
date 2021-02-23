#pragma once

#include <assert.h>
#include <stdlib.h>
#include "MemoryBlock.h"

class MemoryBlock;

class MemoryAlloc
{
protected:
	//�ڴ���С
	size_t _nSize;
	//�ڴ浥Ԫ����
	size_t _nBlockSize;
	//ͷ���ڴ�danyuan
	MemoryBlock* _pHeader;
	//�ڴ�ص�ַ
	char* _pBuf;
public:
	MemoryAlloc() :_pBuf(nullptr), _pHeader(nullptr), _nSize(0), _nBlockSize(0) {
	}

	virtual ~MemoryAlloc() {
		if (_pBuf) {
			free(_pBuf);
		}
	}

	void* AllocMem(size_t nSize);

	void FreeMem(void* p);

	void InitMemory();
};