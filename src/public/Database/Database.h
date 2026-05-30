#pragma once
#include <sqlite3.h>
#include "Invoice.h"

class Database {
public:
	Database();
	~Database();

	QVector<Invoice> getAllInvoices();

	void insertData(const QString& name, double amount, const QString& date);

private:
	sqlite3* db = nullptr;
	int ConnectionResult{ 0 };
	void SetupDatabase();
	void CreateTable();
};