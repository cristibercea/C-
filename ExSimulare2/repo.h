#pragma once
#include <vector>
#include "domain.h"
using std::vector;
class Repo
{
private:
	string& filename;
	vector<Tricou> rep;

	//loads the data from the file (file <- filename)
	void loadFromFile();
public:
	Repo(string file) :filename{file} {
		loadFromFile();
	}
	//gets all the data stored in repo
	vector<Tricou> getAll();
};

