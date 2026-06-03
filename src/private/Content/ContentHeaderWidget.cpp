#include "Content/ContentHeaderWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ContentHeaderWidget::ContentHeaderWidget(QWidget* parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	layout->addWidget(CreateProfitWidget(), 0, Qt::AlignHCenter);
	layout->addWidget(CreateAddButtonWidget());
	layout->addWidget(CreateHeaderWidget());
}

QWidget* ContentHeaderWidget::CreateAddButtonWidget()
{
	QWidget* buttonWidget = new QWidget(this);
	QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
	buttonLayout->setContentsMargins(0, 10, 0, 10);
	buttonLayout->setAlignment(Qt::AlignRight);

	QPushButton* addButton = new QPushButton("+", buttonWidget);
	addButton->setObjectName("addButton");
	addButton->setFixedSize(QSize{ 50,50 });
	addButton->setStyleSheet(R"(
		QPushButton#addButton {
			font-size: 22pt;
			font-weight: bold;
			color: #f0ead6;
			background-color: #5fa8d3;
			border-radius: 8px;
			border: 2px solid #4f98c3;
			padding: 0px;
			text-align: center;
		}

		QPushButton#addButton:hover {
			background-color: #4f98c3;
			border-color: #3f88b3;
		}

		QPushButton#addButton:pressed {
			background-color: #3f88b3;
			border-color: #2f789f;
		}
	)");

	addButton->setCursor(Qt::PointingHandCursor);
	connect(addButton, &QPushButton::clicked, this, &ContentHeaderWidget::AddButtonClicked);

	buttonLayout->addWidget(addButton);

	return buttonWidget;
}

QWidget* ContentHeaderWidget::CreateHeaderWidget()
{
	QWidget* HeaderWidget = new QWidget(this);
	QLabel* idLabel = new QLabel("ID", HeaderWidget);
	QLabel* nameLabel = new QLabel("Név", HeaderWidget);
	QLabel* amountLabel = new QLabel("Összeg", HeaderWidget);
	QLabel* dateLabel = new QLabel("Dátum", HeaderWidget);
	QHBoxLayout* HeaderLayout = new QHBoxLayout(HeaderWidget);
	HeaderLayout->addWidget(idLabel);
	HeaderLayout->addWidget(nameLabel);
	HeaderLayout->addWidget(amountLabel);
	HeaderLayout->addWidget(dateLabel);
	HeaderLayout->setSpacing(0);
	HeaderLayout->setContentsMargins(0, 0, 0, 0);

	QString headerStyle = R"(
		QLabel {
			font-weight: bold;
			font-size: 18pt;
			color: #f0ead6;
			padding: 8px;
		}
		QWidget {
			border-bottom: 2px solid #f0ead6;
			background-color: #5fa8d3;
		}
	)";

	idLabel->setStyleSheet(headerStyle);
	nameLabel->setStyleSheet(headerStyle);
	amountLabel->setStyleSheet(headerStyle);
	dateLabel->setStyleSheet(headerStyle);

	return HeaderWidget;
}

QWidget* ContentHeaderWidget::CreateProfitWidget()
{
	QWidget* profitWidget = new QWidget(this);
	profitWidget->setFixedSize(180, 180);

	QLabel* profitLabel = new QLabel("Bevétel: 0 €", profitWidget);
	profitLabel->setAlignment(Qt::AlignCenter);


	QHBoxLayout* layout = new QHBoxLayout(profitWidget);
	layout->addWidget(profitLabel);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setAlignment(Qt::AlignCenter);

	profitWidget->setStyleSheet(R"(
		QWidget {
			background-color: #5fa8d3;
			border-radius: 90px;
		}

		QLabel {
			color: white;
			font-weight: bold;
			font-size: 22pt;
		}
	)");

	return profitWidget;
}
