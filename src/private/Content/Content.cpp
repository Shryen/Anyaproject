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

	connect(addContentWidget, &AddContentWidget::AddRequested, this, [this](const Invoice& Data) {
		emit AddToDatabaseRequested(Data);
		stackedWidget->setCurrentWidget(contentWidget);
	});

	connect(headerWidget, &ContentHeaderWidget::AddButtonClicked,
		this, [this]() {
		stackedWidget->setCurrentWidget(addContentWidget);
	});

	connect(headerWidget, &ContentHeaderWidget::SortChanged, this, [this](int sortOption) {
		currentSort = static_cast<SortType>(sortOption);
		emit OnListChanged();
	});
}

void Content::UpdateContent(Database* db) {
	while (QLayoutItem* item = invoiceLayout->takeAt(0)) {
		if (QWidget* widget = item->widget()) {
			widget->deleteLater();
		}
		delete item;
	}

	QVector<Invoice> invoices = db->getAllInvoices();

	switch (currentSort) {
		case SortType::ById:
			std::sort(invoices.begin(), invoices.end(), [](const Invoice& a, const Invoice& b) {
				return a.id > b.id;
			});
		break;
		case SortType::ByName:
			std::sort(invoices.begin(), invoices.end(), [](const Invoice& a, const Invoice& b) {
				return a.nev < b.nev;
			});
			break;
		case SortType::ByAmount:
			std::sort(invoices.begin(), invoices.end(), [](const Invoice& a, const Invoice& b) {
				return a.osszeg > b.osszeg;
			});
			break;
		case SortType::ByDate:
			std::sort(invoices.begin(), invoices.end(), [](const Invoice& a, const Invoice& b) {
				return a.datum > b.datum;
			});
			break;
	}


	for(const Invoice& invoice : invoices){
		InvoiceWidget* widget = new InvoiceWidget(invoice, scrollArea->widget());
		invoiceLayout->addWidget(widget);

		connect(widget, &InvoiceWidget::InvoiceSelected, this, &Content::OnInvoiceSelected);
	}
}

void Content::OnInvoiceSelected(int InvoiceId){
	qDebug() << "Selected Invoice ID: " << InvoiceId;
	emit InvoiceSelected(InvoiceId);
	for (int i = 0; i < invoiceLayout->count(); ++i) {
		InvoiceWidget* widgetAtIndex = qobject_cast<InvoiceWidget*>(invoiceLayout->itemAt(i)->widget());
		if (!widgetAtIndex) continue;

		if (widgetAtIndex->GetInvoiceId() == InvoiceId)
			widgetAtIndex->setStyleSheet(R"(
                InvoiceWidget {
                    border: 2px solid #5fa8d3;
                    background-color: rgba(95, 168, 211, 0.5);
                }
                QLabel {
                    color: black;
                    font-size: 16pt;
                    border-bottom: 1px solid rgba(0, 0, 0, 0.3);
                    padding: 8px;
                }
            )");
		else
			widgetAtIndex->setStyleSheet(R"(
                QLabel {
                    color: black;
                    font-size: 16pt;
                    border-bottom: 1px solid rgba(0, 0, 0, 0.3);
                    padding: 8px;
                }
            )");

		widgetAtIndex->style()->unpolish(widgetAtIndex);
		widgetAtIndex->style()->polish(widgetAtIndex);
		widgetAtIndex->update();
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
