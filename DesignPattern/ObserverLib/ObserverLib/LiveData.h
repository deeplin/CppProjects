#pragma once
#include "Subject.h"

template<typename T>
class LiveData :
    public Subject<T>
{
public:
    LiveData() : Subject<T>(), m_T(NULL){
	}
    virtual ~LiveData() {
    }

    void postData(const T& t) {
        if (t != m_T) {
            m_T = t;
            Subject<T>::notify(t);
        }
    }

private:
    T m_T;
};

