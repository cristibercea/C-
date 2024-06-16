#include "repository.h"
#include <fstream>

void Repository::loadFromFile()
{
	std::ifstream in(file);
	if (!in.is_open()) throw std::exception("nu s-a putut deschide file-ul");

	while (!in.eof()) {
		int id, n;
		string des, str;
		vector<string> prg;
		string tmp;
		in >> id;
		in.get();
		std::getline(in, des);
		std::getline(in, str);
		in >> n;
		in.get();
		for (int i = 0; i < n; i++) {
			std::getline(in, tmp);
			prg.push_back(tmp);
		}
		if (in.eof()) break;

		Task t(id, des,str,prg);
		rep.push_back(t);
	}

	in.close();
}

void Repository::storeToFile()
{
	std::ofstream out(file);

	for (const auto& t : rep) {
		out << t.getId() << std::endl;
		out << t.getDescriere()<< std::endl;
		out << t.getStare() << std::endl;
		vector<string> v = t.getProgramatori();
		out << v.size() << std::endl;
		for(const auto& el : v) out << el << std::endl;
	}

	out.close();
}

void Repository::store(const Task& t)
{
	for (const auto& e : rep) if (t.getId() == e.getId()) throw std::exception("Id deja existent in app!");
	rep.push_back(t);
	storeToFile();
	//notify()
}

void Repository::edit(const string& stat, const int& id)
{
	auto it = find_if(rep.begin(), rep.end(), [&id](const Task& t) {return t.getId() == id; });
	it->setStare(stat);
	storeToFile();
	//notify();
}

vector<Task> Repository::find(const string& nume) const {
	vector<Task> v;
	for (const auto& e : rep) {
		for (const string& n : e.getProgramatori())
			if (strstr(n.c_str(), nume.c_str()) != NULL) {
				v.push_back(e);
				break;
			}
	}
	return v;
}

vector<Task> Repository::findStatus(const string& status) const
{
	vector<Task> v;
	for (const auto& e : rep) if (e.getStare() == status) v.push_back(e);
	return v;
}
