#include "repository.h"
#include <fstream>

const Tenant InMemoryRepository::find_apartament(const Tenant& t) const {
	vector<Tenant> src = get_all();
	auto it = std::find_if(src.begin(), src.end(),
		[t](const Tenant tenant) {return tenant.get_apartament() == t.get_apartament();});
	if (it == src.end())
		throw RepoException("The apartament does not exist!\n");
	return *it;
}

const Tenant InMemoryRepository::find_name(const string name) const {
	Tenant invalid("", -1, "", -1);
	vector<Tenant> src = get_all();
	auto it = std::find_if(src.begin(), src.end(),
		[name](const Tenant tenant) {return tenant.get_name() == name; });
	if (it == src.end())
		return invalid;
	return *it;
}

const Tenant InMemoryRepository::find_apartament_by_number(const int& number) const {
	vector<Tenant> src = get_all();
	auto it = std::find_if(src.begin(), src.end(),
		[number](const Tenant tenant) {return tenant.get_apartament() == number; });
	if (it == src.end())
		throw RepoException("The apartament does not exist!\n");
	return *it;
}

void InMemoryRepository::store(const Tenant& t) {
	for (const Tenant& tenant : repo)
		if (tenant.get_apartament() == t.get_apartament())
			throw RepoException("A tenant already exists in given apart!\n");
		else if (tenant.get_name() == t.get_name())
			throw RepoException("A tenant with this name already exists!\n");
	repo.push_back(t);
}

Tenant InMemoryRepository::edit(const Tenant& t) {
	if (find_name(t.get_name()) == Tenant("", -1, "", -1)) throw RepoException("The tenant does not exist!\n");
	Tenant temp;
	for (Tenant& tenant : repo)
		if (tenant.get_name() == t.get_name()) {
			temp = tenant;
			tenant.set_area(t.get_area());
			tenant.set_type(t.get_type());
		}
	return temp;
}

Tenant InMemoryRepository::destroy(const string name) {
	if (find_name(name) == Tenant("", -1, "", -1)) throw RepoException("The tenant does not exist!\n");
	Tenant t = find_name(name);
	auto it = std::remove_if(repo.begin(), repo.end(),
		[name](const Tenant tenant) {return tenant.get_name() == name; }
	);
	repo.erase(it, repo.end());
	return t;
}

void FileRepository::loadFromFile() {
	std::ifstream fin(file);
	if (!fin.is_open()) throw RepoException("Unable to open " + file);

	while (!fin.eof()) {
		string name(""), type("");
		int apartament, area;
		getline(fin, name);
		fin >> apartament;
		fin.get();
		getline(fin, type);
		fin >> area;
		fin.get(); 
		if (fin.eof()) break;
		Tenant ten(name, apartament, type, area);
		InMemoryRepository::store(ten);
	}

	fin.close();
}

void FileRepository::storeInFile() const {
	std::ofstream fout(file);
	if (!fout.is_open()) throw RepoException("Unable to open " + file);

	vector<Tenant> v = InMemoryRepository::get_all();
	for (const Tenant& t : v) {
		fout << t.get_name() << std::endl;
		fout << t.get_apartament() << std::endl;
		fout << t.get_type() << std::endl;
		fout << t.get_area() << std::endl;
	}

	fout.close();
}
