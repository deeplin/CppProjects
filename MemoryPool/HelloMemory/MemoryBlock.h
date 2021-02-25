#pragma once
#include "BaseMemoryPool.h"

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