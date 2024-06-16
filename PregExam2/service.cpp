#include "service.h"

void Service::adaugare(const int& id, const string& nume, const string& tip, const double& pret){
	if (pret < 1.0 || pret>100.0) throw std::exception("Pret invalid!");
	try {
		Produs p(id, nume, tip, pret);
		rep.store(p);
	}
	catch (std::exception& ) { throw std::exception("Id deja existent!"); }
}

vector<Produs> Service::getAllSorted() const {
	vector<Produs> v = rep.getAll();
	sort(v.begin(), v.end(), [](const Produs& p1, const Produs& p2) { return p1.getPret() > p2.getPret(); });
	return v;
}

vector<Produs> Service::filter(const double& val) const
{
	vector<Produs> s = getAllSorted();
	vector<Produs> d;
	for (const Produs& p : s)
		if (p.getPret() < val)
			d.push_back(p);
	return d;
}

std::pair<vector<string>, vector<int>> Service::tipuri() const
{
	vector<string> v;
	for (const Produs& el : getAllSorted()) {
		int ok = 1;
		for(const string& e : v)
			if (el.getTip() == e) {
				ok = 0;
				break;
			}
		if (ok) v.push_back(el.getTip());
	}
	vector<int> v2(v.size(), 0);
	for (const Produs& el : getAllSorted())
		for (int i=0;i<v.size();i++)
			if (el.getTip() == v[i])
				v2[i]++;
	return { v,v2 };
}