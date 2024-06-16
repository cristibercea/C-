#pragma once
#include "repo.h"

class Service
{
private:
	Repo& rep;

public:
	Service(Service& srv) = delete;
	Service(Repo& r) : rep{ r } {}

	//gets all Tricou from repo
	vector<Tricou> getAll() { return rep.getAll(); }

	//sorts all Tricou from repo
	vector<Tricou> sortAll();
};

