#pragma once
#include <QWidget>
#include "Invoice.h"

class QPushButton;
class QLineEdit;
class QDateEdit;
class QLabel;

class EditContentWidget : public QWidget {
	Q_OBJECT
public:
	explicit EditContentWidget(QWidget* parent = nullptr);
	void LoadInvoice(const Invoice& invoice);

signals:
	void BackRequested();
	void EditRequested(const Invoice& data);

private:
	QLabel* titleLabel = nullptr;
	QPushButton* backButton = nullptr;

	QLabel* oldNameLabel = nullptr;
	QLabel* oldAmountLabel = nullptr;
	QLabel* oldDateLabel = nullptr;

	QLineEdit* nameEdit = nullptr;
	QLineEdit* amountEdit = nullptr;
	QDateEdit* dateEdit = nullptr;
	QPushButton* cancelButton = nullptr;
	QPushButton* saveButton = nullptr;

	int currentInvoiceId = -1;

	QWidget* CreateHeaderWidget();
	QWidget* CreateFormWidget();
};
