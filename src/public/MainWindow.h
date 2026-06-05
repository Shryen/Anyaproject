#pragma once
#include <QWidget>
#include "Invoice.h"

class AddButton;
class Database;
class Sidebar;
class Content;

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void onDataReceived(const Invoice& Data); 
	void onDeleteRequested();
	void onInvoiceSelected(int id);

private:
	// Buttons
	AddButton* addButton = nullptr;
	Database* database = nullptr;

	Sidebar* sideBar = nullptr;
	Content* contentWidget = nullptr;

	int selectedInvoiceId = -1;
};
