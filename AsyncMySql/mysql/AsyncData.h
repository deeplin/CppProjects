#pragma once

#ifdef AsyncMySqlDll
#define ASYNCAPI __declspec(dllexport)
#else
#define ASYNCAPI __declspec(dllimport)
#endif

#include <string>
#include "AsyncFieldType.h"

namespace Async {
	struct ASYNCAPI AsyncData {
		uint64_t _size = 0;
		AsyncFieldType _fieldType;
		const char* _pData = nullptr;

		AsyncData(const char* pData = nullptr) {
			if (pData) {
				_size = strlen(pData);
				_fieldType = MYSQL_TYPE_STRING;
				_pData = pData;
			}
		}

		AsyncData(const int* data) {
			_size = sizeof(int);
			_fieldType = MYSQL_TYPE_LONG;
			_pData = (const char*) data;
		}

		bool LoadFile(const char* filename);

		bool SaveFile(const char* filename);

		void DeleteData();
	};
}
