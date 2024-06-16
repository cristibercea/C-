#include "tests.h"
#include "service.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <stdlib.h>

void Tests::run_all() const {
	test_entity();
	test_validator();
	test_repository();
	test_file_repository();
	test_service();
	test_export_to_files();
	test_undo();
}

void Tests::test_entity() const {
	Tenant test("nume", 11, "tip", 100);
	assert(test.get_name() == "nume");
	assert(test.get_apartament() == 11);
	assert(test.get_type() == "tip");
	assert(test.get_area() == 100);

	Tenant test3(test);
	assert(test3.get_name() == "nume");
	assert(test3.get_apartament() == 11);
	assert(test3.get_type() == "tip");
	assert(test3.get_area() == 100);

	Tenant test2("aaa", 33333, "bbbb", 2222);
	test = test2;
	assert(test.get_name() == "aaa");
	assert(test.get_apartament() == 33333);
	assert(test.get_type() == "bbbb");
	assert(test.get_area() == 2222);

	assert(test != test3);

	std::cout << test << std::endl << test2;
	system("cls"); ///clears the screen after writting tests
}

void Tests::test_validator() const {
	Validator valid;
	valid.validate_name("aesytsju");
	try { valid.validate_name(""); assert(false); }
	catch (ValidatorException) {}

	try { valid.validate_name("OJFblkjkab^%$"); assert(false); }
	catch (ValidatorException) {}

	try { valid.validate_name("aljn esf12efj"); assert(false); }
	catch (ValidatorException) {}

	valid.validate_apart(1253);
	try { valid.validate_apart(-1253); assert(false); }
	catch (ValidatorException) {}

	valid.validate_type("ajhgih");
	try { valid.validate_type(""); assert(false); }
	catch (ValidatorException) {}

	try { valid.validate_type("OJFblkjkab^%$"); assert(false); }
	catch (ValidatorException) {}

	try { valid.validate_type("aljn esf12efj"); assert(false); }
	catch (ValidatorException) {}

	valid.validate_area(124);
	try { valid.validate_area(-1253); assert(false); }
	catch (ValidatorException) {}

	try { valid.validate_area(4); assert(false); }
	catch (ValidatorException) {}

	try { valid.validate_area(0); assert(false); }
	catch (ValidatorException) {}

	try { throw ValidatorException("ceva"); }
	catch (ValidatorException& v) { assert(v.get_message() == "ceva"); }
}

void Tests::test_repository() const {
	try { throw RepoException("ceva"); }
	catch (RepoException& r) { assert(r.get_message() == "ceva"); }

	InMemoryRepository test;
	Tenant t1("nume1", 1, "tip1", 11), t2("nume2", 2, "tip2", 12), t3("nume3", 3, "tip3", 13), t4("nume4", 4, "tip4", 14), t5("nume1", 5, "tip1", 11);

	test.store(t1);
	test.store(t2);
	try { test.store(t1); assert(false); }
	catch (RepoException) {}
	try { test.store(t5); assert(false); }
	catch (RepoException) {}
	test.store(t3);

	vector<Tenant> v = test.get_all();
	assert(test.get_size() == 3);
	assert(test.get_all()[0] == t1);
	assert(test.get_all()[1] == t2);
	assert(test.get_all()[2] == t3);

	test.edit(t1);
	test.edit(t3);
	test.edit(t2);
	try { test.edit(t4); assert(false); }
	catch (RepoException) {}

	assert(test.find_apartament(t1) == t1);
	assert(test.find_apartament(t2) == t2);
	assert(test.find_apartament(t3) == t3);
	try { test.find_apartament(t4); assert(false); }
	catch (RepoException) {}

	assert(test.find_name(t1.get_name()) == t1);
	assert(test.find_name(t2.get_name()) == t2);
	assert(test.find_name(t3.get_name()) == t3);
	assert(test.find_name(t4.get_name()) == Tenant("", -1, "", -1)); ///the invalid tenant

	test.destroy(t1.get_name());
	test.destroy(t3.get_name());
	test.destroy(t2.get_name());
	try { test.destroy(t4.get_name()); assert(false); }
	catch (RepoException) {}

	assert(test.get_all().empty());
}

