#include "test.h"
#include "service.h"
#include <cassert>

void Tester::testDomain() const
{
	Produs p(1, "aba", "c", 22.5);
	assert(p.getId() == 1);
	assert(p.getNume() == "aba");
	assert(p.getTip() == "c");
	assert(p.getPret() == 22.5);
	assert(p.nrVocale() == 2);
}

void Tester::testRepository() const
{
	Repository r("test.txt");
	Produs dup(1, "asihd", "aihvf", 22.5);

	assert(r.getAll().size() == 5);
	try { r.store(dup); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert(" " == s); }
}

void Tester::testService() const
{
	Repository r("test.txt");
	Service s(r);
	try { s.adaugare(1, "asihd", "aihvf", 22.5); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Id deja existent!" == s); }
	try { s.adaugare(122, "dasf", "aihvf", 222.5); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Pret invalid!" == s); }
}

void Tester::runAll() const
{
	testDomain();
	testRepository();
	testService();
}
