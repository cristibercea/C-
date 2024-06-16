#pragma once
#include <string>
#include <vector>
using std::string, std::vector;
class Task
{
	int id;
	string descriere, stare;
	vector<string> programatori;
public:
	Task(int id, string descriere, string stare, vector<string> programatori) :id{ id }, descriere{descriere}, stare{ stare }, programatori{ programatori } {}
	int getId() const { return id; }
	string getStare() const { return stare; }
	void setStare(const string& st) { stare = st; }
	string getDescriere() const { return descriere; }
	vector<string> getProgramatori() const { return programatori; }
	bool operator==(const Task& t) {
		return id == t.getId() && descriere == t.getDescriere() && stare == t.getStare() && programatori == t.getProgramatori();
	}
	bool operator!=(const Task& t) {
		return !(*this==t);
	}
};

