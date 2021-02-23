#pragma once

#include "MemoryAlloc.h"

template <size_t nSize, size_t nBlockSize>
class MemoryAllocator : public MemoryAlloc
{
public:
	MemoryAllocator() {
		_nSize = nSize;
		_nBlockSize = nBlockSize;
		MemoryAlloc::InitMemory();
	}
	~MemoryAllocator() = default;
};