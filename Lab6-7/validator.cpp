#include "validator.h"

void Validator::validate_name(const string& name) const {
	string err="";
	char s[] = "1234567890@#,!$%^*()[]=+~|\\<>:;&\"";
	if (name.size() < 3) err += "The tenant name must have at least 3 characters!\n";
	if (!isalpha(name[0])) err += "The tenant name must start with a letter!\n";
	for (const char& c : name)
		if (strchr(s, c) != NULL) {
			err += "The tenant name must only contain letters, spaces and '-'!\n";
			break;
		}
	if(!err.empty()) throw ValidatorException(err);
}

void Validator::validate_apart(const int& apart) const {
	string err="";
	if (apart <= 0) err += "The apartament number must be a positive number!\n";
	if (!err.empty()) throw ValidatorException(err);
}

void Validator::validate_type(const string& type) const {
	string err="";
	char s[] = "1234567890@#,!$%^*()[]=+~|\\<>:;&\"";
	if (type.size()<3) err += "The apartament type must have at least 3 characters!\n";
	if (!isalpha(type[0])) err += "The apartament type must start with a letter!\n";
	for (const char& c : type)
		if (strchr(s, c) != NULL) {
			err += "The apartament type must only contain letters, spaces and '-'!\n";
			break;
		}
	if (!err.empty()) throw ValidatorException(err);
}

void Validator::validate_area(const int& area) const {
	string err="";
	if (area <= 5) err += "The area must be a positive number, greater than 5!\n";
	if (!err.empty()) throw ValidatorException(err);
}
