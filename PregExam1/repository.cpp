#include "repository.h"
#include <fstream>

void Repo::loadFromFile()
{
	std::ifstream in(file);
	if (!in.is_open()) throw std::exception("error opening file!");

	int id;
	string tit, art, gen;
	while (!in.eof()) {
		in >> id;
		in.get();
		std::getline(in, tit);
		std::getline(in, art);
		std::getline(in, gen);
		if (in.eof()) break;
		Melodie m(id,tit, art, gen);
		rep.push_back(m);
	}

	in.close();
}

void Repo::writeFile()
{
	std::ofstream out(file);

	for (const Melodie& e : rep) {
		out << e.getId()<<std::endl;
		out << e.getTitlu()<<std::endl;
		out << e.getArtist()<<std::endl;
		out << e.getGen()<<std::endl;
	}

	out.close();
}

void Repo::store(const Melodie& m)
{
	rep.push_back(m);
	writeFile();
}

void Repo::destroy(Melodie& m)
{
	rep.erase(remove(rep.begin(), rep.end(), m));
	writeFile();
}

