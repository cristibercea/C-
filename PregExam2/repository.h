#pragma once
#include "domain.h"
#include "Observer.h"
#include <vector>
using std::vector;
class Repository: public Observable
{
	vector<Produs> repo;
	string fil;
	
	/// <summary>
	/// preia date din fisier
	/// </summary>
	void loadFromFile();

	/// <summary>
	/// salveaza date in fisier
	/// </summary>
	void storeToFile() const;
public:
	Repository(string file) : fil{ file } { loadFromFile(); }

	/// <summary>
	/// salveaza un nou produs in repo
	/// arunca exceptie daca avem duplicat
	/// </summary>
	/// <param name="p"></param>
	void store(const Produs& p);

	/// <summary>
	/// ret toate elem din repo
	/// </summary>
	/// <returns></returns>
	vector<Produs> getAll() const { return repo; }
};

