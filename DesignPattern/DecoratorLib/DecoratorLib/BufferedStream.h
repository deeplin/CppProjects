#pragma once
#include "DecoratorStream.h"
class BufferedStream :
    public DecoratorStream
{
public:
    BufferedStream(Stream* stream) : DecoratorStream(stream) {
    }
    virtual ~BufferedStream() {
    }

    virtual string operation() {
        return "buffered " + DecoratorStream::m_Stream->operation();
    }
};