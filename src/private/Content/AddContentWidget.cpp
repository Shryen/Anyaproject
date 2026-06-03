#include "Content/AddContentWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDate>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QPushButton>

AddContentWidget::AddContentWidget(QWidget* parent) : QWidget(parent)
{
	QWidget* header = CreateHeaderWidget();
	QWidget* form = CreateFormWidget();

	QVBoxLayout* mainLayout = SetupMainLayout();
	mainLayout->addWidget(header, 1);
	mainLayout->addWidget(form, 4);
}

QVBoxLayout* AddContentWidget::SetupMainLayout()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(20, 20, 20, 20);
	mainLayout->setSpacing(20);
	return mainLayout;
}

QHBoxLayout* AddContentWidget::SetupHeaderLayout()
{
	QHBoxLayout* headerLayout = new QHBoxLayout();
	headerLayout->setContentsMargins(0, 0, 0, 0);
	headerLayout->setSpacing(10);
	return headerLayout;
}

QVBoxLayout* AddContentWidget::SetupFormLayout()
{
	QVBoxLayout* formLayout = new QVBoxLayout();
	formLayout->setContentsMargins(16, 16, 16, 16);
	formLayout->setSpacing(12);
	return formLayout;
}

QWidget* AddContentWidget::CreateHeaderWidget()
{
	QWidget* headerWidget = new QWidget(this);
	titleLabel = new QLabel("Számla létrehozása", headerWidget);
	backButton = new QPushButton("Vissza", headerWidget);
	backButton->setCursor(Qt::PointingHandCursor);
	backButton->setFixedHeight(42);

	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet(R"(
		font-size: 28pt;
		color: black;
		font-weight: bold;
	)");

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

	connect(backButton, &QPushButton::clicked,
		this, &AddContentWidget::BackRequested);

	QHBoxLayout* headerLayout = SetupHeaderLayout();
	headerWidget->setLayout(headerLayout);

	headerLayout->addWidget(titleLabel);
	headerLayout->addWidget(backButton, 0, Qt::AlignRight);

	return headerWidget;
}

QWidget* AddContentWidget::CreateFormWidget()
{
	QWidget* formWidget = new QWidget(this);
	formWidget->setObjectName("formWidget");

	nameEdit = new QLineEdit(formWidget);
	amountEdit = new QLineEdit(formWidget);
	dateEdit = new QDateEdit(formWidget);
	addButton = new QPushButton("Hozzáadás", formWidget);

	connect(addButton, &QPushButton::clicked, this, [this]() {
		Invoice invoice;
		invoice.nev = nameEdit->text();
		invoice.osszeg = amountEdit->text().toDouble();
		invoice.datum = dateEdit->date().toString("yyyy-MM-dd");

		emit AddRequested(invoice);
	});

	nameEdit->setPlaceholderText("Név");
	amountEdit->setPlaceholderText("Összeg");
	dateEdit->setCalendarPopup(true);
	dateEdit->setDate(QDate::currentDate());
	dateEdit->setDisplayFormat("yyyy-MM-dd");
	dateEdit->calendarWidget()->setStyleSheet(R"(
		QCalendarWidget {
			background-color: white;
			color: black;
			border: 1px solid black;
		}

		QCalendarWidget QWidget {
			background-color: white;
			color: black;
		}

		QCalendarWidget QToolButton {
			color: black;
			background-color: white;
			border: 1px solid black;
			border-radius: 3px;
			padding: 4px;
		}

		QCalendarWidget QMenu {
			background-color: white;
			color: black;
			border: 1px solid black;
		}

		QCalendarWidget QSpinBox {
			color: black;
			background-color: white;
			border: 1px solid black;
		}

		QCalendarWidget QAbstractItemView {
			color: black;
			background-color: white;
			selection-background-color: #5fa8d3;
			selection-color: white;
			border: 1px solid black;
		}
	)");
	addButton->setCursor(Qt::PointingHandCursor);
	addButton->setFixedHeight(44);

	QVBoxLayout* formLayout = SetupFormLayout();
	formWidget->setLayout(formLayout);

	formLayout->addWidget(nameEdit);
	formLayout->addWidget(amountEdit);
	formLayout->addWidget(dateEdit);
	formLayout->addWidget(addButton, 0, Qt::AlignRight);

	formWidget->setStyleSheet(R"(
		#formWidget {
			background-color: white;
			border: 1px solid rgba(0, 0, 0, 0.3);
			border-radius: 10px;
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
	)");

	return formWidget;
}
