#pragma once
#include <vector>
#include "domain.h"
using std::vector;

class repo{
	vector<doctor> rep;
	string& file;
	void loadFromFile();
public:
	repo(string& f) : file{f} { loadFromFile(); }
	
	vector<doctor> get_all() const;


};

