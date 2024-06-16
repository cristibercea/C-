#include "ui.h"
#include <iostream>
using std::cout;
using std::cin;
using std::getline;

void UI::menu() const {
	cout << "\n	Commands:\n";
	cout << " 0 - Exit App\n" << " 1 - Add new tenant\n" << " 2 - Edit existing tenant\n" << " 3 - Delete existing tenant\n" << " 4 - Show all tenants\n" << " 5 - Search apartament\n" << " 6 - Filter apartaments by type\n" << " 7 - Filter apartaments by area\n" << " 8 - Sort apartaments by...\n" <<" 9 - Create a notification list...\n"<< "10 - Report spartaments by type \n"<< "11 - Undo\n";
}

void UI::sort_menu() const {
	cout << "\n	Sort by...\n";
	cout << "0 - Abort sorting\n" << "1 - owner name, ascending\n" << "2 - owner name, descending\n" << "3 - apartament surface, ascending\n" << "4 - apartament surface, descending\n" << "5 - apartament type and surface, ascending\n" << "6 - apartament type and surface, descending\n";
}

void UI::notification_menu() const{
	cout << "\n	Notification List Manager\n";
	cout << "0 - Exit notification list menu(the list will be destroyed)\n" << "1 - clear list\n" << "2 - add apartament by number\n" << "3 - add a given number of random apartaments(overrides current state of the list if not empty)\n" << "4 - export list in a CSV/HTML file\n";
}

const int UI::read_command() const {
	string read;
	int comm=99;
	while (true) {
		menu();
		read = "";
		cout << ">Insert command: ";
		cin >> read;
		if (read.size() > 2) { 
			cout << "\n-Invalid command!\n";
			continue; 
		}
		if ((read.size() == 1 && !isdigit(read[0])) || (read.size() == 2 && !isdigit(read[1]))) {
			cout << "\n-Invalid command!\n";
			continue; 
		}
		if (read.size() == 1) {
			comm = read[0] - '0';
		}
		else if (read.size() == 2) {
			comm = 10*(read[0] - '0') + read[1] - '0';
		}
		
		if (comm > 11) { 
			cout << "\n-Invalid command!\n";
			continue; 
		}
		return comm;
	}
}

const int UI::read_sort() const {
	string read;
	int comm;
	while (true) {
		sort_menu(); 
		read = ""; 
		cout << ">Insert sort type: "; 
		cin >> read; 
		if (read.size() != 1) { 
			cout << "\n-Invalid sort type!\n"; 
			continue;  
		} 
		if (!isdigit(read[0])) { 
			cout << "\n-Invalid sort type!\n"; 
			continue; 
		} 
		comm = read[0] - '0'; 
		if (comm > 6) { 
			cout << "\n-Invalid sort type!\n"; 
			continue; 
		} 
		return comm; 
	} 
}

const int UI::read_number(string str) const {
	string read;
	int n,ok;
	while (true) {
		n = 0;
		ok = 1;
		read = "";
		cout << ">Insert the "<< str <<": ";
		cin >> read;
		if (read.size() < 1) {
			cout << "\n-Invalid " << str << "!\n";
			continue;
		}
		for(char &c : read)
			if (!isdigit(c)) {
				cout << "\n-Invalid " << str << "!\n";
				ok = 0;
				break;
			}
			else n = n * 10 + c - '0';
		if (!ok) continue;
		return n;
	}
}

void UI::run_app(){
	while (true) {
		int comm = read_command();
		switch (comm){
		case 0:
			return;
		case 1:
			add_tenant();
			break;
		case 2:
			modify_tenant();
			break;
		case 3:
			remove_tenant();
			break;
		case 4:
			print_tenants();
			break;
		case 5:
			search_apartament();
			break;
		case 6:
			print_by_type();
			break;
		case 7:
			print_by_area();
			break;
		case 8:
			print_sorted();
			break;
		case 9:
			notification_list();
			break;
		case 10:
			type_report();
			break;
		case 11:
			make_undo();
			break;
		}
	}
}

void UI::add_tenant(){
	string name, type;
	int c;
	cout << ">Insert tenant name: ";
	c=getchar();
	getline(cin, name);
	int apart = read_number("apartament number");
	cout << ">Insert apartament type: ";
	c=getchar();
	getline(cin, type);
	int area = read_number("area");
	try {
		service.add_tenant(name, apart, type, area);
		cout << "\n-Tenant added successfully!\n";
	}
	catch (ServiceException& e) { cout << "\n-Errors:\n" << e.get_message(); }
}

void UI::modify_tenant(){
	string name, type;
	int c;
	cout << ">Insert tenant name: "; 
	c = getchar();
	getline(cin, name); 
	cout << ">Insert new apartament type: "; 
	getline(cin, type); 
	int area = read_number("new area"); 
	try { 
		service.edit_tenant(name, 0, type, area); 
		cout << "\n-Tenant edited successfully!\n";
	} 
	catch (ServiceException& e) { cout << "\n-Errors:\n" << e.get_message(); } 
}

void UI::remove_tenant(){
	if (service.get_all_from_repo().empty()) { cout << "\nThere are no tenants saved!\n"; return; }
	string name;
	int c;
	cout << ">Insert tenant name: ";
	c = getchar();
	getline(cin, name);
	try {
		service.delete_tenant(name);
		cout << "\n-Tenant deleted successfully!\n";
	}
	catch (ServiceException& e) { cout << "\n-Errors:\n" << e.get_message(); }
}

