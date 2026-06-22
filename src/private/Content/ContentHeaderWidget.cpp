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
	layout->setContentsMargins(0, 10, 0, 0);
	layout->setSpacing(16);

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
			color: #4A5568;
			background-color: white;
			border: 2px solid #1B365D;
			border-radius: 6px;
			padding: 6px 28px 6px 10px;
			font-size: 13pt;
			font-weight: bold;
		}
		QComboBox#sortComboBox:hover {
			border-color: #2C5282;
		}
		QComboBox#sortComboBox:focus {
			border-color: #059669;
		}
		QComboBox#sortComboBox::drop-down {
			subcontrol-origin: padding;
			subcontrol-position: top right;
			width: 28px;
			border-left: 1px solid #1B365D;
			border-top-right-radius: 4px;
			border-bottom-right-radius: 4px;
			background-color: #1B365D;
		}
		QComboBox#sortComboBox::down-arrow {
			width: 0px;
			height: 0px;
			border-left: 5px solid transparent;
			border-right: 5px solid transparent;
			border-top: 6px solid white;
		}
		QComboBox#sortComboBox QAbstractItemView {
			color: #4A5568;
			background-color: white;
			border: 1px solid #1B365D;
			selection-background-color: #1B365D;
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
	QGridLayout* grid = new QGridLayout(buttonWidget);
	grid->setContentsMargins(0, 10, 0, 10);
	grid->setColumnStretch(0, 1);
	grid->setColumnStretch(2, 1);

	QWidget* leftWidget = new QWidget(buttonWidget);
	QHBoxLayout* leftLayout = new QHBoxLayout(leftWidget);
	leftLayout->setContentsMargins(0, 0, 0, 0);
	leftLayout->addWidget(CreateSearchLineEdit(leftWidget));

	QWidget* rightWidget = new QWidget(buttonWidget);
	QHBoxLayout* rightLayout = new QHBoxLayout(rightWidget);
	rightLayout->setContentsMargins(0, 0, 0, 0);
	rightLayout->addWidget(SortComboBox);
	rightLayout->addWidget(CreateAddButton(rightWidget));
	rightLayout->addWidget(CreateEditButton(rightWidget));
	rightLayout->addWidget(CreateDeleteButton(rightWidget));

	grid->addWidget(leftWidget, 0, 0, Qt::AlignLeft);
	grid->addWidget(CreateMonthWidget(), 0, 1, Qt::AlignCenter);
	grid->addWidget(rightWidget, 0, 2, Qt::AlignRight);

	return buttonWidget;
}

QPushButton* ContentHeaderWidget::CreateAddButton(QWidget* buttonWidget)
{
	QPushButton* addButton = new QPushButton("+", buttonWidget);
	addButton->setStyleSheet(GreenButtonStyle);
	addButton->setFixedSize(QSize{ 50,50 });
	addButton->setCursor(Qt::PointingHandCursor);

	connect(addButton, &QPushButton::clicked, this, &ContentHeaderWidget::AddButtonClicked);

	return addButton;
}

QPushButton* ContentHeaderWidget::CreateEditButton(QWidget* parent)
{
	QPushButton* editButton = new QPushButton("/", parent);
	editButton->setStyleSheet(NavyButtonStyle);
	editButton->setFixedSize(QSize{ 50,50 });
	editButton->setCursor(Qt::PointingHandCursor);
	connect(editButton, &QPushButton::clicked, this, &ContentHeaderWidget::EditButtonClicked);

	return editButton;
}

QPushButton* ContentHeaderWidget::CreateDeleteButton(QWidget* parent)
{
	QPushButton* deleteButton = new QPushButton("x", parent);
	deleteButton->setStyleSheet(NavyButtonStyle);
	deleteButton->setFixedSize(QSize{ 50,50 });
	deleteButton->setCursor(Qt::PointingHandCursor);
	connect(deleteButton, &QPushButton::clicked, this, &ContentHeaderWidget::DeleteButtonClicked);
	return deleteButton;
}

QWidget* ContentHeaderWidget::CreateHeaderWidget()
{
	QWidget* HeaderWidget = new QWidget(this);
	HeaderWidget->setStyleSheet(R"(
		QWidget {
			border-bottom: 2px solid rgba(255, 255, 255, 0.2);
			background-color: #1B365D;
		}
	)");

	QLabel* idLabel = new QLabel("ID", HeaderWidget);
	QLabel* nameLabel = new QLabel("Név", HeaderWidget);
	QLabel* amountLabel = new QLabel("Összeg", HeaderWidget);
	QLabel* dateLabel = new QLabel("Dátum", HeaderWidget);

	QString headerLabelStyle = R"(
		QLabel {
			font-weight: bold;
			font-size: 18pt;
			color: white;
			padding: 8px;
		}
	)";

	idLabel->setFixedWidth(120);
	idLabel->setStyleSheet(headerLabelStyle);
	nameLabel->setMinimumWidth(200);
	nameLabel->setStyleSheet(headerLabelStyle);
	nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	amountLabel->setMinimumWidth(200);
	amountLabel->setStyleSheet(headerLabelStyle);
	amountLabel->setAlignment(Qt::AlignCenter);
	dateLabel->setMinimumWidth(200);
	dateLabel->setStyleSheet(headerLabelStyle);
	dateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QWidget* leftGroup = new QWidget(HeaderWidget);
	QHBoxLayout* leftLayout = new QHBoxLayout(leftGroup);
	leftLayout->setContentsMargins(0, 0, 0, 0);
	leftLayout->setSpacing(0);
	leftLayout->addWidget(idLabel);
	leftLayout->addWidget(nameLabel);

	QGridLayout* grid = new QGridLayout(HeaderWidget);
	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
	grid->setColumnStretch(0, 1);
	grid->setColumnStretch(2, 1);

	grid->addWidget(leftGroup, 0, 0, Qt::AlignLeft);
	grid->addWidget(amountLabel, 0, 1, Qt::AlignCenter);
	grid->addWidget(dateLabel, 0, 2, Qt::AlignRight);

	return HeaderWidget;
}

QWidget* ContentHeaderWidget::CreateProfitWidget()
{
	QWidget* profitWidget = new QWidget(this);
	profitWidget->setFixedSize(250, 250);

	profitLabel = new QLabel("Bevétel: 0 €", profitWidget);
	profitLabel->setAlignment(Qt::AlignCenter);
	profitLabel->setWordWrap(true);

	QHBoxLayout* layout = new QHBoxLayout(profitWidget);
	layout->addWidget(profitLabel);
	layout->setContentsMargins(15, 0, 15, 0);
	layout->setAlignment(Qt::AlignCenter);

	profitWidget->setStyleSheet(R"(
		QWidget {
			background-color: #1B365D;
			border-radius: 125px;
		}
		QLabel {
			color: white;
			font-weight: bold;
			font-size: 18pt;
		}
	)");

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(profitWidget);
	shadow->setBlurRadius(30);
	shadow->setColor(QColor("#1B365D"));
	shadow->setOffset(0, 4);
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
			color: #1B365D;
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
			color: #1B365D;
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
			color: #1B365D;
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
			color: #4A5568;
			background-color: white;
			border: 2px solid #1B365D;
			border-radius: 6px;
			padding: 6px 10px;
		}
		QLineEdit:focus {
			border-color: #059669;
			background-color: white;
		}
		QLineEdit::placeholder {
			color: #A0AEC0;
		}
	)");

	connect(searchLineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
		emit SearchChanged(text);
		});

	return searchLineEdit;
}