void Tests::test_file_repository() const {
	try { FileRepository test("sdgdata.txt"); assert(false); }
	catch (RepoException) {}

	FileRepository test("datatest.txt");
	assert(test.get_size() == 1);
	Tenant t1("nume1", 3, "tip1", 11), t2("nume2", 2, "tip2", 12);

	test.store(t1);
	test.store(t2);
	assert(test.get_size() == 3);
	test.edit(t1);
	test.edit(t2);
	assert(test.get_size() == 3);
	test.destroy(t1.get_name());
	test.destroy(t2.get_name());
	assert(test.get_size() == 1);
}

void Tests::test_service() const {
	InMemoryRepository trepo;
	Validator tvalid;
	NotificationRepo noti;
	Service tserv(noti, trepo, tvalid);
	int n = 11, m = 10;
	Tenant t("nume", m, "tip", n);

	try { throw ServiceException("ceva"); }
	catch (ServiceException& v) { assert(v.get_message() == "ceva"); }

	try { tserv.add_apartament_to_notification_list(12); assert(false); }
	catch (ServiceException) {}

	assert(tserv.get_notif_list().size() == 0);
	vector<Tenant> ttest1;
	vector<Tenant> ttest2;
	tserv.add_tenant("nume", m, "tip", n);
	ttest1.push_back(Tenant("nume", m, "tip", n));
	m++, n++;
	tserv.add_tenant("numed", m, "tip", n);
	ttest1.push_back(Tenant("numed", m, "tip", n));
	m++, n++;
	tserv.add_tenant("numet", m, "tipt", n);
	ttest2.push_back(Tenant("numet", m, "tipt", n));
	m -= 2, n -= 2;
	try { tserv.add_tenant("nume", m, "tip", n); assert(false); }
	catch (ServiceException) {}
	try { tserv.add_tenant("invalid", m, "%%%", n); assert(false); }
	catch (ServiceException) {}
	assert(tserv.get_repo_size() == 3);

	std::map<string, vector<Tenant>> testmap;
	tserv.create_report(testmap);
	assert(testmap["tip"] == ttest1);
	assert(testmap["tipt"] == ttest2);

	tserv.add_apartament_to_notification_list(11);
	assert(tserv.get_notif_list().size() == 1);
	tserv.add_apartament_to_notification_list(12);
	try { tserv.add_apartament_to_notification_list(12); assert(false); }
	catch (ServiceException) {}
	assert(tserv.get_notif_list().size() == 2);
	tserv.clear_notification_list();
	assert(tserv.get_notif_list().empty()); 
	tserv.add_apartaments_randomly(2);
	tserv.add_apartaments_randomly(1);
	try { tserv.add_apartaments_randomly(2); assert(false); }
	catch (ServiceException) {}
	assert(tserv.get_notif_list().size() == 3);
	tserv.clear_notification_list();

	tserv.edit_tenant("nume", m, "tip", n);
	try { tserv.edit_tenant("numep", m, "tip", n); assert(false); }
	catch (ServiceException) {}
	try { tserv.edit_tenant("invalid", m, "%%%", n); assert(false); }
	catch (ServiceException) {}

	assert(tserv.find_apartament(m) == t);
	try { tserv.find_apartament(123); assert(false); }
	catch (ServiceException) {}
	try { tserv.find_apartament(463); assert(false); }
	catch (ServiceException) {}

	string s = "tip";
	vector<Tenant> v1;
	m++, n++;
	Tenant tt("numed", m, "tip", n);
	m++, n++;
	Tenant ttt("numet", m, "tipt", n);
	n -= 2, m -= 2;
	v1.push_back(t);
	v1.push_back(tt);
	assert(tserv.filter_by_type(s) == v1);
	s = "tipqwtrydu";
	try { tserv.filter_by_type(s); assert(false); }
	catch (ServiceException) {}
	s = "%$^&";
	try { tserv.filter_by_type(s); assert(false); }
	catch (ServiceException) {}
	v1.clear();

	v1.push_back(t);
	assert(tserv.filter_by_area(n) == v1);
	n += 100;
	try { tserv.filter_by_area(n); assert(false); }
	catch (ServiceException) {}
	n -= 10000;
	try { tserv.filter_by_area(n); assert(false); }
	catch (ServiceException) {}
	v1.clear();

	int c = 0;
	vector<Tenant> v;
	v.push_back(t);
	v.push_back(tt);
	v.push_back(ttt);
	assert(tserv.sort_manager(++c) == v);
	v.clear();

	v.push_back(ttt);
	v.push_back(tt);
	v.push_back(t);
	assert(tserv.sort_manager(++c) == v);
	v.clear();

	v.push_back(t);
	v.push_back(tt);
	v.push_back(ttt);
	assert(tserv.sort_manager(++c) == v);
	v.clear();

	v.push_back(ttt);
	v.push_back(tt);
	v.push_back(t);
	assert(tserv.sort_manager(++c) == v);
	v.clear();

	v.push_back(t);
	v.push_back(tt);
	v.push_back(ttt);
	assert(tserv.sort_manager(++c) == v);
	v.clear();

	v.push_back(ttt);
	v.push_back(tt);
	v.push_back(t);
	assert(tserv.sort_manager(++c) == v);
	v.clear();

	try { tserv.delete_tenant("numeweyt"); assert(false); }
	catch (ServiceException) {}
	tserv.delete_tenant("nume");
	tserv.delete_tenant("numed");
	tserv.delete_tenant("numet");
	try { tserv.delete_tenant("nume"); assert(false); }
	catch (ServiceException) {}
	try { tserv.delete_tenant("inv@lid"); assert(false); }
	catch (ServiceException) {}
	assert(tserv.get_all_from_repo().empty());
}

