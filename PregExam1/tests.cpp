#include "tests.h"
#include "service.h"
#include <cassert>

void Tester::runAll() const noexcept {
	runDomainTests();
	runRepoTests();
	runServiceTests();
}

void Tester::runDomainTests() const noexcept
{
	Melodie m(1,"a","b","c");
	assert(m.getId() == 1);
	assert(m.getTitlu() == "a");
	assert(m.getArtist() == "b");
	assert(m.getGen() == "c");
}

void Tester::runRepoTests() const noexcept
{
	Repo r("test.txt");
	assert(r.getAll().size() == 5);
	Melodie m(11, "a", "b", "c");
	r.store(m);
	assert(r.getAll().size() == 6);
	r.destroy(m);
	assert(r.getAll().size() == 5);
}

void Tester::runServiceTests() const noexcept
{
	Repo r("test.txt");
	Service s(r);
	assert(s.getAllSorted().size() == 5);
	s.adauga("a", "b", "c");
	assert(s.getAllSorted().size() == 6);
	s.sterge(6);
	assert(s.getAllSorted().size() == 5);
}
