#include "AsyncData.h"
#include "AsyncLog.h"
#include <fstream>

using namespace std;

bool Async::AsyncData::LoadFile(const char* filename)
{
	fstream in(filename, ios::in | ios::binary);
	if (!in.is_open()) {
		AsyncLog::Error("Mysql open file failed. %s\n", filename);
		return false;
	}

	in.seekg(0, ios::end);
	_size = in.tellg();
	in.seekg(0, ios::beg);

	if (_size <= 0) {
		AsyncLog::Error("Mysql file is empty. %s\n", filename);
		return false;
	}

	_pData = new char[_size];
	int read = 0;
	while (!in.eof()) {
		in.read((char*)_pData + read, _size - read);
		if (in.gcount() > 0) {
			read += (int)in.gcount();
		}
		else {
			break;
		}
	}
	in.close();
	_fieldType = MYSQL_TYPE_BLOB;
	return true;
}

bool Async::AsyncData::SaveFile(const char* filename)
{
	if (!_pData || _size <= 0) {
		return false;
	}
	fstream out(filename, ios::out | ios::binary);
	if (!out.is_open()) {
		AsyncLog::Error("Mysql save file failed. %s\n", filename);
		return false;
	}
	out.write(_pData, _size);
	return true;
}

void Async::AsyncData::DeleteData()
{
	if (_pData) {
		delete[] _pData;
		_pData = nullptr;
	}
}
