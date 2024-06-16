#pragma once
#include <string>
using std::string;
class Tricou
{
private:
	string univers, model, marime;
	int pret;
public:
	Tricou(string num, int prt, string mar, string unv) : univers{ unv }, model{ num }, pret{ prt }, marime{ mar } {}

	//gets the price
	int get_pret() const { return pret; }

	//gets the universe name
	string get_univers() const { return univers; }

	//gets the model name
	string get_model() const { return model; }

	//gets the size
	string get_marime() const { return marime; }

	bool operator==(const Tricou& ot) const {return ot.get_marime() == marime && ot.get_pret() == pret && ot.get_univers() == univers && ot.get_model() == model;}
	bool operator!=(const Tricou& ot) const { return !(ot == *this); }
};

