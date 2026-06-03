#include "Content/Content.h"
#include "Content/ContentHeaderWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include "Database/Database.h"
#include <QStyleOption>
#include <QPainter>
#include <QScrollArea>
#include "Invoice/InvoiceWidget.h"
#include <QStackedWidget>
#include "Content/AddContentWidget.h"


Content::Content(QWidget* parent) : QWidget(parent)
{
	addContentWidget = new AddContentWidget(stackedWidget);
	SetupWidget();
	BindDependencies();
}

void Content::BindDependencies()
{
	connect(addContentWidget, &AddContentWidget::BackRequested,
		this, [this]() {
		stackedWidget->setCurrentWidget(contentWidget);
	});

	connect(headerWidget, &ContentHeaderWidget::AddButtonClicked,
		this, [this]() {
		stackedWidget->setCurrentWidget(addContentWidget);
	});
}

void Content::UpdateContent(Database* db) {
	QVector<Invoice> invoices = db->getAllInvoices();
	
	TestFillupContent();

	for(const Invoice& invoce : invoices){
		InvoiceWidget* widget = new InvoiceWidget(invoce, scrollArea->widget());

		invoiceLayout->addWidget(widget);
	}
}

void Content::SetupWidget()
{
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(20, 0, 20, 10);
	m_layout->setSpacing(0);

	stackedWidget = new QStackedWidget(this);

	SetupContentWidget();

	QLabel* title = SetupTitleLabel();
	headerWidget = new ContentHeaderWidget(contentWidget);
	SetupScrollArea();

	stackedWidget->addWidget(contentWidget);
	stackedWidget->addWidget(addContentWidget);

	m_layout->addWidget(stackedWidget);

	contentLayout->addWidget(title);
	contentLayout->addWidget(headerWidget);
	contentLayout->addWidget(scrollArea,4);
}

void Content::SetupContentWidget()
{
	contentWidget = new QWidget(stackedWidget);
	contentWidget->setObjectName("contentWidget");

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

		InvoiceWidget* testwidget = new InvoiceWidget(test, scrollArea->widget());
		invoiceLayout->addWidget(testwidget);
	}
}

QLabel* Content::SetupTitleLabel()
{
	QLabel* label = new QLabel("Számlák", contentWidget);
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet(R"(
	font-size: 32pt;
	color: black;
	font-weight: bold;
	)");
	return label;
}

void Content::SetupScrollArea()
{
	scrollArea = new QScrollArea(contentWidget);
	QWidget* invoiceWidget = new QWidget(scrollArea);
	invoiceLayout = new QVBoxLayout(invoiceWidget);
	invoiceLayout->setContentsMargins(0, 0, 0, 0);
	invoiceLayout->setSpacing(0);

	scrollArea->setWidget(invoiceWidget);
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
}
