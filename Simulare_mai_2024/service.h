#pragma once
#include "repo.h"

class Service
{
private:
	Repo &rep;
public:
	Service(Repo& r):rep{r}{}
	vector<Stock> getAll() const;
	void sterge(string id);
};

