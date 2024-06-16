#include "test.h"
#include "service.h"
#include <cassert>

void Tester::runAll() const
{
	testDomain();
	testRepo();
	testService();
}

void Tester::testDomain() const
{
	float i= 11.23;
	Stock s("IDID", "nume", i, -12);
	assert(s.get_id()=="IDID");
	assert(s.get_name()=="nume");
	assert(s.get_price()==i);
	assert(s.get_rate()==-12);
}

void Tester::testRepo() const
{
	Repo test("test.txt");
	vector<Stock> t = test.getAll();
	assert(t[0].get_id() == "AAPL");
	assert(t[0].get_name() == "Apple Inc.");
	assert(t[0].get_price() == (float)192.35);
	assert(t[0].get_rate() == 16);
	assert(t.size()==10);
}

void Tester::testService() const
{
	Repo test("test.txt");
	Service srv(test);
	vector<Stock> t = srv.getAll();
	assert(t[0].get_id() == "AAPL"); 
	assert(t[0].get_name() == "Apple Inc."); 
	assert(t[0].get_price() == (float)192.35); 
	assert(t[0].get_rate() == 16); 
	assert(t.size() == 10);
}
