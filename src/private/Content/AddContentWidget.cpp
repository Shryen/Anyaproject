#include "Content/AddContentWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

AddContentWidget::AddContentWidget(QWidget* parent)
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
	formLayout->setSpacing(15);
	formLayout->setContentsMargins(30, 30, 30, 30);

	titleLabel = new QLabel("Új számla hozzáadása", formWidget);
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

	nameEdit = new QLineEdit(formWidget);
	nameEdit->setPlaceholderText("Név");
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

	amountEdit = new QLineEdit(formWidget);
	amountEdit->setPlaceholderText("Összeg");
	amountEdit->setStyleSheet(nameEdit->styleSheet());

	dateEdit = new QDateEdit(QDate::currentDate(), formWidget);
	dateEdit->setDisplayFormat("yyyy-MM-dd");
	dateEdit->setStyleSheet(R"(
		QDateEdit {
			font-size: 14pt;
			color: #4A5568;
			background-color: #F7FAFC;
			border: 2px solid #1B365D;
			border-radius: 6px;
			padding: 10px;
		}
		QDateEdit:focus {
			border-color: #059669;
		}
		QDateEdit::drop-down {
			subcontrol-origin: padding;
			subcontrol-position: top right;
			width: 30px;
			border-left: 1px solid #1B365D;
			background-color: #1B365D;
			border-top-right-radius: 4px;
			border-bottom-right-radius: 4px;
		}
		QDateEdit::down-arrow {
			width: 0px;
			height: 0px;
			border-left: 5px solid transparent;
			border-right: 5px solid transparent;
			border-top: 6px solid white;
		}
	)");

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setSpacing(15);

	backButton = new QPushButton("Vissza", formWidget);
	backButton->setFixedSize(200, 50);
	backButton->setCursor(Qt::PointingHandCursor);
	backButton->setStyleSheet(R"(
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

	addButton = new QPushButton("Hozzáadás", formWidget);
	addButton->setFixedSize(200, 50);
	addButton->setCursor(Qt::PointingHandCursor);
	addButton->setStyleSheet(R"(
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

	buttonLayout->addWidget(backButton);
	buttonLayout->addWidget(addButton);

	formLayout->addWidget(titleLabel);
	formLayout->addWidget(nameEdit);
	formLayout->addWidget(amountEdit);
	formLayout->addWidget(dateEdit);
	formLayout->addLayout(buttonLayout);

	layout->addWidget(formWidget);

	connect(addButton, &QPushButton::clicked, this, [this]() {
		QString name = nameEdit->text();
		QString amountStr = amountEdit->text();
		emit AddRequested(Invoice{ 0, name, amountStr.toDouble(), dateEdit->date().toString("yyyy-MM-dd") });
	});
	connect(backButton, &QPushButton::clicked, this, &AddContentWidget::BackRequested);
}
