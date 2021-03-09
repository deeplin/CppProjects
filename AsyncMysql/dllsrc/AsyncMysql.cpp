#include "AsyncMysql.h"
#include "mysql.h"

#include <iostream>

using namespace std;

bool AsyncMysql::Init()
{
	mysql = mysql_init(0);
	if (!mysql) {

	}
	cout << "hello dll" << endl;
	return false;
}