void UI::print_tenants() const {
	vector<Tenant> v = service.get_all_from_repo();
	if (v.empty()) cout << "\nThere are no tenants saved!\n";
	else {
		cout << "\n	Tenants List:\n";
		print_all(v);
	}
}

void UI::search_apartament() const {
	if (service.get_all_from_repo().empty()) { cout << "\nThere are no apartaments saved!\n"; return; }
	string type;
	int c;
	int apart = read_number("apartament number");
	cout << ">Insert apartament type: ";
	c = getchar();
	getline(cin, type);
	int area = read_number("area");
	try {
		cout << "\n-Matched apartament: " << service.find_apartament(apart, type, area) << " (sq meters)" << std::endl;
	}
	catch (ServiceException& e) { cout << std::endl << e.get_message(); }
}

void UI::print_by_type() const {
	if (service.get_all_from_repo().empty()) { cout << "\nThere are no apartaments saved!\n"; return; }
	string type; 
	int c; 
	cout << ">Insert apartament type: ";
	c = getchar(); 
	getline(cin, type); 
	try {
		vector<Tenant> v = service.filter_by_type(type);
		cout << "\n-Matched apartaments:\n";
		print_all(v); 
	}
	catch (ServiceException& e) { cout << std::endl << e.get_message(); }
}

void UI::print_by_area() const {
	if (service.get_all_from_repo().empty()) { cout << "\nThere are no apartaments saved!\n"; return; }
	int area = read_number("area");
	try {
		vector<Tenant> v = service.filter_by_area(area); 
		cout << "\n-Matched apartaments:\n";
		print_all(v);
	}
	catch (ServiceException& e) { cout << std::endl << e.get_message(); }
}

void UI::print_sorted() const {
	if (service.get_all_from_repo().empty()) { cout << "\nThere are no apartaments saved!\n"; return; }
	int sort_type = read_sort();
	if (sort_type == 0) return;
	cout << "\n-Sorted apartaments:\n";
	vector<Tenant> v = service.sort_manager(sort_type);
	print_all(v);
}

void UI::print_all(vector<Tenant>& v) const{
	int i = 1;
	for (auto& el : v) { cout << "  " << i << ". " << el << " (sq meters)" << std::endl; i++; }
}

void UI::add_apartament(vector<Tenant>& notification_list) const {
	if (notification_list.size() == service.get_repo_size()) {
		cout << "\nAll apartaments saved have been added to this list!\n";
		return;
	}
	int apart = read_number("apartament number");
	try {
		service.add_apartament_to_notification_list(notification_list, apart);
	} 
	catch(ServiceException& e){ cout << std::endl << e.get_message(); } 
	
}

void UI::add_apartaments_random(vector<Tenant>& notification_list) const {
	int number = read_number("number of apartaments to be added");
	while (number > service.get_repo_size()) {
		cout << "\nThere are not enough apartaments saved!\n";
		number = read_number("number of apartaments to be added");
	}
	service.add_apartaments_randomly(notification_list, number);
}

void UI::export_list(vector<Tenant>& notification_list) const {
	if (notification_list.size() == service.get_repo_size()) {
		cout << "\nNotification list is empty!\n";
		return;
	}
	string file;
	cout << "\n>Insert file name(with extensions: \".html\", \".csv\"): ";
	cin >> file;
	while (true) {
		if (file.size() > 4 && file[file.size() - 4] == '.' && file[file.size() - 3] == 'c' && file[file.size() - 2] == 's' && file[file.size() - 1] == 'v')
			break;
		if (file.size() > 5 && file[file.size() - 5] == '.' && file[file.size() - 4] == 'h' && file[file.size() - 3] == 't' && file[file.size() - 2] == 'm' && file[file.size() - 1] == 'l')
			break;
		cout << "\nInvalid file name!\n";
		cout << "\n>Insert file name(with extensions: \".html\", .\"csv\"): ";
		cin >> file;
	}
	service.export_to_file(notification_list,file);
	
}

void UI::type_report() const{
	if (service.get_all_from_repo().empty()) { cout << "\nThere are no apartaments saved!\n"; return; }
	std::map<string, vector<Tenant>> map;
	service.create_report(map);
	cout << "\nApartaments Report:\n";
	for (auto& p : map) {
		cout << "   Type: " << p.first << ";  Found: " << std::endl;
		for (auto& t : p.second) {
			cout << " -" << t<<std::endl;
		}
	}
}

void UI::make_undo() const{ 
	try { service.undo(); cout << "\nUndo succeeded!\n"; }
	catch (ServiceException& se) { cout << se.get_message(); }
}

void UI::notification_list() const {
	vector<Tenant> notification_list;
	if (service.get_repo_size()==0) { cout << "\nThere are no apartaments saved!\n"; return; } 
	while (1) {
		notification_menu();
		string str;
		int comm;
		cout << ">Insert command: ";
		cin >> str;
		while (str.size() != 1) {
			cout << "\n-Invalid command!\n";
			cout << ">Insert command: ";
			cin >> str;
		}
		comm = str[0] - '0';
		switch (comm) {
		case 0:
			return;
		case 1:
			service.clear_notification_list(notification_list);
			break;
		case 2:
			add_apartament(notification_list);
			break;
		case 3:
			add_apartaments_random(notification_list);
			break;
		case 4:
			export_list(notification_list);
			break;
		default:
			cout << "\n-Invalid command!\n";
		}
		cout << std::endl << " ->Number of tenants in notification list: " << notification_list.size() << std::endl;
	}
}

