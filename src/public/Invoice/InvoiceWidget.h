#pragma once
#include <QWidget>
#include <QLabel>

struct Invoice;
class QPaintEvent;

class InvoiceWidget : public QWidget {
	Q_OBJECT

public:
	explicit InvoiceWidget(const Invoice& invoice, QWidget* parent = nullptr);

	int GetInvoiceId() const { return idLabel->text().toInt(); }

protected:
	void mousePressEvent(QMouseEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

signals:
	void InvoiceSelected(int invoiceId);


private:
	QLabel* idLabel;
	QLabel* nameLabel;
	QLabel* amountLabel;
	QLabel* dateLabel;
};