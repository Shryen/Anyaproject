#include "MainWindow.h"
#include <QApplication>

int main() {
	QApplication app(__argc, __argv);
	MainWindow* mainWindow = new MainWindow();
	mainWindow->show();
	return app.exec();
}