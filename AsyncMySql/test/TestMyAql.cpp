#include <iostream>
#include "AsyncMySql.h"
#include "AsyncLog.h"

#include <iostream>
#include "AsyncDatah.h"

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

	sql = "select * from t_video";
	//sql = "insert into t_video(name) value('test')";
	int ret = mysql.Query(sql.c_str());
	cout << ret << endl;
	mysql.StoreResult();
	while (true) {
		vector<AsyncData> result = mysql.FetchRow();
		if (result.size() == 0) break;
		//for (int i = 0; i < result.size(); i++) {
		//	auto data = result[i].pData;
		//	cout << data << endl;
		//}

		for (auto iter = result.begin(); iter != result.end();iter++) {
			auto data = iter->pData;
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