#include "Content/EditContentWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

EditContentWidget::EditContentWidget(QWidget* parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignCenter);

	QWidget* formWidget = new QWidget(this);
	formWidget->setFixedSize(500, 380);
	formWidget->setStyleSheet(R"(
		QWidget {
			background-color: white;
			border: 2px solid #1B365D;
			border-radius: 12px;
		}
	)");

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(formWidget);
	shadow->setBlurRadius(30);
	shadow->setColor(QColor(0, 0, 0, 40));
	shadow->setOffset(0, 4);
	formWidget->setGraphicsEffect(shadow);

	QVBoxLayout* formLayout = new QVBoxLayout(formWidget);
	formLayout->setSpacing(10);
	formLayout->setContentsMargins(30, 30, 30, 30);

	titleLabel = new QLabel("Számla szerkesztése", formWidget);
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet(R"(
		QLabel {
			color: #1B365D;
			font-size: 22pt;
			font-weight: bold;
			background: transparent;
			border: none;
		}
	)");

	oldNameLabel = new QLabel(formWidget);
	oldNameLabel->setStyleSheet(R"(
		QLabel {
			color: #4A5568;
			font-size: 11pt;
			background: transparent;
			border: none;
			padding: 0px;
		}
	)");

	nameEdit = new QLineEdit(formWidget);
	nameEdit->setStyleSheet(R"(
		QLineEdit {
			font-size: 14pt;
			color: #4A5568;
			background-color: #F7FAFC;
			border: 2px solid #1B365D;
			border-radius: 6px;
			padding: 10px;
		}
		QLineEdit:focus {
			border-color: #059669;
		}
	)");

	oldAmountLabel = new QLabel(formWidget);
	oldAmountLabel->setStyleSheet(R"(
		QLabel {
			color: #4A5568;
			font-size: 11pt;
			background: transparent;
			border: none;
			padding: 0px;
		}
	)");

	amountEdit = new QLineEdit(formWidget);
	amountEdit->setStyleSheet(nameEdit->styleSheet());

	oldDateLabel = new QLabel(formWidget);
	oldDateLabel->setStyleSheet(R"(
		QLabel {
			color: #4A5568;
			font-size: 11pt;
			background: transparent;
			border: none;
			padding: 0px;
		}
	)");

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setSpacing(15);

	cancelButton = new QPushButton("Mégsem", formWidget);
	cancelButton->setFixedSize(200, 50);
	cancelButton->setCursor(Qt::PointingHandCursor);
	cancelButton->setStyleSheet(R"(
		QPushButton {
			font-size: 14pt;
			font-weight: bold;
			color: #4A5568;
			background-color: white;
			border: 2px solid #1B365D;
			border-radius: 8px;
		}
		QPushButton:hover {
			background-color: #F7FAFC;
			border-color: #2C5282;
		}
		QPushButton:pressed {
			background-color: #EDF2F7;
		}
	)");

	saveButton = new QPushButton("Mentés", formWidget);
	saveButton->setFixedSize(200, 50);
	saveButton->setCursor(Qt::PointingHandCursor);
	saveButton->setStyleSheet(R"(
		QPushButton {
			font-size: 14pt;
			font-weight: bold;
			color: white;
			background-color: #059669;
			border: none;
			border-radius: 8px;
		}
		QPushButton:hover {
			background-color: #047857;
		}
		QPushButton:pressed {
			background-color: #065F46;
		}
	)");

	buttonLayout->addWidget(cancelButton);
	buttonLayout->addWidget(saveButton);

	formLayout->addWidget(titleLabel);
	formLayout->addWidget(oldNameLabel);
	formLayout->addWidget(nameEdit);
	formLayout->addWidget(oldAmountLabel);
	formLayout->addWidget(amountEdit);
	formLayout->addWidget(oldDateLabel);
	formLayout->addLayout(buttonLayout);

	layout->addWidget(formWidget);

	connect(cancelButton, &QPushButton::clicked, this, [this]() {
		currentInvoiceId = -1;
		oldNameLabel->clear();
		oldAmountLabel->clear();
		oldDateLabel->clear();
		nameEdit->clear();
		amountEdit->clear();
		emit BackRequested();
	});

	connect(saveButton, &QPushButton::clicked, this, [this]() {
		QString name = nameEdit->text();
		QString amountStr = amountEdit->text();
		QString date = oldDateLabel->text();
		emit EditRequested(Invoice{ currentInvoiceId, name, amountStr.toDouble(), date });
	});
}

void EditContentWidget::LoadInvoice(const Invoice& invoice)
{
	currentInvoiceId = invoice.id;
	oldNameLabel->setText(QStringLiteral("Régi név: ") + invoice.nev);
	oldAmountLabel->setText(QStringLiteral("Régi összeg: ") + QString::number(invoice.osszeg, 'f', 2));
	oldDateLabel->setText(invoice.datum);
	nameEdit->setText(invoice.nev);
	amountEdit->setText(QString::number(invoice.osszeg, 'f', 2));
}
