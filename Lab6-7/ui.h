#pragma once
#include "service.h"

class UI{
private:
	Service& service;

	/// <summary>
	/// prints the main menu of the app
	/// </summary>
	void menu() const;

	/// <summary>
	/// prints the sorts menu
	/// </summary>
	void sort_menu() const;

	/// <summary>
	/// prints notifications list menu
	/// </summary>
	void notification_menu() const;

	/// <summary>
	/// reads a command from console
	/// </summary>
	/// <returns>the command as an int</returns>
	const int read_command() const;
	
	/// <summary>
	/// reads a sort command from console
	/// </summary>
	/// <returns>the sort command as an int</returns>
	const int read_sort() const;

	/// <summary>
	/// reads a number from console
	/// </summary>
	/// <param name="str">specifies what number to be read</param>
	/// <returns>the number</returns>
	const int read_number(string str) const;

	/// <summary>
	/// adds a tenant to the app
	/// catches and prints ServiceException if something went wrong
	/// </summary>
	void add_tenant();

	/// <summary>
	/// modifies a tenant in the app
	/// catches and prints ServiceException if something went wrong
	/// </summary>
	void modify_tenant();

	/// <summary>
	/// removes a tenant from the app
	/// catches and prints ServiceException if something went wrong
	/// </summary>
	void remove_tenant();

	/// <summary>
	/// prints tenants in the order they appear in the repo
	/// </summary>
	void print_tenants() const;

	/// <summary>
	/// searches prints an apartament
	/// catches and prints ServiceException if something went wrong
	/// </summary>
	void search_apartament() const;

	/// <summary>
	/// filters the list of apartaments by type and prints it
	/// catches and prints ServiceException if something went wrong
	/// </summary>
	void print_by_type() const;

	/// <summary>
	/// filters the list of apartaments by surface and prints it
	/// catches and prints ServiceException if something went wrong
	/// </summary>
	void print_by_area() const;

	/// <summary>
	/// sorts the list of apartaments by a criteria and prints it
	/// </summary>
	void print_sorted() const;

	/// <summary>
	/// prints all the alems of a vector
	/// </summary>
	/// <param name="v">a Tenants vector to be printed</param>
	void print_all(vector<Tenant>& v) const;

	/// <summary>
	/// deletes all tenants
	/// </summary>
	void erase_all();

	/// <summary>
	/// notification list menu
	/// </summary>
	void notification_list() const;

	/// <summary>
	/// adds to the notif list an apartament
	/// </summary>
	/// <param name="notification_list"></param>
	void add_apartament(vector<Tenant>& notification_list) const;

	/// <summary>
	/// adds to the notif list n apartaments randomly
	/// </summary>
	/// <param name="notification_list"></param>
	void add_apartaments_random(vector<Tenant>& notification_list) const;

	/// <summary>
	/// exports the notification list to a user-given html/csv file
	/// </summary>
	/// <param name="notification_list"></param>
	void export_list(vector<Tenant>& notification_list) const;

	/// <summary>
	/// prints a report of apartaments by types
	/// </summary>
	void type_report() const;

	void make_undo() const;

public:
	UI(Service& serv) : service{serv} { }

	/// <summary>
	/// no copies of UI are allowed
	/// </summary>
	/// <param name="ot">other UI object</param>
	UI(const UI& ot) = delete;

	/// <summary>
	/// runs the app...
	/// </summary>
	void run_app();
};

