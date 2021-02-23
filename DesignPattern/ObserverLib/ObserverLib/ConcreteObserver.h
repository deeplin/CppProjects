#pragma once
#include <iostream>
#include "IObserver.h"
using namespace std;

template<typename T>
class ConcreteObserver : public IObserver<T>
{
public:
    ConcreteObserver(int id) : m_Id(id), IObserver<T>() {
    }

    ~ConcreteObserver() {
    }

    void update(const T& count) {
		cout << "Observer Id=" << m_Id << " data=" << count << endl;
    }

private:
    int m_Id;
};

