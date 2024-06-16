#pragma once
#include <string>
using std::string;

class doctor{
	string nume, prenume, cnp, sectie;
	int status;

public:
	doctor(const string& cnp, const string& nume, const string& prenume, const string& sectie, const int& s) : nume{ nume }, prenume{ prenume }, cnp{ cnp }, sectie{ sectie }, status{ s } {}
	int get_status() const noexcept { return status; }
	string get_nume() const noexcept { return nume; }
	string get_prenume() const noexcept { return prenume; }
	string get_cnp() const noexcept { return cnp; }
	string get_sectie() const noexcept { return sectie; }

	bool operator==(const doctor& ot) {
		return (nume == ot.get_nume()&& prenume == ot.get_prenume()&& cnp == ot.get_cnp()&& sectie == ot.get_sectie());
	}

	bool operator!=(const doctor& ot) {
		return !(*this == ot);
	}
};

