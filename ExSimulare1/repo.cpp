#include "repo.h"
#include <fstream>
void repo::loadFromFile()
{
	std::ifstream in(file);
	while (!in.eof()) {
		string num, pren, cnp, sec;
		int stat;
		std::getline(in, cnp);
		std::getline(in, num);
		std::getline(in, pren);
		std::getline(in, sec);
		in >> stat;
		if (in.eof()) break;
		in.get();
		rep.push_back(doctor(cnp, num, pren, sec, stat));
	}
	in.close();
}

vector<doctor> repo::get_all() const
{
	return rep;
}
