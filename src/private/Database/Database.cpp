#include "Database/Database.h"
#include <QDebug>
#include <QString>
#include <QDate>
#include <QRandomGenerator>

Database::Database() {
    SetupDatabase();
    CreateTable();
}

Database::~Database() {
    if (db != nullptr) {
        qDebug() << "Adatbázis nullpointer: " << sqlite3_errmsg(db);
        sqlite3_close(db);
    }
}

void Database::SetupDatabase() {
    ConnectionResult = sqlite3_open("szamlak.db", &db);
    if (ConnectionResult != SQLITE_OK) {
        qDebug() << "Nem sikerült megnyitni az adatbázist: " << sqlite3_errmsg(db);
        sqlite3_close(db);
        db = nullptr;
    }
    else
        qDebug() << "Adatbázis megnyitva";
}

void Database::CreateTable() {

    if (db == nullptr) {
        qDebug() << "Adatbázis nem elérhető: " << sqlite3_errmsg(db);
        return;
    }

    const char* sql = R"(CREATE TABLE IF NOT EXISTS szamlak 
                    (id INTEGER PRIMARY KEY, 
                    nev TEXT NOT NULL, 
                    osszeg REAL NOT NULL, 
                    datum DATETIME NOT NULL );)";

    char* errMsg = nullptr;
    int result = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        qDebug() << "Hiba a tábla létrehozásakor: " << errMsg;
        sqlite3_free(errMsg);
    } else 
        qDebug() << "Tábla létrehozva vagy már létezik.";
}

void Database::insertData(const Invoice& Data) {
    if (!db) {
        qDebug() << "Adatbázis nem elérhető: " << sqlite3_errmsg(db);
        return;
    }

    const char* sqlStmt = "INSERT INTO szamlak (nev, osszeg, datum) VALUES (?, ?, ?)";
    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sqlStmt, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, Data.nev.toStdString().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(statement, 2, Data.osszeg);
        sqlite3_bind_text(statement, 3, Data.datum.toStdString().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(statement) == SQLITE_DONE)
            qDebug() << "Adat rögzítve";
        else 
            qDebug() << "Nem sikerült rögzíteni az adatot: " << sqlite3_errmsg(db);
    } else
        qDebug() << "Prepare failed: " << sqlite3_errmsg(db);

    sqlite3_finalize(statement);
}

