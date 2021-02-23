#include "Allocate.h"
#include "MemoryMgr.h"

void* operator new(size_t size) {
	return MemoryMgr::GetInstance().AllocMem(size);
}

void* operator new[](size_t size) {
	return MemoryMgr::GetInstance().AllocMem(size);
}

void operator delete(void* p) {
	return MemoryMgr::GetInstance().FreeMem(p);
}

void operator delete[](void* p) {
	return MemoryMgr::GetInstance().FreeMem(p);
}