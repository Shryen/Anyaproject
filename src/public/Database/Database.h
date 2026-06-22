#pragma once
#include <sqlite3.h>
#include "Invoice.h"

class QString;

class Database {
public:
	Database();
	~Database();

	QVector<Invoice> getAllInvoices();
	Invoice getInvoiceById(int id);

	void insertData(const Invoice& Data);
	void updateData(const Invoice& Data);
	void deleteData(int id);


	QString GetSumOfInvoices();


	QString getInvoiceInfo(int id);
private:
	sqlite3* db = nullptr;
	int ConnectionResult{ 0 };
	void SetupDatabase();
	void CreateTable();
};