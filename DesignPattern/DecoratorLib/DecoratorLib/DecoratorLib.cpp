// DecoratorLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Stream.h"
#include "FileStream.h"
#include "MemoryStream.h"
#include "BufferedStream.h"
#include "CryptoStream.h"

using namespace std;

int main()
{
	Stream* stream = new FileStream();

	BufferedStream bufferedStream(stream);
	CryptoStream cryptoStream(&bufferedStream);
	CryptoStream cryptoCryptoStream(&cryptoStream);

	cout << stream->operation() << endl;
	cout << bufferedStream.operation() << endl;
	cout << cryptoStream.operation() << endl;
	cout << cryptoCryptoStream.operation() << endl;
	delete stream;
}