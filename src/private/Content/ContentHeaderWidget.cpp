#include "Content/ContentHeaderWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

ContentHeaderWidget::ContentHeaderWidget(QWidget* parent)
	: QWidget(parent)
{
	SetupSortComboBox();

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	layout->addWidget(CreateProfitWidget(), 0, Qt::AlignHCenter);
	layout->addWidget(CreateAddButtonWidget());
	layout->addWidget(CreateHeaderWidget());
}

void ContentHeaderWidget::SetupSortComboBox()
{
	SortComboBox = new QComboBox(this);
	SortComboBox->setObjectName("sortComboBox");
	SortComboBox->setFixedHeight(50);
	SortComboBox->setMinimumWidth(180);
	SortComboBox->addItem("Rendezés: ");
	SortComboBox->addItem("Név szerint");
	SortComboBox->addItem("Összeg szerint");
	SortComboBox->addItem("Dátum szerint");

	connect(SortComboBox, &QComboBox::currentIndexChanged,
		this, [this](int sortOption) {
		emit SortChanged(sortOption);
	});




	SortComboBox->setStyleSheet(R"(
		QComboBox#sortComboBox {
			color: rgba(0, 0, 0, 0.75);
			background-color: #fff5ee;
			border: 2px solid #5fa8d3;
			border-radius: 6px;
			padding: 6px 28px 6px 10px;
			font-size: 13pt;
			font-weight: bold;
		}

		QComboBox#sortComboBox:hover {
			background-color: white;
			border-color: #4f98c3;
		}

		QComboBox#sortComboBox:focus {
			border-color: #3f88b3;
		}

		QComboBox#sortComboBox::drop-down {
			subcontrol-origin: padding;
			subcontrol-position: top right;
			width: 28px;
			border-left: 1px solid #5fa8d3;
			border-top-right-radius: 4px;
			border-bottom-right-radius: 4px;
			background-color: #5fa8d3;
		}

		QComboBox#sortComboBox::down-arrow {
			width: 0px;
			height: 0px;
			border-left: 5px solid transparent;
			border-right: 5px solid transparent;
			border-top: 6px solid #f0ead6;
		}

		QComboBox#sortComboBox QAbstractItemView {
			color: black;
			background-color: white;
			border: 1px solid #5fa8d3;
			selection-background-color: #5fa8d3;
			selection-color: white;
			outline: none;
			font-size: 12pt;
		}
	)");
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

	addButton->setCursor(Qt::PointingHandCursor);
	connect(addButton, &QPushButton::clicked, this, &ContentHeaderWidget::AddButtonClicked);

	buttonLayout->addStretch();
	buttonLayout->addWidget(SortComboBox);
	buttonLayout->addWidget(addButton);


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
