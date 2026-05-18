#pragma once
#include <sqlite3.h>
#include <QString>

struct Szamla {
	int id;
	QString nev;
	double osszeg;
	QString datum;
};


class Database {
public:
	Database();
	~Database();

	QVector<Szamla> getAllInvoices();

	void insertData(const QString& name, double amount, const QString& date);

private:
	sqlite3* db = nullptr;
	int ConnectionResult{ 0 };
	void SetupDatabase();
	void CreateTable();
};