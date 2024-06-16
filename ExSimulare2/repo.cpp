#include "repo.h"
#include <fstream>

void Repo::loadFromFile()
{
	std::ifstream in(filename);
	
	string model, univers, marime;
	int pret;

	while (!in.eof()) {
		getline(in,model);
		in >> pret;
		in.get();
		getline(in, marime); 
		getline(in, univers);
		if (in.eof()) break;
		rep.push_back(Tricou(model,pret,marime,univers));
	}
	
	in.close();
}

vector<Tricou> Repo::getAll(){return rep;}
