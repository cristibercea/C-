#include "tests.h"
#include <cassert>
#include "service.h"

void tests::startTests() const{
	testDomain();
	testRepo();
	testServ();
}

void tests::testDomain() const{
	doctor d("cnp","nume", "prenume", "sec", 1);
	assert(d.get_cnp()=="cnp");
	assert(d.get_nume()=="nume");
	assert(d.get_prenume()=="prenume");
	assert(d.get_sectie()=="sec");
	assert(d.get_status()==1);
}

void tests::testRepo() const {
	string file = "data.txt";
	repo test(file);

	assert(test.get_all()[0]==doctor("5030183432742","Dumbrava","Alin","pediatrie",1));
	///...
}

void tests::testServ() const
{
	string file = "data.txt"; 
	repo test(file); 
	service s(test); 

	assert(s.get_all()[0] == doctor("5030183432742", "Dumbrava", "Alin", "pediatrie", 1));
}
