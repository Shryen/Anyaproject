#include "Content/Content.h"
#include "Content/ContentHeaderWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include "Database/Database.h";
#include <QStyleOption>
#include <QPainter>
#include <QScrollArea>
#include "Invoice/InvoiceWidget.h"


Content::Content(QWidget* parent) : QWidget(parent)
{
	SetupMainLayout();
}

void Content::UpdateContent(Database* db) {
	QVector<Invoice> invoices = db->getAllInvoices();
	
	TestFillupContent();

	for(const Invoice& invoce : invoices){
		InvoiceWidget* widget = new InvoiceWidget(invoce, contentWidget);

		contentLayout->addWidget(widget);
	}
}

void Content::SetupMainLayout()
{
	// Label
	QLabel* label = new QLabel("Számlák", this);
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet(R"(
	font-size: 32pt;
	color: black;
	font-weight: bold;
	)");

	SetupContentWidget();

	scrollArea = new QScrollArea(this);
	scrollArea->setWidget(contentWidget);
	scrollArea->setWidgetResizable(true);
	scrollArea->setStyleSheet(R"(
		QScrollArea {
			background-color: transparent;
			border: none;
		}

		QScrollBar:vertical {
			background-color: rgba(0, 0, 0, 0.05);
			width: 12px;
			margin-left: 2px;
			border: none,
		}

		QScrollBar::handle:vertical {
			background-color: #5fa8d3;
			min-height: 32px;
			border-radius: 6px;
		}

		QScrollBar::handle:vertical:hover {
			background-color: #4f98c3;
		}

		QScrollBar::add-line:vertical,
		QScrollBar::sub-line:vertical {
			height: 0;
			background: none;
			border: none;
		}

		QScrollBar::add-page:vertical,
		QScrollBar::sub-page:vertical {
			background: transparent;
		}
	)");

	// Layout
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(20, 0, 20, 10);
	m_layout->setSpacing(0);

	ContentHeaderWidget* HeaderWidget = new ContentHeaderWidget(this);

	m_layout->addWidget(label,1);
	m_layout->addWidget(HeaderWidget);
	m_layout->addWidget(scrollArea,4);
}

void Content::SetupContentWidget()
{
	contentWidget = new QWidget(this);
	contentWidget->setObjectName("contentWidget");

	setStyleSheet(R"(
		#contentWidget {
			border: 1px solid rgba(0, 0, 0, 0.3);
ű			border-radius: 10px;
		}
	)");

	contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(10, 10, 10, 10);
}


void Content::paintEvent(QPaintEvent* event)
{
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(
		QStyle::PE_Widget, &o, &p, this);
}


void Content::TestFillupContent() {
	for (int i = 0; i < 50; ++i) {
		Invoice test;
		test.id = i;
		test.nev = QString("Név %1").arg(i);
		test.osszeg = i * 1000;
		test.datum = QString("2024-06-%1").arg(i % 30 + 1, 2, 10, QChar('0'));

		InvoiceWidget* testwidget = new InvoiceWidget(test, this);
		contentLayout->addWidget(testwidget);
	}
}
