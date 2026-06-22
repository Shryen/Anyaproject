#pragma once
#include <QWidget>
#include "Invoice.h"

class Database;
class Content;

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void onDataReceived(const Invoice& Data); 
	void onDeleteRequested();
	void onEditRequested(const Invoice& Data);
	void onInvoiceSelected(int id);

private:
	Database* database = nullptr;
	Content* contentWidget = nullptr;

	int selectedInvoiceId = -1;
};
