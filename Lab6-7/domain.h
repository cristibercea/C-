#pragma once
#include <string>
#include <ostream>
using std::string;
using std::ostream;

class Tenant {
private:
	string name, type;
	int apartament, area;

public:
	Tenant() :apartament{ -1 }, area{ -1 }{}

	/// <summary>
	/// main constructor
	/// </summary>
	/// <param name="nam">string</param>
	/// <param name="ap">int</param>
	/// <param name="tp">string</param>
	/// <param name="ar">int</param>
	Tenant(const string nam, const int ap, const string tp, const int ar) :name{ nam }, apartament{ ap }, type{ tp }, area{ ar } {}

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">other Tenant object</param>
	Tenant(const Tenant& other) :name{ other.name }, apartament{ other.apartament }, type{ other.type }, area{ other.area } { }

	/// <summary>
	/// gets the name of the tenant
	/// </summary>
	/// <returns>string</returns>
	const string& get_name() const;

	/// <summary>
	/// gets the type of the apartament
	/// </summary>
	/// <returns>string</returns>
	const string& get_type() const;

	/// <summary>
	/// gets the number of the apartament
	/// </summary>
	/// <returns>int</returns>
	const int& get_apartament() const;

	/// <summary>
	/// gets the area of the apartament
	/// </summary>
	/// <returns>int</returns>
	const int& get_area() const;

	/// <summary>
	/// sets the area of the apartament
	/// </summary>
	/// <param name="ar"></param>
	void set_area(const int ar);

	/// <summary>
	/// sets the type of the apartament
	/// </summary>
	/// <param name="ty"></param>
	void set_type(const string ty);

	/// <summary>
	/// equal override
	/// </summary>
	bool operator==(const Tenant& other) const;

	bool operator!=(const Tenant& other) const;

	void operator=(const Tenant& other);
	
	/// <summary>
	/// out stream override
	/// </summary>
	friend std::ostream& operator<<(ostream& os, const Tenant& obj);
};