void Database::updateData(const Invoice& Data)
{
	if (!db) {
		qDebug() << "Adatbázis nem elérhető: " << sqlite3_errmsg(db);
		return;
	}

	const char* sqlStmt = "UPDATE szamlak SET nev = ?, osszeg = ?, datum = ? WHERE id = ?";
	sqlite3_stmt* statement = nullptr;

	if (sqlite3_prepare_v2(db, sqlStmt, -1, &statement, nullptr) == SQLITE_OK) {
		sqlite3_bind_text(statement, 1, Data.nev.toStdString().c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_double(statement, 2, Data.osszeg);
		sqlite3_bind_text(statement, 3, Data.datum.toStdString().c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(statement, 4, Data.id);

		if (sqlite3_step(statement) == SQLITE_DONE)
			qDebug() << "Adat frissítve";
		else
			qDebug() << "Nem sikerült frissíteni az adatot: " << sqlite3_errmsg(db);
	} else
		qDebug() << "Prepare failed: " << sqlite3_errmsg(db);

	sqlite3_finalize(statement);
}

void Database::deleteData(int id)
{
    if (!db) {
        qDebug() << "Adatbázis nem elérhető: " << sqlite3_errmsg(db);
        return;
    }

	const char* sqlStmt = "DELETE FROM szamlak WHERE id = ?";
	sqlite3_stmt* statement = nullptr;

    if(sqlite3_prepare_v2(db, sqlStmt, -1, &statement, nullptr) == SQLITE_OK){
		sqlite3_bind_text(statement, 1, QString::number(id).toStdString().c_str(), -1, SQLITE_TRANSIENT);

		if (sqlite3_step(statement) == SQLITE_DONE)
            qDebug() << "Adat törölve";
        else
            qDebug() << "Nem sikerült törölni az adatot: " << sqlite3_errmsg(db);
    } else
		qDebug() << "Prepare failed: " << sqlite3_errmsg(db);

    sqlite3_finalize(statement);
}

void Database::deleteAllData()
{
	const char* deleteAll = "DELETE FROM szamlak";
	char* errMsg = nullptr;
	sqlite3_exec(db, deleteAll, nullptr, nullptr, &errMsg);
}

void Database::GenerateMockData()
{
	const char* deleteAll = "DELETE FROM szamlak";
	char* errMsg = nullptr;
	sqlite3_exec(db, deleteAll, nullptr, nullptr, &errMsg);

	const char* resetId = "DELETE FROM sqlite_sequence WHERE name='szamlak'";
	sqlite3_exec(db, resetId, nullptr, nullptr, nullptr);

	QStringList names = {
		"Kovács Béla", "Nagy Anna", "Tóth Péter", "Szabó Eszter",
		"Horváth Gábor", "Varga Mária", "Kiss László", "Molnár Zsófia",
		"Nemeth Dániel", "Farkas Viktória", "Balogh Tamás", "Papp Judit",
		"Lakatos István", "Mészáros Andrea", "Simon Róbert", "Oláh Katalin",
		"Takács József", "Fazekas Gabriella", "Sándor Attila", "Bíró Dóra",
		"Gál Zoltán", "Fehér Ildikó", "Pintér Csaba", "Kovács Erika",
		"Fülöp Gergő", "Szűcs Nikolett", "Vincze Ádám", "Hegedűs Tímea",
		"Bodnár Tibor", "Bogdán Petra"
	};

	int currentYear = QDate::currentDate().year();

	for (int month = 1; month <= 12; ++month) {
		int daysInMonth = QDate(currentYear, month, 1).daysInMonth();

		for (int i = 0; i < 25; ++i) {
			int day = QRandomGenerator::global()->bounded(1, daysInMonth + 1);
			QDate date(currentYear, month, day);

			QString name = names[QRandomGenerator::global()->bounded(names.size())];
			double amount = QRandomGenerator::global()->bounded(500, 100000) / 100.0;

			Invoice invoice;
			invoice.nev = name;
			invoice.osszeg = amount;
			invoice.datum = date.toString("yyyy-MM-dd");

			insertData(invoice);
		}
	}
}

QString Database::GetSumOfInvoices()
{
    QVector<Invoice> AllInvoices = getAllInvoices();
    QString sumString = "";
    double sum{ 0.0 };
    for(const Invoice& invoice : AllInvoices){
		sum += invoice.osszeg;
    }
    return QString("%1").arg(sum);
}

QString Database::getInvoiceInfo(int id)
{
	Invoice invoice = getInvoiceById(id);
 
    return QString("<p style='text-align:center; font-size: 14pt;'>ID: %1 | Név: %2 | Összeg: %3 | Dátum: %4</p>")
        .arg(invoice.id)
        .arg(invoice.nev)
        .arg(invoice.osszeg)
        .arg(invoice.datum);
}

QVector<Invoice> Database::getAllInvoices() {
    QVector<Invoice> szamlak;
    if (!db) {
        qDebug() << "Addatbázis nem elérhető: " << sqlite3_errmsg(db);
        return szamlak;
    }

    const char* sql = "SELECT * from szamlak";
    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            Invoice szamla;
            szamla.id = sqlite3_column_int(statement, 0);
            szamla.nev = QString::fromUtf8((const char*)sqlite3_column_text(statement, 1));
            szamla.osszeg = sqlite3_column_double(statement, 2);
            szamla.datum = QString::fromUtf8((const char*)sqlite3_column_text(statement, 3));

            szamlak.append(szamla);
            qDebug() << "ID: " << szamla.id << "Név: " << szamla.nev << "Összeg: " << szamla.osszeg << "Dátum: " << szamla.datum;
        }

        qDebug() << "Lekérdezés sikeres. Találatok: " << szamlak.size();
    }
    else 
        qDebug() << "Prepare failed: " << sqlite3_errmsg(db);
    
    sqlite3_finalize(statement);
    return szamlak;

}

Invoice Database::getInvoiceById(int id)
{
    if (!db) {
        qDebug() << "Addatbázis nem elérhető: " << sqlite3_errmsg(db);
    }
    Invoice invoice;
    const char* sql = "SELECT * from szamlak WHERE id = ?";
	sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, id);
        if (sqlite3_step(statement) == SQLITE_ROW) {
            invoice.id = sqlite3_column_int(statement, 0);
            invoice.nev = QString::fromUtf8((const char*)sqlite3_column_text(statement, 1));
            invoice.osszeg = sqlite3_column_double(statement, 2);
            invoice.datum = QString::fromUtf8((const char*)sqlite3_column_text(statement, 3));
        }
    }

    sqlite3_finalize(statement);

    return invoice;
}
