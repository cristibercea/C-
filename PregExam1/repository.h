#pragma once
#include "domain.h"
#include <vector>
using std::vector;
class Repo
{
	vector<Melodie> rep;
	string file;
public:
	Repo(const string& f) : file{f} {loadFromFile();}

	/// <summary>
	/// ia melodii din fisier si le introduce in repo
	/// </summary>
	void loadFromFile();

	/// <summary>
	/// actualizeaza file repo
	/// </summary>
	void writeFile();

	/// <summary>
	/// adauga o melodie in repo
	/// </summary>
	/// <param name="m"></param>
	void store(const Melodie& m);

	/// <summary>
	/// sterge o melodie din repo
	/// </summary>
	/// <param name="m"></param>
	void destroy(Melodie& m);

	/// <summary>
	/// ia datele din repo
	/// </summary>
	/// <returns>datele din repo</returns>
	vector<Melodie> getAll() { return rep; }
};

