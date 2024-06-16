#pragma once
#include <vector>
#include "domain.h"
using std::vector;

/// <summary>
/// fully abstract Repository class
/// </summary>
class Repository {
public:
	Repository() = default;
	Repository(const Repository& rep) = delete;
	virtual ~Repository() = default;

	/// <summary>
	/// gets all the elements in the repo
	/// </summary>
	/// <returns>vector</returns>
	virtual vector<Tenant> get_all() const = 0;

	/// <summary>
	/// gets the size of the repo
	/// </summary>
	/// <returns>size of the repo</returns>
	virtual int get_size() const = 0;

	/// <summary>
	/// finds an apartament by number, type and surface
	/// throws RepositoryException if inexistent
	/// </summary>
	/// <param name="t">Tenant, with an empty name</param>
	/// <returns>wanted apartament's details</returns>
	virtual const Tenant find_apartament(const Tenant& t) const = 0;

	/// <summary>
	/// finds an apartament by a given number
	/// </summary>
	/// <param name="number">the number of the apart</param>
	/// <returns>wanted apartament</returns>
	virtual const Tenant find_apartament_by_number(const int& number) const = 0; 

	/// <summary>
	/// finds a tenant name
	/// </summary>
	/// <param name="name">owner name</param>
	/// <returns>wanted tenant, or an invalid tenant</returns>
	virtual const Tenant find_name(const string name) const = 0;

	/// <summary>
	/// stores a tenant in the repo
	/// throws RepositoryException if already existent
	/// </summary>
	/// <param name="t"></param>
	/// <returns>true, if saved</returns>
	virtual void store(const Tenant& t) = 0;

	/// <summary>
	/// edits a tenant in the repo
	/// throws RepositoryException if inexistent
	/// </summary>
	/// <param name="t"></param>
	/// <returns>true, if edited; false, else</returns>
	virtual Tenant edit(const Tenant& t) = 0;

	/// <summary>
	/// deletes a tenant from the repo
	/// throws RepositoryException if inexistent
	/// </summary>
	/// <param name="name"></param>
	/// <returns>true, if deleted; false, else</returns>
	virtual Tenant destroy(const string name) = 0;
};


class InMemoryRepository: public Repository{
private:
	vector<Tenant> repo;
public:
	InMemoryRepository() = default;
	InMemoryRepository(const InMemoryRepository& rep) = delete;
	virtual ~InMemoryRepository() = default;

	/// <summary>
	/// gets all the elements in the repo
	/// </summary>
	/// <returns>vector</returns>
	vector<Tenant> get_all() const override { return repo; }

	/// <summary>
	/// gets the size of the repo
	/// </summary>
	/// <returns>size of the repo</returns>
	int get_size() const override { return (int)repo.size(); };

	/// <summary>
	/// finds an apartament by number, type and surface
	/// throws RepositoryException if inexistent
	/// </summary>
	/// <param name="t">Tenant, with an empty name</param>
	/// <returns>wanted apartament's details</returns>
	const Tenant find_apartament(const Tenant& t) const override;

	/// <summary>
	/// finds an apartament by a given number
	/// </summary>
	/// <param name="number">the number of the apart</param>
	/// <returns>wanted apartament</returns>
	const Tenant find_apartament_by_number(const int &number) const override;

	/// <summary>
	/// finds a tenant name
	/// </summary>
	/// <param name="name">owner name</param>
	/// <returns>wanted tenant, or an invalid tenant</returns>
	const Tenant find_name(const string name) const override;

	/// <summary>
	/// stores a tenant in the repo
	/// throws RepositoryException if already existent
	/// </summary>
	/// <param name="t"></param>
	/// <returns>true, if saved</returns>
	virtual void store(const Tenant& t) override;

	/// <summary>
	/// edits a tenant in the repo
	/// throws RepositoryException if inexistent
	/// </summary>
	/// <param name="t"></param>
	/// <returns>true, if edited; false, else</returns>
	virtual Tenant edit(const Tenant& t) override;

	/// <summary>
	/// deletes a tenant from the repo
	/// throws RepositoryException if inexistent
	/// </summary>
	/// <param name="name"></param>
	/// <returns>true, if deleted; false, else</returns>
	virtual Tenant destroy(const string name) override;
};


class FileRepository : public InMemoryRepository {
private:
	string file; //the name of the repo file
	
	/// <summary>
	/// loads data from file
	/// </summary>
	void loadFromFile();

	/// <summary>
	/// stores all data form the repo into a file
	/// </summary>
	void storeInFile() const;

public:
	FileRepository(const string& name) : InMemoryRepository(), file{ name } {
		loadFromFile(); 
	}
	
	void store(const Tenant& t) override {
		InMemoryRepository::store(t);
		storeInFile();
	}

	Tenant edit(const Tenant& t) override {
		Tenant edited = InMemoryRepository::edit(t);
		storeInFile();
		return edited;
	}

	Tenant destroy(const string name) override {
		Tenant destroyed = InMemoryRepository::destroy(name); 
		storeInFile();
		return destroyed; 
	}
};


class RepoException {
private:
	string message;
public:
	RepoException(const string& mess) : message{ mess } { }

	/// <summary>
	/// gets exception's error message
	/// </summary>
	/// <returns>string</returns>
	const string& get_message() const { return message; }
};