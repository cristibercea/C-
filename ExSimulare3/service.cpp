#include "service.h"
#include <algorithm>
#include <iterator>
void Service::addPlaci(const string nume, const string soclu, const int pret) {
	try {
		placi.store(PlacaDeBaza(nume, soclu, pret));
	}
	catch (std::exception& e) { throw std::exception(); }
}

vector<PlacaDeBaza> Service::filtruSoclu(string soc)
{
	vector<PlacaDeBaza> src = getPlaciDeBaza();
	vector<PlacaDeBaza> filtered;

	std::copy_if(src.begin(), src.end(), back_inserter(filtered), [soc](PlacaDeBaza p) { return p.get_soclu() == soc; });

	return filtered;
}
