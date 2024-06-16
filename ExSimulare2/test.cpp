#include "test.h"
#include "service.h"
#include <cassert>

void test::runTests()
{
	testDomain();
	testRepo();
	testServ();
}

void test::testDomain()
{
	Tricou t("model", 100, "XXL", "univers");
	assert(t.get_marime()=="XXL");
	assert(t.get_model()=="model");
	assert(t.get_univers()=="univers");
	assert(t.get_pret()==100);
}

void test::testRepo()
{
	Repo test("data.txt");
	assert(test.getAll()[0].get_marime() == "S");
	assert(test.getAll()[0].get_model() == "sdkjfgh");
	assert(test.getAll()[0].get_univers() == "Marvel");
	assert(test.getAll()[0].get_pret() == 123);
	assert(test.getAll().size() == 10);
}

void test::testServ()
{
	Repo rep("data.txt");
	Service test(rep);
	assert(test.getAll()[0].get_marime() == "S");
	assert(test.getAll()[0].get_model() == "sdkjfgh");
	assert(test.getAll()[0].get_univers() == "Marvel");
	assert(test.getAll()[0].get_pret() == 123);
	assert(test.getAll().size() == 10);

	assert(test.sortAll()[0].get_marime() == "XL"); 
	assert(test.sortAll()[0].get_model() == "dorsdg"); 
	assert(test.sortAll()[0].get_univers() == "Marvel"); 
	assert(test.sortAll()[0].get_pret() == 120); 
}
