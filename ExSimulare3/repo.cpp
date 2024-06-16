#include "repo.h"
#include <fstream>
void repoPB::loadFromFile()
{
	std::ifstream in(file);

	while(!in.eof()){
		string nume, soclu;
		int pret;
		std::getline(in, nume);
		std::getline(in, soclu);
		in >> pret;
		in.get();
		if (in.eof()) break;
		PlacaDeBaza pb(nume, soclu, pret);
		rep.push_back(pb);
	}

	in.close();
}

void repoPB::store(const PlacaDeBaza& p)
{
	for (PlacaDeBaza pb : rep) if (pb == p) throw std::exception();
	rep.push_back(p);

	std::ofstream out(file);
	for (const PlacaDeBaza& el : getAll()) {
		out << el.get_nume() << "\n";
		out << el.get_soclu() << "\n";
		out << el.get_pret() << "\n";
	}
}

void repoPR::loadFromFile()
{
	std::ifstream in(file); 

	while (!in.eof()) {
		string nume, soclu; 
		int pret, threads; 
		std::getline(in, nume); 
		in >> threads;
		in.get();
		std::getline(in, soclu); 
		in >> pret; 
		in.get(); 
		if (in.eof()) break; 
		Procesor pr(nume, threads, soclu, pret); 
		rep.push_back(pr); 
	}

	in.close(); 
}
