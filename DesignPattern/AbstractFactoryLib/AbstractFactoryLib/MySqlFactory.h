#pragma once
#include "IDBFactory.h"
#include "MySqlConnection.h"
#include "MySqlReader.h"
#include "MySqlCommand.h"

class MySqlFactory :
    public IDBFactory
{
public:
	virtual IConnection* createConnection() {
		return new MySqlConnection();
	}

	virtual ICommand* createCommand() {
		return new MySqlCommand();
	}
	virtual IReader* createReader() {
		return new MySqlReader();
	}
};

