#include "MainWindow.h"
#include <QHBoxLayout>

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
	addButton = new AddButton("Add");
	connect(addButton, &AddButton::buttonPressed, this, &MainWindow::onAddButtonPressed);

	MainLayout->addWidget(addButton);

	database->getAllInvoices();
}

void MainWindow::onAddButtonPressed() {
	database->insertData("Jani", 2.0, "2026/05/13");
}