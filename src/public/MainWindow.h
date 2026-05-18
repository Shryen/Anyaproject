#pragma once
#include <QWidget>


class AddButton;
class Database;
class Sidebar;

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void onAddButtonPressed(); 

private:
	// Buttons
	AddButton* addButton = nullptr;
	Database* database = nullptr;

	// Sidebar
	Sidebar* sidebar = nullptr;

};