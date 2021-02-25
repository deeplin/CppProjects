#pragma once
#include "MemoryAlloc.h"

#ifdef _DEBUG
#include <stdio.h>
#define xPrintf(...) printf(__VA_ARGS__)
#else
#define xPrintf(...)
#endif

class MemoryAlloc;

class MemoryBlock
{
public:
	MemoryAlloc* _pMemoryAlloc;
	MemoryBlock* _pNext;
	int _nId;
	int _nRef;
	bool _bPool;
private:
	char _cNULL[3];
};