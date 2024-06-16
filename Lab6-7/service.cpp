#include "service.h"
#include <fstream>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

vector<Tenant> Service::get_all_from_repo() const {
	return repository.get_all();
}

void Service::add_tenant(const string& name, const int& apart, const string& type, const int& area){
	try {
		validator.validate_name(name);
		validator.validate_apart(apart);
		validator.validate_type(type);
		validator.validate_area(area);
		Tenant t(name, apart, type, area);
		repository.store(t);
		undoVector.push_back(std::make_unique<UndoAdauga>(repository, t));
	}
	catch (ValidatorException& e) { throw ServiceException(e.get_message()); }
	catch (RepoException& e) { throw ServiceException(e.get_message()); }}

void Service::edit_tenant(const string& name, const int& apart, const string& type, const int& area) {
	try {
		validator.validate_name(name);
		validator.validate_type(type);
		validator.validate_area(area);
		Tenant t(name, apart, type, area);
		Tenant ten = repository.edit(t);
		undoVector.push_back(std::make_unique<UndoModifica>(repository, ten)); 
	}
	catch (ValidatorException& e) { throw ServiceException(e.get_message()); }
	catch (RepoException& e) { throw ServiceException(e.get_message()); }}

void Service::delete_tenant(const string& name) {
	try {
		validator.validate_name(name); 
		Tenant ten = repository.destroy(name); 
		undoVector.push_back(std::make_unique<UndoSterge>(repository, ten));
	}
	catch (ValidatorException& e) { throw ServiceException(e.get_message()); }
	catch (RepoException& e) { throw ServiceException(e.get_message()); }}

Tenant Service::find_apartament(const int& apart, const string type, const int& area) const {
	try {
		validator.validate_apart(apart);
		validator.validate_type(type);
		validator.validate_area(area);
		Tenant t("", apart, type, area);
		t = repository.find_apartament(t);
		return t;
	}
	catch (ValidatorException& e) { throw ServiceException(e.get_message()); }
	catch (RepoException& e) { throw ServiceException(e.get_message()); }}

vector<Tenant> Service::filter_by_type(const string& type) const {
	try {
		validator.validate_type(type); 
		vector<Tenant> src= get_all_from_repo();  
		vector<Tenant> dest; 
		std::copy_if(src.begin(),src.end(),std::back_inserter(dest),
			[type](const Tenant& t) { return t.get_type() == type; });
		if (dest.empty()) throw ServiceException("-There is no apartament with the given type!\n");
		return dest; 
	}
	catch (ValidatorException& e) { throw ServiceException(e.get_message()); } 
}

vector<Tenant> Service::filter_by_area(const int& area) const {
	try {
		validator.validate_area(area); 
		vector<Tenant> src = get_all_from_repo(); 
		vector<Tenant> dest; 
		std::copy_if(src.begin(), src.end(), std::back_inserter(dest), 
			[area](const Tenant& t) { return t.get_area() == area; });
		if (dest.empty()) throw ServiceException("-There is no apartament with the given area!\n");
		return dest;
	}
	catch (ValidatorException& e) { throw ServiceException(e.get_message()); }
}

vector<Tenant> Service::sort_manager(const int& sort_type) const {
	vector<Tenant> v = get_all_from_repo();
	switch (sort_type) {
	case 1:
		std::sort(v.begin(), v.end(),
			[](Tenant& t1, Tenant& t2) {
				return t1.get_name() < t2.get_name();
			});
		break;
	case 2:
		std::sort(v.begin(), v.end(),
			[](Tenant& t1, Tenant& t2) {
				return t1.get_name() > t2.get_name();
			});
		break;
	case 3:
		std::sort(v.begin(), v.end(),
			[](Tenant& t1, Tenant& t2) {
				return t1.get_area() < t2.get_area();
			});
		break;
	case 4:
		std::sort(v.begin(), v.end(),
			[](Tenant& t1, Tenant& t2) {
				return t1.get_area() > t2.get_area();
			});
		break;
	case 5:
		std::sort(v.begin(), v.end(),
			[](Tenant& t1, Tenant& t2) {
				return (t1.get_type() < t2.get_type()) || ((t1.get_type() == t2.get_type()) && (t1.get_area() < t2.get_area()));
			});
		break;
	case 6:
		std::sort(v.begin(), v.end(),
			[](Tenant& t1, Tenant& t2) {
				return (t1.get_type() > t2.get_type()) || ((t1.get_type() == t2.get_type()) && (t1.get_area() > t2.get_area()));
			});
		break;
	}
	return v;
}

void Service::clear_notification_list(vector<Tenant>& notification_list) const {
	notification_list.clear();
}

void Service::add_apartament_to_notification_list(vector<Tenant>& notification_list, const int& number) const {
	try {
		Tenant apart = repository.find_apartament_by_number(number);
		for(const Tenant& t: notification_list)
			if(t==apart)
				throw ServiceException("-The apartament is already in the notification list!\n");
		notification_list.push_back(apart);
	}
	catch (RepoException& re) { throw ServiceException(re.get_message()); }
}

void Service::add_apartaments_randomly(vector<Tenant>& notification_list, int number) const {
	notification_list.clear();
	vector<Tenant>v = get_all_from_repo();
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed)); //amesteca vectorul v
	for (auto& t : v) {
		if (number == 0) break;
		notification_list.push_back(t);
		number--;
	}
}

void Service::export_to_file(vector<Tenant>& notification_list, const string& file) {
	std::ofstream fout("D:\\"+file);
	for (const Tenant& t : notification_list) fout << t << std::endl;
	fout.close();
}

void Service::create_report(std::map<string, vector<Tenant>>& map) const {
	vector<Tenant> temp = get_all_from_repo();
	for (const Tenant& t : temp)
		map[t.get_type()].push_back(t);
}

void Service::undo() {
	if (undoVector.empty()) throw ServiceException("\n-There is no action to be undone!\n"); 
	undoVector.back()->doUndo();
	//auto  x= std::move(undoVector.back());
	undoVector.pop_back(); 
}