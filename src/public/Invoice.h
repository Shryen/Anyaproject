#pragma once
#include <QString>

struct Invoice {
	int id{ 0 };
	QString nev{ "" };
	double osszeg{ 0.0 };
	QString datum{ "" };
};
