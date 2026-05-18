#include <QVBoxLayout>
#include <QPushButton>
#include "Sidebar/Sidebar.h"
#include <QStyleOption>
#include <QPainter>

Sidebar::Sidebar(QWidget* parent) : QWidget(parent)
{
	receiptsButton = new QPushButton("Receipts", this);
	profitsButton = new QPushButton("Profits", this);

	SetupSidebarStyle();
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(5, 20, 5, 20);
	layout->setSpacing(10);
	layout->addWidget(receiptsButton);
    layout->addWidget(profitsButton);
	setFixedWidth(220);

    layout->addStretch();
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
	style()->drawPrimitive(
		QStyle::PE_Widget, &o, &p, this);
}
