#include "service.h"
#include <algorithm>

void Service::adauga(string titlu, string artist, string gen)
{
	int id = rep.getAll().back().getId() + 1;
	Melodie m(id, titlu, artist, gen);
	rep.store(m);
}

void Service::sterge(int id)
{
	vector<Melodie> v = rep.getAll();
	auto it = std::find_if(v.begin(), v.end(), [&id](const Melodie& m) { return m.getId() == id; });
	rep.destroy(*it);
}

int Service::nrMelodiiArtist(const string& art)
{
	int nr = 0;
	vector<Melodie> v = rep.getAll();
	for (const auto& e : v) if (art == e.getArtist()) nr++;
	return nr;
}

int Service::nrMelodiiGen(const string& gen)
{
	int nr = 0;
	vector<Melodie> v = rep.getAll();
	for (const auto& e : v) if (gen == e.getGen()) nr++;
	return nr;
}


