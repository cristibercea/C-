#pragma once
#include "repository.h"
#include <algorithm>

class Service
{
	Repository& rep;
public:
	Service(Repository& repository) :rep{repository}{}

	/// <summary>
	/// adauga un produs nou in app
	/// daca datele sunt invalie arunca exceptie
	/// daca avem duplicat arunca exceptie
	/// </summary>
	/// <param name="id"></param>
	/// <param name="nume"></param>
	/// <param name="tip"></param>
	/// <param name="pret"></param>
	void adaugare(const int& id, const string& nume, const string& tip, const double& pret);

	/// <summary>
	/// ret produsele din repo ordonate dupa pret
	/// </summary>
	/// <returns></returns>
	vector<Produs> getAllSorted() const;

	/// <summary>
	/// filtreaza produse dupa pret
	/// </summary>
	/// <param name="val"></param>
	/// <returns></returns>
	vector<Produs> filter(const double& val) const;

	/// <summary>
	/// returneaza tipurile de produse
	/// </summary>
	/// <returns></returns>
	std::pair<vector<string>, vector<int>> tipuri() const;

	void addObserver(Observer* o) { rep.addObserver(o); }
	void rmvObserver(Observer* o) { rep.rmvObserver(o); }
};

