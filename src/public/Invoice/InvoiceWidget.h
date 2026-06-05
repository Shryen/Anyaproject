#pragma once
#include <QWidget>

class QLabel;
struct Invoice;

class InvoiceWidget : public QWidget {
	Q_OBJECT

public:
	explicit InvoiceWidget(const Invoice& invoice, QWidget* parent = nullptr);

protected:
	void mousePressEvent(QMouseEvent* event) override;

signals:
	void InvoiceSelected(int invoiceId);

private:
	QLabel* idLabel;
	QLabel* nameLabel;
	QLabel* amountLabel;
	QLabel* dateLabel;
};