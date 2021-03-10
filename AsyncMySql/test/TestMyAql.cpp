#include <iostream>
#include "AsyncMySql.h"
#include "AsyncLog.h"

#include <iostream>
#include "AsyncData.h"

using namespace Async;

int main()
{
	AsyncMySql mysql;
	mysql.Init();
	mysql.SetConnectionTimeout(3);
	mysql.SetReconnect();
	mysql.Connect("192.168.2.11", "root", "Deeplin-123456", "asyncDB");

	string sql = "CREATE TABLE IF NOT EXISTS `t_video` ( \
								`id` int AUTO_INCREMENT, \
								`name` varchar(1024), \
								`data` blob, \
								`size` int, \
								PRIMARY KEY(`id`))";

	sql = "TRUNCATE t_video";
	//sql = "insert into t_video(name) value('test')";

	map<string, AsyncData> sqlMap;
	AsyncData nameData("mysql.jpg");
	sqlMap["name"] = nameData;
	AsyncData dataData;
	dataData.LoadFile("mysql.jpg");
	sqlMap["data"] = dataData;
	AsyncData sizeData("1024");
	sqlMap["size"] = sizeData;

	int ret = mysql.Insert(sqlMap, "t_video");
	cout << ret << " insert: " << sql << endl;

	dataData.DeleteData();

	sql = "select * from t_video";
	ret = mysql.Query(sql.c_str());

	mysql.StoreResult();
	while (true) {
		vector<AsyncData> result = mysql.FetchRow();
		if (result.size() == 0) break;
		for (auto iter = result.begin(); iter != result.end();iter++) {
			auto data = iter->_pData;
			if (data) {
				cout << data << " " ;
			}
			else {
				cout << "NULL ";
			}
		}
		cout << endl;
	}
	mysql.FreeResult();

	//ret = mysql.Query(sql.c_str());
	//mysql.UseResult();
	//mysql.FreeResult();




	mysql.Close();
    std::cout << "Hello World!\n";
	getchar();
}