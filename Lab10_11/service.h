#pragma once
#include "repository.h"
#include "validator.h"
#include "undo.h"
#include <map>

class Service {
private:
	Repository& repository;
	NotificationRepo& notification;
	Validator& validator;
	vector<std::unique_ptr<ActiuneUndo>> undoVector;
public:
	Service(Service& s) = delete;
	Service operator=(const Service& s) = delete;
	Service(NotificationRepo& n, Repository& r, Validator& v) : notification{ n },repository { r }, validator{ v } {}

	/// <summary>
	/// returns all tenants from the repo
	/// </summary>
	/// <returns>a copy of the repo</returns>
	vector<Tenant> get_all_from_repo() const;

	/// <summary>
	/// gets the size of the repo
	/// </summary>
	/// <returns>size of the repo</returns>
	int get_repo_size() const { return repository.get_size(); };

	/// <summary>
	/// creates and adds a new tenant from the repo
	/// catches ValidatorException if any of the data is invalid
	/// catches RepositoryException if the Tenant is a duplicate
	/// throws ServiceException if catches any of the above
	/// </summary>
	/// <param name="name">owner name</param>
	/// <param name="apart">apartament number</param>
	/// <param name="type">apartament type</param>
	/// <param name="area">apartament surface</param>
	/// <returns>true, if stored</returns>
	void add_tenant(const string& name, const int& apart, const string& type, const int& area);

	/// <summary>
	/// edits tenant in the repo
	/// catches ValidatorException if any of the data is invalid
	/// catches RepositoryException if the Tenant is inexistent
	/// throws ServiceException if catches any of the above
	/// </summary>
	/// <param name="name">owner name</param>
	/// <param name="apart">apartament number</param>
	/// <param name="type">apartament type</param>
	/// <param name="area">apartament surface</param>
	/// <returns>true, if edited; false, else</returns>
	void edit_tenant(const string& name, const int& apart, const string& type, const int& area);

	/// <summary>
	/// removes by name a tenant from the repo
	/// catches ValidatorException if the name is invalid
	/// catches RepositoryException if the Tenant is inexistent
	/// throws ServiceException if catches any of the above
	/// </summary>
	/// <param name="name">owner name</param>
	/// <returns>true, if deleted; false, else</returns>
	void delete_tenant(const string& name);

	/// <summary>
	/// finds an apartament by number, type and surface and returns it
	/// catches ValidatorException if params are invalid
	/// catches RepositoryException if the Tenant is inexistent
	/// throws ServiceException if catches any of the above
	/// </summary>
	/// <param name="apart">apartament number</param>
	/// <param name="type">apartament type</param>
	/// <param name="area">apartament surface</param>
	Tenant find_apartament(const int& apart) const;

	/// <summary>
	/// makes a copy of the repo, filters it by apartament type and returns the filtered vector
	/// catches ValidatorException if param is invalid
	/// throws ServiceException if catches ValidatorException or if the filtered vector is empty
	/// </summary>
	/// <param name="type">apartament type</param>
	vector<Tenant> filter_by_type(const string& type) const;

	/// <summary>
	/// makes a copy of the repo, filters it by apartament surface and returns the filtered vector
	/// catches ValidatorException if param is invalid
	/// throws ServiceException if catches ValidatorException or if the filtered vector is empty
	/// </summary>
	/// <param name="area">apartament surface</param>
	vector<Tenant> filter_by_area(const int& area) const;

	/// <summary>
	/// makes a copy of the repo, sorts it in a specified way and returns the sorted vector
	/// </summary>
	/// <param name="sort_type">represents what sort should be made</param>
	vector<Tenant> sort_manager(const int& sort_type) const;

	/// <summary>
	/// empties the notification list
	/// </summary>
	/// <param name="notification_list"></param>
	void clear_notification_list();

	/// <summary>
	/// adds to notif list an apartament from repo with given number
	/// </summary>
	/// <param name="notification_list"></param>
	void add_apartament_to_notification_list(const int& number);

	/// <summary>
	/// adds a number of apartaments from the repo to the notif list
	/// </summary>
	/// <param name="notification_list"></param>
	void add_apartaments_randomly(int number);

	/// <summary>
	/// exports the notification list current state in a file 
	/// </summary>
	/// <param name="notification_list"></param>
	/// <param name="file"></param>
	void export_to_file(const string& file);

	/// <summary>
	/// gets notification list
	/// </summary>
	/// <returns>the notif vector</returns>
	vector<Tenant> get_notif_list() const { return notification.get_all(); }

	/// <summary>
	/// creates a report with the amount of apartaments with a certain type type
	/// </summary>
	void create_report(std::map<string, vector<Tenant>>& map) const;

	/// <summary>
	/// makes the undo until not possible
	/// </summary>
	void undo();

	/// <summary>
	/// adds the given observer to the list of observers
	/// </summary>
	/// <param name="obs">pointer to the observer to be added</param>
	void addObserver(Observer* obs) { notification.addObserver(obs); }

	/// <summary>
	/// removes a given observer from the list of observers
	/// </summary>
	/// <param name="obs">pointer to the observer to be deleted</param>
	void removeObserver(Observer* obs) { notification.removeObserver(obs); }
};

class ServiceException {
private:
	string message;
public:
	ServiceException(const string& mess) : message{ mess } { }

	/// <summary>
	/// gets exception's error message
	/// </summary>
	/// <returns>string</returns>
	const string& get_message() const { return message; }
};