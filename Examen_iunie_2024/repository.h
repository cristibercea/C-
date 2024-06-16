#pragma once
#include "domain.h"
#include "Observer.h"

class Repository:public Observable
{
	string file;
	vector<Task> rep;

	/// <summary>
	/// preia elem din file in repo
	/// </summary>
	void loadFromFile();

	/// <summary>
	/// salveaza elem din repo in file
	/// </summary>
	void storeToFile();
public:
	Repository(string filename) : file{ filename } {
		loadFromFile();
	}

	/// <summary>
	/// salveaza taskul t in repo
	/// </summary>
	/// <param name="t"></param>
	void store(const Task& t);

	/// <summary>
	/// editeaza starea unui obj
	/// </summary>
	/// <param name="stat"></param>
	/// <param name="id"></param>
	void edit(const string& stat, const int& id);

	/// <summary>
	/// gaseste task-uri dupa un programator
	/// </summary>
	/// <param name="nume"></param>
	/// <returns></returns>
	vector<Task> find(const string& nume) const;
	
	/// <summary>
	/// gaseste task-uri dupa un status
	/// </summary>
	/// <param name="nume"></param>
	/// <returns></returns>
	vector<Task> findStatus(const string& status) const;

	/// <summary>
	/// ret elem din repo
	/// </summary>
	/// <returns></returns>
	vector<Task> getAll() const { return rep; }
};

