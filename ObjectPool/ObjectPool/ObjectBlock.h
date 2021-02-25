#pragma once

class ObjectBlock
{
public:
	ObjectBlock* _pNext;
	int _nId;
	bool _bPool;
	char _nRef;
private:
	char _cNULL[2];
};