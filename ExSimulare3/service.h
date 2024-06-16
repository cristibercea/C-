#pragma once
#include "repo.h"
class Service
{
private:
	repoPB& placi;
	repoPR& procesoare;
public:
	Service(repoPB& pb, repoPR& pr) : placi{ pb }, procesoare{ pr } {}
	vector<Procesor> getProcesoare() { return procesoare.getAll(); }
	vector<PlacaDeBaza> getPlaciDeBaza() { return placi.getAll(); }
	void addPlaci(const string nume, const string soclu, const int pret);
	vector<PlacaDeBaza> filtruSoclu(string soc);
};

