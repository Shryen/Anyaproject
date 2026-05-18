#pragma once
#include <QWidget>

class QPushButton;
class QVBoxLayout;

class Sidebar : public QWidget {
	Q_OBJECT

public:
	explicit Sidebar(QWidget* parent = nullptr);
	void SetupSidebarStyle();
	void paintEvent(QPaintEvent* event) override;

private:
	QPushButton* receiptsButton;
	QPushButton* profitsButton;

	QVBoxLayout* layout;
};