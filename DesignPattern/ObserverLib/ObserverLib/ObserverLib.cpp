// ObserverLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Subject.h"
#include "IObserver.h"
#include "ConcreteObserver.h"
#include "LiveData.h"

using namespace std;

void testConcreteObserver() {
    Subject<int> subject;

    IObserver<int>* observer1 = new ConcreteObserver<int>(10);
    IObserver<int>* observer2 = new ConcreteObserver<int>(20);
    IObserver<int>* observer3 = new ConcreteObserver<int>(30);

    subject.Attach(observer1);
    subject.Attach(observer2);
    subject.Attach(observer3);
    subject.Attach(observer2);
    subject.Attach(observer2);
    subject.Attach(observer2);

    subject.ListObserver();
    subject.notify(123);

    cout << "-------" << endl;

    subject.Detach(observer2);
    subject.Detach(observer1);

    subject.notify(234);
}

void testLiveData() {
    LiveData<int> liveData;

    IObserver<int>* observer1 = new ConcreteObserver<int>(10);
    liveData.Attach(observer1);

    for (int index = 0; index < 10; index++) {
        liveData.postData(index + 10);
		liveData.postData(index + 10);
    }
}

int main()
{
    //testConcreteObserver();
    testLiveData();
}
