#pragma once
#include "repository.h"
#include <algorithm>

class Service
{
	Repository& repo;
public:
	Service(Repository& repository) : repo{repository} {}

	/// <summary>
	/// adauga un nou task in repo
	/// </summary>
	/// <param name="id"></param>
	/// <param name="descriere"></param>
	/// <param name="status"></param>
	/// <param name="programatori"></param>
	void adauga(int id, string descriere, string status, vector<string> programatori);

	/// <summary>
	/// filtreaza repo-ul dupa un programator
	/// </summary>
	/// <param name="nume"></param>
	/// <returns></returns>
	vector<Task> filtruProgramator(const string& nume) const { return repo.find(nume); }

	/// <summary>
	/// filtreaza repo-ul dupa un status
	/// </summary>
	/// <param name="nume"></param>
	/// <returns></returns>
	vector<Task> filtruStatus(const string& status) const { return repo.findStatus(status); }

	/// <summary>
	/// editeaza starea unui task
	/// </summary>
	void editStat(const string& stat, const int& id);

	/// <summary>
	/// ret repo-ul sortat dupa starea task-urilor
	/// </summary>
	/// <returns></returns>
	vector<Task> getAllSorted() { 
		vector<Task> v = repo.getAll(); 
		sort(v.begin(), v.end(), [](const Task& a, const Task& b) {return a.getStare() > b.getStare(); });
		return v;
	}
};

