#include "MemoryAlloc.h"

void * MemoryAlloc::AllocMem(size_t nSize)
{
	MemoryBlock* pReturn = nullptr;
	if (nullptr == _pHeader) {
		pReturn = (MemoryBlock*) malloc(nSize + sizeof(MemoryBlock));
		pReturn->_bPool = false;
		pReturn->_nId = -1;
		pReturn->_pMemoryAlloc = nullptr;
		pReturn->_pNext = nullptr;
	}
	else {
		pReturn = _pHeader;
		assert(0 == pReturn->_nRef);
		_pHeader = pReturn->_pNext;
	}
	pReturn->_nRef = 1;
	xPrintf("AlloMem:%llx,id=%d,size=%d\n", pReturn, pReturn->_nId, nSize);
	return ((char*)pReturn) + sizeof(MemoryBlock);
}

void MemoryAlloc::FreeMem(void * pMem)
{
	MemoryBlock * pBlock = (MemoryBlock*) ((char*)pMem - sizeof(MemoryBlock));
	assert(1 == pBlock->_nRef);
	if (pBlock->_bPool) {
		pBlock->_nRef = 0;
		pBlock->_pNext = _pHeader;
		_pHeader = pBlock;
	}
	else {
		free(pBlock);
	}
}

void MemoryAlloc::InitMemory()
{
	assert(nullptr == _pBuf);
	size_t realSize = _nSize + sizeof(MemoryBlock);
	size_t bufSize = realSize * _nBlockSize;
	_pBuf = (char*)malloc(bufSize);
	_pHeader = (MemoryBlock*)_pBuf;
	_pHeader->_bPool = true;
	_pHeader->_nId = 0;
	_pHeader->_nRef = 0;
	_pHeader->_pMemoryAlloc = this;

	MemoryBlock* pCurrentBlock = _pHeader;
	for (int i = 0; i < _nBlockSize; i++)
	{
		MemoryBlock* pNextBlock = (MemoryBlock*)(_pBuf + realSize * i);
		pNextBlock->_bPool = true;
		pNextBlock->_nId = i;
		pNextBlock->_nRef = 0;
		pNextBlock->_pMemoryAlloc = this;
		pCurrentBlock->_pNext = pNextBlock;
		pNextBlock->_pNext = nullptr;
		pCurrentBlock = pNextBlock;
	}
}
