#pragma once
#include "Stream.h"
class FileStream :
    public Stream
{
public:
    FileStream() : Stream(){
    }
    virtual ~FileStream() {
    }

    virtual string operation();

};

