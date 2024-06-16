#pragma once
#include <string>
using std::string;

class Produs{
	int id, vocale;
	string nume, tip;
	double pret;
public:
	Produs(int id, string nume, string tip, double pret) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret } { 
		vocale = 0; for (const char& c : nume) for (const char& voc : "aeiouAEIOU") if (c == voc) { vocale++; break; }
	}
	int getId() const { return id; }
	string getNume() const { return nume; }
	void setNume(const string& numw) { nume=numw; }
	string getTip() const { return tip; }
	double getPret() const { return pret; }
	bool operator==(const Produs& o) const { return id == o.getId()&&nume==o.getNume()&&tip==o.getTip()&&pret==o.getPret(); }
	bool operator!=(const Produs& o) const { return !(*this == o); }
	int nrVocale() const { return vocale; }
};

