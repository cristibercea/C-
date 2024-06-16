#include "repository.h"
#include <fstream>
#include <algorithm>

void Repository::loadFromFile()
{
	std::ifstream in(fil);
	if (!in.is_open()) throw std::exception("Nu s-a putut deschide fisierul!\n");
	
	while (!in.eof()) {
		int id; 
		string nume, tip;
		double pret;
		in >> id;
		in.get(); 
		std::getline(in, nume); 
		std::getline(in, tip);
		in >> pret;

		if (in.eof()) break;
		Produs p(id, nume, tip, pret);
		repo.push_back(p);
	} 
	
	in.close();
}

void Repository::storeToFile() const
{
	std::ofstream out(fil);

	for (const auto& p : repo) {
		out << p.getId() << std::endl;
		out << p.getNume() << std::endl; 
		out << p.getTip() << std::endl; 
		out << p.getPret() << std::endl; 
	}

	out.close(); 
}

void Repository::store(const Produs& p)
{
	int ok = 0;
	auto it = find_if(repo.begin(), repo.end(), [p, &ok](const Produs& pp) { ok = p.getId() == pp.getId(); return ok; });
	if (ok == 1) throw std::exception(" ");
	repo.push_back(p);
	storeToFile();
	notify();
}
