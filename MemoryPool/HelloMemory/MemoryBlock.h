#pragma once
#include "BaseMemoryPool.h"

#ifdef _DEBUG
#include <stdio.h>
#define xPrintf(...) printf(__VA_ARGS__)
#else
#define xPrintf(...)
#endif

class BaseMemoryPool;

class MemoryBlock
{
public:
	BaseMemoryPool* _pMemoryPool;
	MemoryBlock* _pNext;
	int _nId;
	int _nRef;
	bool _bPool;
private:
	char _cNULL[3];
};