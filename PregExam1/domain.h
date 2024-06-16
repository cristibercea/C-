#pragma once
#include <string>
using std::string;
class Melodie
{
	int id;
	string titlu, artist, gen;
public:
	Melodie(int i, string t, string a, string g) :id{ i }, titlu{ t }, artist{ a }, gen{ g } {}
	const string& getTitlu() const { return titlu; }
	const string& getArtist() const { return artist; }
	const string& getGen() const { return gen; }
	const int& getId() const { return id; }
	bool operator==(const Melodie& ot) const {
		return titlu==ot.getTitlu() && artist==ot.getArtist() && gen==ot.getGen() && id == ot.getId();
	}
	bool operator!=(const Melodie& ot) const {
		return !(*this==ot);
	}
};

