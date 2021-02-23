#pragma once
#include "DecoratorStream.h"
#include <string>
class CryptoStream :
    public DecoratorStream
{
public:
    CryptoStream(Stream* stream) : DecoratorStream(stream){
    }
    virtual ~CryptoStream() {
    }
    virtual string operation();
};
