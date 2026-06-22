#include "Invoice/InvoiceWidget.h"
#include "Invoice.h"
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>

InvoiceWidget::InvoiceWidget(const Invoice& invoice, QWidget* parent)
	: QWidget(parent)
{
	idLabel = new QLabel(QString::number(invoice.id), this);
	nameLabel = new QLabel(invoice.nev, this);
	amountLabel = new QLabel(QString::number(invoice.osszeg, 'f', 2), this);
	dateLabel = new QLabel(invoice.datum, this);

	QString labelStyle = R"(
		QLabel {
			font-size: 16pt;
			padding: 8px;
			color: #4A5568;
			border-bottom: 1px solid rgba(74, 85, 104, 0.15);
		}
	)";

	QString amountStyle = R"(
		QLabel {
			font-size: 16pt;
			padding: 8px;
			color: #059669;
			font-weight: bold;
			border-bottom: 1px solid rgba(74, 85, 104, 0.15);
		}
	)";

	idLabel->setFixedWidth(120);
	idLabel->setStyleSheet(labelStyle);

	nameLabel->setMinimumWidth(200);
	nameLabel->setStyleSheet(labelStyle);
	nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	amountLabel->setMinimumWidth(200);
	amountLabel->setStyleSheet(amountStyle);
	amountLabel->setAlignment(Qt::AlignCenter);

	dateLabel->setMinimumWidth(200);
	dateLabel->setStyleSheet(labelStyle);
	dateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QWidget* leftGroup = new QWidget(this);
	QHBoxLayout* leftLayout = new QHBoxLayout(leftGroup);
	leftLayout->setContentsMargins(0, 0, 0, 0);
	leftLayout->setSpacing(0);
	leftLayout->addWidget(idLabel);
	leftLayout->addWidget(nameLabel);

	QGridLayout* grid = new QGridLayout(this);
	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
	grid->setColumnStretch(0, 1);
	grid->setColumnStretch(2, 1);

	grid->addWidget(leftGroup, 0, 0, Qt::AlignLeft);
	grid->addWidget(amountLabel, 0, 1, Qt::AlignCenter);
	grid->addWidget(dateLabel, 0, 2, Qt::AlignRight);

	setCursor(Qt::PointingHandCursor);
}

void InvoiceWidget::mousePressEvent(QMouseEvent* event)
{
	emit InvoiceSelected(idLabel->text().toInt());
	QWidget::mousePressEvent(event);
}

void InvoiceWidget::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
