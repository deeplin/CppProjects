#pragma once

struct MYSQL;

class __declspec(dllexport) AsyncMysql {
public:
	bool Init();

protected:
	MYSQL* mysql = nullptr;
};
