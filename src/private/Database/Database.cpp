#include "Database/Database.h"
#include <QDebug>

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

void Database::insertData(const QString& name, double amount, const QString& date) {
    if (!db) {
        qDebug() << "Adatbázis nem elérhető: " << sqlite3_errmsg(db);
        return;
    }

    const char* sqlStmt = "INSERT INTO szamlak (nev, osszeg, datum) VALUES (?, ?, ?)";
    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sqlStmt, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, name.toStdString().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(statement, 2, amount);
        sqlite3_bind_text(statement, 3, date.toStdString().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(statement) == SQLITE_DONE)
            qDebug() << "Adat rögzítve";
        else 
            qDebug() << "Nem sikerült rögzíteni az adatot: " << sqlite3_errmsg(db);
    } else
        qDebug() << "Prepare failed: " << sqlite3_errmsg(db);

    sqlite3_finalize(statement);
}

QVector<Szamla> Database::getAllInvoices() {
    QVector<Szamla> szamlak;
    if (!db) {
        qDebug() << "Addatbázis nem elérhető: " << sqlite3_errmsg(db);
        return szamlak;
    }

    const char* sql = "SELECT * from szamlak";
    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            Szamla szamla;
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