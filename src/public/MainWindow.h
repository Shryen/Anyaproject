#pragma once
#include <QWidget>


class AddButton;
class Database;
class Sidebar;
class Content;

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

	Sidebar* sideBar = nullptr;
	Content* contentWidget = nullptr;
};
