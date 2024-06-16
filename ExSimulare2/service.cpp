#include "service.h"
#include <algorithm>

vector<Tricou> Service::sortAll()
{
	vector<Tricou> sorted = getAll();
	
	std::sort(sorted.begin(), sorted.end(), [](const Tricou& t1, const Tricou& t2) {
		int nr1 = 0, nr2 = 0;
		if (t1.get_marime() == "S") nr1 = 6;
		else if (t1.get_marime() == "M") nr1 = 9;
		else if (t1.get_marime() == "L") nr1 = 12;
		else if (t1.get_marime() == "XL") nr1 = 15;
		if (t2.get_marime() == "S") nr2 = 6;
		else if (t2.get_marime() == "M") nr2 = 9;
		else if (t2.get_marime() == "L") nr2 = 12;
		else if (t2.get_marime() == "XL") nr2 = 15;

		return nr1 > nr2 || (nr1 == nr2 && t1.get_pret() > t2.get_pret());
	});

	return sorted;
}
