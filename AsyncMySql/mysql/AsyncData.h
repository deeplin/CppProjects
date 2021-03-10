#pragma once

#ifdef AsyncMySqlDll
#define ASYNCAPI __declspec(dllexport)
#else
#define ASYNCAPI __declspec(dllimport)
#endif

#include <string>

namespace Async {
	struct ASYNCAPI AsyncData {
		AsyncData(const char* pData = nullptr) {
			if (pData) {
				_pData = pData;
				_size = strlen(pData);
			}
		}
		const char* _pData = nullptr;
		uint64_t _size = 0;
	};
}
