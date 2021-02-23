#pragma once
#include <vector>
#include "IObserver.h"
#include "ISubject.h"
#include "algorithm"

using namespace std;

template <typename T>
class Subject : public ISubject<T>
{
public:
	Subject() {
	}

	virtual ~Subject() {
	}

	virtual void Attach(IObserver<T>* pObserver) {
		m_ObserverVector.push_back(pObserver);
	}

	virtual void Detach(IObserver<T>* pObserver) {
		auto it = m_ObserverVector.begin();
		while (true) {
			it = find(it, m_ObserverVector.end(), pObserver);
			if (it == m_ObserverVector.end()) {
				break;
			}
			it = m_ObserverVector.erase(it);
		}
		//for (auto iterStart = m_ObserverVector.begin();
		//	iterStart != m_ObserverVector.end(); iterStart++) {
		//	if (*iterStart == pObserver) {
		//		m_ObserverVector.erase(iterStart);
		//		iterStart = m_ObserverVector.begin();
		//	}
		//}
	}

	void ListObserver() {
		for (auto iterStart = m_ObserverVector.begin();
			iterStart != m_ObserverVector.end(); iterStart++) {
			(*iterStart)->update(0);
		}
	}

	void notify(const T& t) {
		for (auto iterStart = m_ObserverVector.begin();
			iterStart != m_ObserverVector.end(); iterStart++) {
			(*iterStart)->update(t);
		}
	}
private:
	vector<IObserver<T>*> m_ObserverVector;
};