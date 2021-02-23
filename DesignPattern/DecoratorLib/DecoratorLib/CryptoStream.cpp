#include "CryptoStream.h"

string CryptoStream::operation()
{
	return "Crypto " + DecoratorStream::m_Stream->operation();
}
