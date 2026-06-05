#include "Invoice/InvoiceWidget.h"
#include "Invoice.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>

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
		QLabel {
			color: black;
			font-size: 16pt;
			border-bottom: 1px solid rgba(0, 0, 0, 0.3);
			padding: 8px;
		}
	)");
}

void InvoiceWidget::mousePressEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
		emit InvoiceSelected(idLabel->text().toInt());
}

void InvoiceWidget::paintEvent(QPaintEvent* event) {
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}