#pragma once
#include <QWidget>

class QPushButton;
class QLineEdit;
class QDateEdit;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class AddContentWidget : public QWidget {
	Q_OBJECT
public:
	explicit AddContentWidget(QWidget* parent = nullptr);

signals:
	void BackRequested();
private:
	QLabel* titleLabel = nullptr;
	QPushButton* backButton = nullptr;
	QLineEdit* nameEdit = nullptr;
	QLineEdit* amountEdit = nullptr;
	QDateEdit* dateEdit = nullptr;
	QPushButton* addButton = nullptr;

	QVBoxLayout* SetupMainLayout();
	QHBoxLayout* SetupHeaderLayout();
	QVBoxLayout* SetupFormLayout();

	QWidget* CreateHeaderWidget();
	QWidget* CreateFormWidget();
};
