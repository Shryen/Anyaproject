#include "Invoice/InvoiceWidget.h"
#include "Invoice.h"
#include <QLabel>
#include <QHBoxLayout>

InvoiceWidget::InvoiceWidget(const Invoice& invoice, QWidget* parent)
	: QWidget(parent)
{
	idLabel = new QLabel(QString("%1").arg(invoice.id), this);
	nameLabel = new QLabel(QString("%1").arg(invoice.nev), this);
	amountLabel = new QLabel(QString("%1").arg(invoice.osszeg), this);
	dateLabel = new QLabel(QString("%1").arg(invoice.datum), this);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(8, 8, 8, 8);
	layout->setSpacing(0);

	layout->addWidget(idLabel);
	layout->addWidget(nameLabel);
	layout->addWidget(amountLabel);
	layout->addWidget(dateLabel);

	setStyleSheet(R"(
		InvoiceWidget {
			border: 1px solid rgba(0, 0, 0, 0.3);
		}

		QLabel {
			color: black;
			font-size: 16pt;
			border-bottom: 1px solid rgba(0, 0, 0, 0.3);
			padding: 8px;
		}
	)");
}
