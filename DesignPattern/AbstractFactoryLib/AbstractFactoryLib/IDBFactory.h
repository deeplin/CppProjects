#pragma once
#include "IConnection.h"
#include "ICommand.h"
#include "IReader.h"

class IDBFactory
{
public:
	virtual IConnection* createConnection() = 0;
	virtual ICommand* createCommand() = 0;
	virtual IReader* createReader() = 0;
};

