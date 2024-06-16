#include "service.h"

void Service::adauga(int id, string descriere, string status, vector<string> programatori)
{
	int ok = 0;
	for (const auto& s : { "open", "inprogress", "closed" }) if (status == s) ok = 1;
	if(!ok) throw std::exception("Stare invalida!");
	if(programatori.size()<1||programatori.size()>4) throw std::exception("Numar invalid de programatori!");
	try { Task t(id, descriere, status, programatori); repo.store(t); }
	catch (std::exception& e) { throw e; }
}

void Service::editStat(const string& stat, const int& id)
{
	repo.edit(stat, id);
}
