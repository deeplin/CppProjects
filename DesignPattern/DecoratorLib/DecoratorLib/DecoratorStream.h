#pragma once
#include "Stream.h"

class DecoratorStream :
    public Stream
{
public:
    DecoratorStream(Stream* stream) : m_Stream(stream) {
	}
protected:
    Stream* m_Stream;
};

