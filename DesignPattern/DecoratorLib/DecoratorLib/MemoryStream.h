#pragma once
#include "Stream.h"
class MemoryStream :
    public Stream
{
public:
    MemoryStream() :Stream() {
    }
    virtual ~MemoryStream() {
    }
    virtual string operation();
};

