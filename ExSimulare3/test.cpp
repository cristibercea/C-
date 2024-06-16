#include "test.h"
#include "service.h"
#include <cassert>

void tester::runAllTests() const {
	runDomainTests();
	runRepoTests();
	runServTests();
}

void tester::runDomainTests() const
{
	PlacaDeBaza pb("nume", "soclu", 1);
	assert(pb.get_nume()=="nume");
	assert(pb.get_soclu()=="soclu");
	assert(pb.get_pret()==1);

	Procesor pr("nume", 123, "soclu", 1);
	assert(pr.get_nume() == "nume");
	assert(pr.get_soclu() == "soclu");
	assert(pr.get_pret() == 1); 
	assert(pr.get_threads() == 123);  
}

void tester::runServTests() const
{
	repoPR pr("proc.txt");
	repoPB pb("placi.txt"); 
	Service serv(pb, pr);

	PlacaDeBaza pbz("soeg goh srnh ud", "soc1", 1234); 
	assert(serv.getProcesoare().size() == 5);
	assert(serv.getPlaciDeBaza()[0] == pbz);

	try { serv.addPlaci(pbz.get_nume(), pbz.get_soclu(), pbz.get_pret()); assert(false); }
	catch (std::exception& e) {}
}

void tester::runRepoTests() const
{
	repoPR pr("proc.txt");
	Procesor prc("sdgvh", 124, "soc1", 1234);
	assert(pr.getAll()[0] == prc);

	repoPB pb("placi.txt");
	PlacaDeBaza pbz("soeg goh srnh ud", "soc1", 1234);
	assert(pb.getAll()[0] == pbz);

	try { pb.store(pbz); assert(false); }
	catch (std::exception& e) {}
}
