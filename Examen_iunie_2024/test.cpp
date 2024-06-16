#include "test.h"
#include "service.h"
#include <cassert>

void Tester::testDomain() const
{
	Task t(1, "a", "b", { "c","d","e" });
	assert(t.getDescriere()=="a"); 
	assert(t.getStare()=="b"); 
	assert(t.getId()==1);
	assert(t.getProgramatori().size() == 3); 
	assert(t.getProgramatori()[1] == "d"); 
	assert(t.getProgramatori()[2] == "e");
	assert(t.getProgramatori()[0] == "c");
}

void Tester::testRepo() const
{
	Repository r("test.txt");
	Task t(11, "a", "b", { "c","d","e" });
	vector<Task> v = r.getAll();
	assert(v.size() == 4);
	assert(r.find("sidjbfihrsebg").size() == 0);
	assert(r.find("Alin").size() == 2);
	try { r.store(t); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Id deja existent in app!" ==s); }
}

void Tester::testService() const
{
	Repository r("test.txt");
	Service s(r);
	vector<Task> v = s.getAllSorted();
	assert(v.size() == 4);
	assert(s.filtruProgramator("sidjbfihrsebg").size() == 0);
	assert(s.filtruProgramator("Alin").size() == 2);
	try { s.adauga(11, "a", "open", { "c","d","e" }); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Id deja existent in app!" == s); }
	try { s.adauga(11, "a", "open", { "c","d","e","s","e"}); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Numar invalid de programatori!" == s); }
	try { s.adauga(11, "a", "open", { }); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Numar invalid de programatori!" == s); }
	try { s.adauga(11, "a", "b", { "c","d","e" }); assert(false); }
	catch (std::exception& e) { string s = e.what(); assert("Stare invalida!" == s); }
}

void Tester::runAll() const
{
	testDomain();
	testRepo();
	testService();
}
