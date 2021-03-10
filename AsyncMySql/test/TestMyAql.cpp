#include <iostream>
#include "AsyncMySql.h"
#include "AsyncLog.h"

#include <iostream>

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
	while (true) {
		int ret = mysql.Query(sql.c_str());
		cout << ret << " ";
		mysql.StoreResult();
		mysql.FreeResult();
			this_thread::sleep_for(chrono::milliseconds(1000));
	}

	//ret = mysql.Query(sql.c_str());
	//mysql.UseResult();
	//mysql.FreeResult();

	//while (true) {

	//	int ret = mysql.Query(sql.c_str());

	//	cout << ret << endl;
	//}


	mysql.Close();
    std::cout << "Hello World!\n";
	getchar();
}