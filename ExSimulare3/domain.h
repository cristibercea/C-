#pragma once
#include <string>
using std::string;
class Procesor
{
private:
	string nume, soclu;
	int pret, threads;
public:
	Procesor(string num, int thr, string soc, int prt) : nume{ num }, threads{ thr }, soclu{ soc }, pret{prt} {}
	string get_nume() const { return nume; }
	string get_soclu() const { return soclu; }
	int get_threads() const { return threads; }
	int get_pret() const { return pret; }

	bool operator==(const Procesor o) const {
		return nume == o.get_nume() && soclu == o.get_soclu() && pret == o.get_pret() && threads == o.get_threads();
	}

	bool operator!=(const Procesor o) const {
		return !(o == *this);
	}
};

class PlacaDeBaza
{
private:
	string nume, soclu;
	int pret;
public:
	PlacaDeBaza(string num, string soc, int prt) : nume{ num }, soclu{ soc }, pret{ prt } {}
	string get_nume() const { return nume; }
	string get_soclu() const { return soclu; }
	int get_pret() const { return pret; }

	bool operator==(const PlacaDeBaza o) const {
		return nume==o.get_nume() && soclu == o.get_soclu() && pret == o.get_pret();
	}

	bool operator!=(const PlacaDeBaza o) const {
		return !(o==*this);
	}
};

