#include "Content/ContentHeaderWidget.h"

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDate>
#include <QLocale>

ContentHeaderWidget::ContentHeaderWidget(QWidget* parent)
	: QWidget(parent)
{
	currentDate = QDate::currentDate();
	SetupSortComboBox();

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	layout->addWidget(CreateProfitWidget(), 0, Qt::AlignHCenter);
	layout->addWidget(CreateToolBarWidget());
	layout->addWidget(CreateHeaderWidget());

	UpdateMonthLabel();
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

void ContentHeaderWidget::UpdateProfit(const QString& profit)
{
	profitLabel->setText(QString("Bevétel: %1€").arg(profit));
}

QWidget* ContentHeaderWidget::CreateToolBarWidget()
{
	QWidget* buttonWidget = new QWidget(this);
	QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
	buttonLayout->setContentsMargins(0, 10, 0, 10);

	QPushButton* addButton = CreateAddButton(buttonWidget);
	QPushButton* editButton = CreateEditButton(buttonWidget);
	QPushButton* deleteButton = CreateDeleteButton(buttonWidget);

	buttonLayout->addWidget(CreateSearchLineEdit(buttonWidget));
	buttonLayout->addStretch();
	buttonLayout->addWidget(CreateMonthWidget());
	buttonLayout->addStretch();
	buttonLayout->addWidget(SortComboBox);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(editButton);
	buttonLayout->addWidget(deleteButton);

	return buttonWidget;
}

QPushButton* ContentHeaderWidget::CreateAddButton(QWidget* buttonWidget)
{
	QPushButton* addButton = new QPushButton("+", buttonWidget);
	addButton->setStyleSheet(ButtonStyling);
	addButton->setFixedSize(QSize{ 50,50 });
	addButton->setCursor(Qt::PointingHandCursor);

	connect(addButton, &QPushButton::clicked, this, &ContentHeaderWidget::AddButtonClicked);

	return addButton;
}

QPushButton* ContentHeaderWidget::CreateEditButton(QWidget* parent)
{
	QPushButton* editButton = new QPushButton("/", parent);
	editButton->setStyleSheet(ButtonStyling);
	editButton->setFixedSize(QSize{ 50,50 });
	editButton->setCursor(Qt::PointingHandCursor);
	connect(editButton, &QPushButton::clicked, this, &ContentHeaderWidget::EditButtonClicked);

	return editButton;
}

QPushButton* ContentHeaderWidget::CreateDeleteButton(QWidget* parent)
{
	QPushButton* deleteButton = new QPushButton("x", parent);
	deleteButton->setStyleSheet(ButtonStyling);
	deleteButton->setFixedSize(QSize{ 50,50 });
	deleteButton->setCursor(Qt::PointingHandCursor);
	connect(deleteButton, &QPushButton::clicked, this, &ContentHeaderWidget::DeleteButtonClicked);
	return deleteButton;
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

	profitLabel = new QLabel("Bevétel: 0 €", profitWidget);
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
			font-size: 20pt;
		}
	)");

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(profitWidget);
	shadow->setBlurRadius(20);
	shadow->setColor(QColor("#5fa8d3"));
	shadow->setOffset(0, 0);
	profitWidget->setGraphicsEffect(shadow);

	return profitWidget;
}

void ContentHeaderWidget::UpdateMonthLabel()
{
	QLocale hu(QLocale::Hungarian);
	monthLabel->setText(hu.toString(currentDate, "MMMM yyyy"));
}

QWidget* ContentHeaderWidget::CreateMonthWidget()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layout = new QHBoxLayout(widget);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	monthLeftButton = new QPushButton("<", widget);
	monthLeftButton->setFixedSize(40, 50);
	monthLeftButton->setCursor(Qt::PointingHandCursor);
	monthLeftButton->setStyleSheet(R"(
		QPushButton {
			font-size: 18pt;
			font-weight: bold;
			color: black;
			border-radius: 6px;
			padding: 0px;
		}
	)");

	connect(monthLeftButton, &QPushButton::clicked, this, [this]() {
		currentDate = currentDate.addMonths(-1);
		UpdateMonthLabel();
		emit MonthChanged(currentDate.month(), currentDate.year());
	});

	monthLabel = new QLabel(widget);
	monthLabel->setAlignment(Qt::AlignCenter);
	monthLabel->setFixedWidth(160);
	monthLabel->setFixedHeight(50);
	monthLabel->setStyleSheet(R"(
		QLabel {
			font-size: 14pt;
			font-weight: bold;
			color: #333333;
			background-color: #fff5ee;
			border-left: none;
			border-right: none;
			padding: 0px;
		}
	)");

	monthRightButton = new QPushButton(">", widget);
	monthRightButton->setFixedSize(40, 50);
	monthRightButton->setCursor(Qt::PointingHandCursor);
	monthRightButton->setStyleSheet(R"(
		QPushButton {
			font-size: 18pt;
			font-weight: bold;
			color: black;
			border-radius: 6px;
			padding: 0px;
		}
	)");

	connect(monthRightButton, &QPushButton::clicked, this, [this]() {
		currentDate = currentDate.addMonths(1);
		UpdateMonthLabel();
		emit MonthChanged(currentDate.month(), currentDate.year());
	});

	layout->addWidget(monthLeftButton);
	layout->addWidget(monthLabel);
	layout->addWidget(monthRightButton);

	return widget;
}

QLineEdit* ContentHeaderWidget::CreateSearchLineEdit(QWidget* parent)
{
	searchLineEdit = new QLineEdit(parent);
	searchLineEdit->setPlaceholderText("Keresés...");
	searchLineEdit->setFixedHeight(50);
	searchLineEdit->setMinimumWidth(250);
	searchLineEdit->setStyleSheet(R"(
		QLineEdit {
			font-size: 13pt;
			color: #333333;
			background-color: #fff5ee;
			border: 2px solid #5fa8d3;
			border-radius: 6px;
			padding: 6px 10px;
		}
		QLineEdit:focus {
			border-color: #3f88b3;
			background-color: white;
		}
	)");

	connect(searchLineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
		emit SearchChanged(text);
		});

	return searchLineEdit;
}
