#pragma once
#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QLabel;

class Sidebar : public QWidget {
	Q_OBJECT

public:
	explicit Sidebar(QWidget* parent = nullptr);
	void SetupButtons();
	void SetupTitleLabel();
	void SetupSidebarStyle();
	void paintEvent(QPaintEvent* event) override;

private:
	QPushButton* receiptsButton = nullptr;
	QPushButton* profitsButton = nullptr;

	QVBoxLayout* layout = nullptr;

	QLabel* titleLabel = nullptr;
};
