#pragma once
#include "domain.h"
#include <vector>
using std::vector;
class repoPB{
private:
	vector<PlacaDeBaza> rep;
	string file;
	void loadFromFile();
public:
	repoPB(string f) :file{ f } {
		loadFromFile();
	}
	vector<PlacaDeBaza> getAll() { return rep; }
	void store(const PlacaDeBaza& p);
};

class repoPR {
private:
	vector<Procesor> rep;
	string file;
	void loadFromFile();
public:
	repoPR(string f) :file{ f } {
		loadFromFile();
	}
	vector<Procesor> getAll() { return rep; }
};

