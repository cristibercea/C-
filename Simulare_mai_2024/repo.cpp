#include "repo.h"
#include <fstream>
void Repo::loadFromFile()
{
	std::ifstream in(file);

	while (!in.eof()) {
		string id, num;
		int rat;
		float pric;

		std::getline(in, id);
		std::getline(in, num);
		in >> pric;
		in.get();
		in >> rat;
		in.get();
		
		if (in.eof()) break;
		Stock s(id,num, pric,rat);
		rep.push_back(s);
	}

	in.close();
}

vector<Stock> Repo::getAll() const
{
	return rep;
}
