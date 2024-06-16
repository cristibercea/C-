#pragma once
#include <vector>
#include <algorithm>
class Observer { public: virtual void update() = 0; };

class Observable {
	std::vector<Observer*> v;
public:
	void addObserver(Observer* o) { v.push_back(o); }
	void rmvObserver(Observer* o) { v.erase(std::remove(v.begin(),v.end(),o)); }
protected:
	void notify() {
		for (auto p : v) p->update();
	}
};
