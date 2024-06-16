#pragma once
#include "domain.h"
#include <vector>
using std::vector;
class Repo
{
private:
	string file;
	vector<Stock> rep;
	void loadFromFile();
public:
	Repo(const string& f) : file{f} {
		loadFromFile();
	}
	vector<Stock> getAll() const;
};

