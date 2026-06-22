#pragma once
#include <QWidget>
#include <QLabel>
#include <QDate>

struct Invoice;
class QPaintEvent;

class InvoiceWidget : public QWidget {
	Q_OBJECT

public:
	explicit InvoiceWidget(const Invoice& invoice, QWidget* parent = nullptr);

	int GetInvoiceId() const { return idLabel->text().toInt(); }
	QString GetInvoiceName() const { return nameLabel->text(); }
	int GetInvoiceYear() const {
		return QDate::fromString(dateLabel->text(), "yyyy-MM-dd").year();
	}

	int GetInvoiceMonth() const {
		return QDate::fromString(dateLabel->text(), "yyyy-MM-dd").month();
	}

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