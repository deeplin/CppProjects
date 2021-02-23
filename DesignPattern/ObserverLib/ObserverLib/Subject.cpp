#include "Subject.h"

using namespace std;

void Subject::attach(Observer* observer)
{
	m_ObserverVector.push_back(observer);
}

void Subject::detach(Observer* observer)
{
	for (vector<Observer*>::iterator iterStart = m_ObserverVector.begin(); 
		iterStart != m_ObserverVector.end(); iterStart++) {
		if (*iterStart == observer) {
			m_ObserverVector.erase(iterStart);
			iterStart = m_ObserverVector.begin();
		}
	}
}

void Subject::listObserver()
{
	for (vector<Observer*>::iterator iterStart = m_ObserverVector.begin(); iterStart != m_ObserverVector.end(); iterStart++) {
		(*iterStart)->update(0);
	}
}