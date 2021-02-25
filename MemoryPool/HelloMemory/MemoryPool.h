#pragma once

#include "BaseMemoryPool.h"

template <size_t nSize, size_t nBlockSize>
class MemoryPool : public BaseMemoryPool
{
public:
	MemoryPool() {
		_nSize = nSize;
		_nPoolSize = nBlockSize;
		BaseMemoryPool::InitMemory();
	}
	~MemoryPool() = default;
};