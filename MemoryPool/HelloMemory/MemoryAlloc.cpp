#include "BaseMemoryPool.h"

void * BaseMemoryPool::AllocMem(size_t nSize)
{
	std::lock_guard < std::mutex > lockGuard(_mutex);
	MemoryBlock* pReturn = nullptr;
	if (nullptr == _pHeader) {
		pReturn = (MemoryBlock*) malloc(nSize + sizeof(MemoryBlock));
		pReturn->_bPool = false;
		pReturn->_nId = -1;
		pReturn->_pMemoryPool = nullptr;
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

void BaseMemoryPool::FreeMem(void * pMem)
{
	MemoryBlock * pBlock = (MemoryBlock*) ((char*)pMem - sizeof(MemoryBlock));
	assert(1 == pBlock->_nRef);

	if (pBlock->_bPool) {
		std::lock_guard<std::mutex> lockGuard(_mutex);
		pBlock->_nRef = 0;
		pBlock->_pNext = _pHeader;
		_pHeader = pBlock;
	}
	else {
		free(pBlock);
	}
}

void BaseMemoryPool::InitMemory()
{
	assert(nullptr == _pBuf);
	size_t realSize = _nSize + sizeof(MemoryBlock);
	size_t bufSize = realSize * _nPoolSize;
	_pBuf = (char*)malloc(bufSize);
	_pHeader = (MemoryBlock*)_pBuf;
	_pHeader->_bPool = true;
	_pHeader->_nId = 0;
	_pHeader->_nRef = 0;
	_pHeader->_pMemoryPool = this;
	_pHeader->_pNext = nullptr;
	MemoryBlock* pCurrentBlock = _pHeader;
	for (int i = 1; i < _nPoolSize; i++)
	{
		MemoryBlock* pNextBlock = (MemoryBlock*)(_pBuf + realSize * i);
		pNextBlock->_bPool = true;
		pNextBlock->_nId = i;
		pNextBlock->_nRef = 0;
		pNextBlock->_pMemoryPool = this;
		pCurrentBlock->_pNext = pNextBlock;
		pNextBlock->_pNext = nullptr;
		pCurrentBlock = pNextBlock;
	}
}