void Tests::test_export_to_files() const {
	Tenant t1("nume1", 1, "tip1", 11), t2("nume2", 2, "tip2", 12), t3("nume3", 3, "tip3", 13), t4("nume4", 4, "tip4", 14);
	InMemoryRepository trepo; 
	Validator tvalid; 
	NotificationRepo noti; 
	Service tserv(noti, trepo, tvalid); 
	trepo.store(t1);
	trepo.store(t2);
	trepo.store(t3);
	trepo.store(t4);
	tserv.add_apartament_to_notification_list(1);
	tserv.add_apartament_to_notification_list(2);
	tserv.add_apartament_to_notification_list(3);
	tserv.add_apartament_to_notification_list(4);
	//tserv.add_apartaments_randomly(3);
	tserv.export_to_file("test.csv"); 
	std::ifstream fin("D:\\test.csv");
	using std::getline;
	string line;
	getline(fin, line);
	assert(line == "Owner: nume1; Ap. number: 1; Ap. type: tip1; Ap. area: 11");
	getline(fin, line);
	assert(line == "Owner: nume2; Ap. number: 2; Ap. type: tip2; Ap. area: 12");
	getline(fin, line);
	assert(line == "Owner: nume3; Ap. number: 3; Ap. type: tip3; Ap. area: 13");
	getline(fin, line);
	assert(line == "Owner: nume4; Ap. number: 4; Ap. type: tip4; Ap. area: 14");
	fin.close();

	tserv.export_to_file("test.html");
	std::ifstream in("D:\\test.html");
	getline(in, line);
	assert(line == "Owner: nume1; Ap. number: 1; Ap. type: tip1; Ap. area: 11");
	getline(in, line);
	assert(line == "Owner: nume2; Ap. number: 2; Ap. type: tip2; Ap. area: 12");
	getline(in, line);
	assert(line == "Owner: nume3; Ap. number: 3; Ap. type: tip3; Ap. area: 13");
	getline(in, line);
	assert(line == "Owner: nume4; Ap. number: 4; Ap. type: tip4; Ap. area: 14");
	in.close();
}

void Tests::test_undo() const {
	InMemoryRepository trepo;
	NotificationRepo noti;
	Validator tvalid;
	Service tserv(noti, trepo, tvalid);
	int n = 11, m = 10;
	tserv.add_tenant("nume", m, "tip", n);
	m++, n++;
	tserv.add_tenant("numed", m, "tip", n);
	m++, n++;
	tserv.add_tenant("numet", m, "tipt", n);
	m -= 2, n -= 2;
	assert(tserv.get_repo_size() == 3);
	tserv.undo();
	assert(tserv.get_repo_size() == 2);
	tserv.delete_tenant("nume");
	assert(tserv.get_repo_size() == 1);
	tserv.undo();
	assert(tserv.get_repo_size() == 2);
	tserv.edit_tenant("nume", m, "tipnou", n + 100); ///the apartament number never changes (id-like field)
	assert(trepo.find_apartament_by_number(m) == Tenant("nume", m, "tipnou", n + 100));
	tserv.undo();
	assert(trepo.find_apartament_by_number(m) == Tenant("nume", m, "tip", n));
}