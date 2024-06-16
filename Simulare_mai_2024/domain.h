#pragma once
#include <string>
using std::string;
class Stock
{
private:
	string id, name;
	int rate;
	float price;
public:
	Stock(string i, string num, float pric, int r) :rate{ r }, id{ i }, name{ num }, price{ pric } {}
	string get_id() const { return id; } //gets id
	string get_name() const { return name; } //gets name
	int get_rate() const { return rate; } //gets rate
	float get_price() const { return price; } //gets price

	bool operator==(const Stock& o) {
		return id == o.get_id();
	}

	bool operator!=(const Stock& o) {
		return !(*this==o);
	}

};

