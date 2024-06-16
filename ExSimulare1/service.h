#pragma once
#include "repo.h"
class service{
	repo& rep;
public:
	service(repo& r) : rep{r} {}
	vector<doctor> get_all();

};

