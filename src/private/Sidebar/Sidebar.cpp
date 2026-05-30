#include "Sidebar/Sidebar.h"

#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
#include <QVBoxLayout>

Sidebar::Sidebar(QWidget* parent) : QWidget(parent)
{
	SetupTitleLabel();
	SetupButtons();

	SetupSidebarStyle();
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(5, 20, 5, 20);
	layout->setSpacing(10);
	layout->addWidget(titleLabel);
	layout->addWidget(receiptsButton);
	layout->addWidget(profitsButton);
	setFixedWidth(220);

	layout->addStretch();
}

void Sidebar::SetupButtons()
{
	receiptsButton = new QPushButton("Receipts", this);
	profitsButton = new QPushButton("Profits", this);

	QString buttonStyle = R"(
		QPushButton{
			background-color: transparent;
			border: 2px solid white;
			border-radius: 10px;
			padding: 10px;
			font-size: 18px;
		}
		QPushButton:hover {
			background-color: rgba(255, 255, 255, 0.1);
		}
	)";

	receiptsButton->setCursor(Qt::PointingHandCursor);
	profitsButton->setCursor(Qt::PointingHandCursor);

	receiptsButton->setStyleSheet(buttonStyle);
	profitsButton->setStyleSheet(buttonStyle);
}

void Sidebar::SetupTitleLabel()
{
	titleLabel = new QLabel("Számlák", this);
	titleLabel->setStyleSheet(R"(
		background-color: transparent;
		font-size: 36px;
		width: 100%;
		font-weight: bold;
	)");
	titleLabel->setAlignment(Qt::AlignCenter);
}

void Sidebar::SetupSidebarStyle()
{
	this->setStyleSheet(R"(
		Sidebar{
			background-color: #5fa8d3;
		}
	)");
}

void Sidebar::paintEvent(QPaintEvent* event)
{
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
