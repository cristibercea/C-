#pragma once
#include <string>

using std::string;
class Validator {
public:
	Validator(const Validator& val) = delete;

	Validator() = default;

	/// <summary>
	/// validates the name of an owner
	/// throws ValidatorException if invalid
	/// </summary>
	/// <param name="name">string</param>
	void validate_name(const string& name) const;

	/// <summary>
	/// validates the number of an apartament
	/// throws ValidatorException if invalid
	/// </summary>
	/// <param name="apart">int</param>
	void validate_apart(const int& apart) const;

	/// <summary>
	/// validates the type of an apartament
	/// throws ValidatorException if invalid
	/// </summary>
	/// <param name="type">string</param>
	void validate_type(const string& type) const;

	/// <summary>
	/// validates the area of an apartament
	/// throws ValidatorException if invalid
	/// </summary>
	/// <param name="area">int</param>
	void validate_area(const int& area) const;
};

class ValidatorException {
private:
	string message;
public:
	ValidatorException(const string& mess) : message{ mess } { }

	/// <summary>
	/// gets exception's error message
	/// </summary>
	/// <returns>string</returns>
	const string& get_message() const { return message; }
};


