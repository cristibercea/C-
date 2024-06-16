#pragma once
class test
{
public:
	//runs all tests
	void runTests();
private:
	//runs domain tests
	void testDomain();

	//runs repo tests
	void testRepo();

	//runs service tests
	void testServ(); 
};

