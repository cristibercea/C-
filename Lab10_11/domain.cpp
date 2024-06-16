#include "domain.h"
using std::string;

const string& Tenant::get_name() const { return name; }

const string& Tenant::get_type() const { return type; }

const int& Tenant::get_apartament() const { return apartament; }

const int& Tenant::get_area() const { return area; }

void Tenant::set_area(const int ar) { area = ar; }

void Tenant::set_type(const string ty) { type = ty; }

bool Tenant::operator==(const Tenant& other) const {
	if (this->name == other.name && this->apartament == other.apartament && this->type == other.type && this->area == other.area)
		return true;
	return false;
}

bool Tenant::operator!=(const Tenant& other) const {
	return !(*this == other);
}

void Tenant::operator=(const Tenant& other) {
	if (this != &other) {
		this->name = other.name;
		this->apartament = other.apartament;
		this->type = other.type;
		this->area = other.area;
	}
}

std::ostream& operator<<(std::ostream& os, const Tenant& obj) {
	return os << "Owner: " << obj.get_name() << "; Ap. number: " << obj.get_apartament() << "; Ap. type: " << obj.get_type() << "; Ap. area: " << obj.get_area();
}
