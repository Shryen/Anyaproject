#include "Content/EditContentWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>

EditContentWidget::EditContentWidget(QWidget* parent) : QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(20, 20, 20, 20);
	mainLayout->setSpacing(20);

	mainLayout->addWidget(CreateHeaderWidget());
	mainLayout->addWidget(CreateFormWidget());
}

void EditContentWidget::LoadInvoice(const Invoice& invoice)
{
	currentInvoiceId = invoice.id;
	oldNameLabel->setText(invoice.nev);
	oldAmountLabel->setText(QString("%1 €").arg(invoice.osszeg));
	oldDateLabel->setText(invoice.datum);

	nameEdit->setText(invoice.nev);
	amountEdit->setText(QString::number(invoice.osszeg, 'f', 2));
	dateEdit->setDate(QDate::fromString(invoice.datum, "yyyy-MM-dd"));
}

QWidget* EditContentWidget::CreateHeaderWidget()
{
	QWidget* headerWidget = new QWidget(this);

	titleLabel = new QLabel("Számla szerkesztése", headerWidget);
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet(R"(
		font-size: 28pt;
		color: black;
		font-weight: bold;
	)");

	backButton = new QPushButton("Vissza", headerWidget);
	backButton->setCursor(Qt::PointingHandCursor);
	backButton->setFixedHeight(42);
	backButton->setStyleSheet(R"(
		QPushButton {
			font-size: 14pt;
			font-weight: bold;
			color: rgba(0, 0, 0, 0.65);
			background-color: white;
			border-radius: 5px;
			border: 2px solid #5fa8d3;
			padding: 6px 18px;
		}
		QPushButton:hover {
			background-color: #f0ead6;
		}
		QPushButton:pressed {
			background-color: #5fa8d3;
			color: white;
		}
	)");
	connect(backButton, &QPushButton::clicked, this, &EditContentWidget::BackRequested);

	QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
	headerLayout->setContentsMargins(0, 0, 0, 0);
	headerLayout->setSpacing(10);
	headerLayout->addWidget(titleLabel);
	headerLayout->addWidget(backButton, 0, Qt::AlignRight);

	return headerWidget;
}

QWidget* EditContentWidget::CreateFormWidget()
{
	QWidget* formWidget = new QWidget(this);
	formWidget->setObjectName("formWidget");

	oldNameLabel = new QLabel(formWidget);
	oldAmountLabel = new QLabel(formWidget);
	oldDateLabel = new QLabel(formWidget);
	nameEdit = new QLineEdit(formWidget);
	amountEdit = new QLineEdit(formWidget);
	dateEdit = new QDateEdit(formWidget);
	cancelButton = new QPushButton("Mégsem", formWidget);
	saveButton = new QPushButton("Mentés", formWidget);

	formWidget->setStyleSheet(R"(
		#formWidget {
			background-color: white;
			border: 1px solid rgba(0, 0, 0, 0.3);
			border-radius: 10px;
		}

		QLabel {
			color: rgba(0, 0, 0, 0.5);
			font-size: 12pt;
			padding: 4px 0px;
		}

		QLineEdit,
		QDateEdit {
			color: black;
			background-color: white;
			border: 2px solid #5fa8d3;
			border-radius: 5px;
			padding: 8px;
			font-size: 16pt;
		}

		QLineEdit:focus,
		QDateEdit:focus {
			border-color: #4f98c3;
		}
	)");

	QString buttonStyle = R"(
		QPushButton {
			font-size: 14pt;
			font-weight: bold;
			color: white;
			background-color: #5fa8d3;
			border-radius: 5px;
			border: none;
			padding: 8px 20px;
		}
		QPushButton:hover {
			background-color: #4f98c3;
		}
		QPushButton:pressed {
			background-color: #3f88b3;
		}
	)";

	QString cancelButtonStyle = R"(
		QPushButton {
			font-size: 14pt;
			font-weight: bold;
			color: rgba(0, 0, 0, 0.65);
			background-color: white;
			border-radius: 5px;
			border: 2px solid #5fa8d3;
			padding: 8px 20px;
		}
		QPushButton:hover {
			background-color: #f0ead6;
		}
		QPushButton:pressed {
			background-color: #5fa8d3;
			color: white;
		}
	)";

	cancelButton->setCursor(Qt::PointingHandCursor);
	cancelButton->setFixedHeight(44);
	cancelButton->setStyleSheet(cancelButtonStyle);

	saveButton->setCursor(Qt::PointingHandCursor);
	saveButton->setFixedHeight(44);
	saveButton->setStyleSheet(buttonStyle);

	dateEdit->setCalendarPopup(true);
	dateEdit->setDisplayFormat("yyyy-MM-dd");

	connect(cancelButton, &QPushButton::clicked, this, &EditContentWidget::BackRequested);
	connect(saveButton, &QPushButton::clicked, this, [this]() {
		Invoice invoice;
		invoice.id = currentInvoiceId;
		invoice.nev = nameEdit->text();
		invoice.osszeg = amountEdit->text().toDouble();
		invoice.datum = dateEdit->date().toString("yyyy-MM-dd");
		emit EditRequested(invoice);
	});

	QVBoxLayout* formLayout = new QVBoxLayout(formWidget);
	formLayout->setContentsMargins(16, 16, 16, 16);
	formLayout->setSpacing(12);

	formLayout->addWidget(new QLabel("Régi értékek:", formWidget));
	formLayout->addWidget(oldNameLabel);
	formLayout->addWidget(oldAmountLabel);
	formLayout->addWidget(oldDateLabel);

	formLayout->addSpacing(16);
	formLayout->addWidget(new QLabel("Új értékek:", formWidget));
	formLayout->addWidget(nameEdit);
	formLayout->addWidget(amountEdit);
	formLayout->addWidget(dateEdit);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setSpacing(10);
	buttonLayout->addStretch();
	buttonLayout->addWidget(cancelButton);
	buttonLayout->addWidget(saveButton);
	formLayout->addLayout(buttonLayout);

	return formWidget;
}
