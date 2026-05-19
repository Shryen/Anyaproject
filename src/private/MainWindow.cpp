#include "MainWindow.h"
#include <QHBoxLayout>
#include "Buttons/AddButton.h"
#include "Database/Database.h"
#include "Content/Content.h"
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

	sideBar = new Sidebar(this);
	contentWidget = new Content(this);

	connect(addButton, &AddButton::buttonPressed, this, &MainWindow::onAddButtonPressed);

	MainLayout->addWidget(sideBar);
	MainLayout->addWidget(addButton);
	MainLayout->addWidget(contentWidget);

	contentWidget->UpdateContent(database);
}

void MainWindow::onAddButtonPressed() {
	database->insertData("Jani", 2.0, "2026/05/13");
}