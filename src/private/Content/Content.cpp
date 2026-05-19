#include "Content/Content.h"
#include <QVBoxLayout>
#include <QLabel>
#include "Database/Database.h";
#include <QStyleOption>
#include <QPainter>

Content::Content(QWidget* parent) : QWidget(parent)
{
	SetupMainLayout();
}

void Content::UpdateContent(Database* db) {
	QVector<Szamla> invoices = db->getAllInvoices();

	for(const Szamla& invoce : invoices){
		QLabel* label = new QLabel(QString("ID: %1, Név: %2, Összeg: %3, Dátum: %4")
			.arg(invoce.id)
			.arg(invoce.nev)
			.arg(invoce.osszeg)
			.arg(invoce.datum), this);

		label->setStyleSheet("color: black; font-size: 24pt;");

		contentLayout->addWidget(label);
	}
}

void Content::SetupMainLayout()
{
	QLabel* label = new QLabel("content test", this);
	label->setAlignment(Qt::AlignCenter);

	SetupContentWidget();

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(20, 0, 20, 10);
	m_layout->setSpacing(0);

	m_layout->addWidget(label, 1);
	m_layout->addWidget(contentWidget, 3);

	label->setStyleSheet(R"(
	font-size: 24px;
	color: black;
	)");
}

void Content::SetupContentWidget()
{
	contentWidget = new QWidget(this);
	contentWidget->setObjectName("contentWidget");
	setStyleSheet(R"(#contentWidget {
		border: 1px solid rgba(0,0,0,0.4);	
		border-radius: 5px;
		}
	)");

	contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(10, 10, 10, 10);
	contentLayout->setSpacing(10);
}


void Content::paintEvent(QPaintEvent* event)
{
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(
		QStyle::PE_Widget, &o, &p, this);
}
