#pragma once
#include <QWidget>
#include "Buttons/AddButton.h"
#include "Database/Database.h"

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void onAddButtonPressed(); 

private:
	AddButton* addButton = nullptr;
	Database* database = nullptr;

};