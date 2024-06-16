#pragma once
#include "repository.h"

class Service
{
	Repo& rep;
public:
	Service(Repo& r) : rep{ r } {}

	/// <summary>
	/// adauga melodie
	/// </summary>
	/// <param name="titlu"></param>
	/// <param name="artist"></param>
	/// <param name="gen"></param>
	void adauga(string titlu, string artist, string gen);

	/// <summary>
	/// sterge o melodie
	/// </summary>
	/// <param name="id"></param>
	void sterge(int id);

	/// <summary>
	/// returneaza nr de melodii de la artistul "art"
	/// </summary>
	/// <param name="art"></param>
	/// <returns></returns>
	int nrMelodiiArtist(const string& art);

	/// <summary>
	/// returneaza nr de melodii de genul "gen"
	/// </summary>
	/// <param name="gen"></param>
	/// <returns></returns>
	int nrMelodiiGen(const string& gen);

	/// <summary>
	/// ia toate elem din repo sortate dupa autor
	/// </summary>
	/// <returns></returns>
	vector<Melodie> getAllSorted() { return rep.getAll(); }
};

