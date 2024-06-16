#pragma once
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
};

class Observable {
	std::vector<Observer*> o;
public: 
	void AddObserver(Observer* ob) { o.push_back(ob); }
	void RmObserver(Observer* ob) { o.push_back(ob); }
protected:
	void notify() { for (auto v : o) v->update(); }
};
