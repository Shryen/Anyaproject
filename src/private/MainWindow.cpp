#include "MainWindow.h"
#include <QHBoxLayout>
#include "Buttons/AddButton.h"
#include "Database/Database.h"
#include "Sidebar/Sidebar.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
	// Start Database
	database = new Database();

	// Setup Window
	setWindowTitle("Számlák");
	setFixedSize(QSize{ 1280,720 });
	setStyleSheet(R"(
		background-color: #f5f5f5;
	)");

	// Setup Layout and widgets
	QHBoxLayout* MainLayout = new QHBoxLayout(this);
	MainLayout->setContentsMargins(0, 0, 0, 0);
	MainLayout->setSpacing(10);
	Sidebar* sideBar = new Sidebar(this);
	addButton = new AddButton("Add");
	connect(addButton, &AddButton::buttonPressed, this, &MainWindow::onAddButtonPressed);

	MainLayout->addWidget(sideBar);
	MainLayout->addWidget(addButton);

	database->getAllInvoices();
}

void MainWindow::onAddButtonPressed() {
	database->insertData("Jani", 2.0, "2026/05/13");
}