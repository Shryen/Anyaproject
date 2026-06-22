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
#include "Content/EditContentWidget.h"
#include <QDate>
#include <QTimer>


Content::Content(QWidget* parent) : QWidget(parent)
{
	addContentWidget = new AddContentWidget(stackedWidget);
	editContentWidget = new EditContentWidget(stackedWidget);

	searchTimer = new QTimer(this);
	searchTimer->setSingleShot(true);
	searchTimer->setInterval(150);
	connect(searchTimer, &QTimer::timeout, this, [this]() {
		OnSearchChanged(currentSearchFilter);
	});

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

	connect(editContentWidget, &EditContentWidget::BackRequested,
		this, [this]() {
		stackedWidget->setCurrentWidget(contentWidget);
	});

	connect(editContentWidget, &EditContentWidget::EditRequested, this, [this](const Invoice& Data) {
		emit EditFromDatabaseRequested(Data);
		stackedWidget->setCurrentWidget(contentWidget);
	});

	connect(headerWidget, &ContentHeaderWidget::EditButtonClicked,
		this, [this]() {
		for (const Invoice& inv : invoiceCache) {
			if (inv.id == selectedInvoiceId) {
				editContentWidget->LoadInvoice(inv);
				stackedWidget->setCurrentWidget(editContentWidget);
				break;
			}
		}
	});

	connect(headerWidget, &ContentHeaderWidget::DeleteButtonClicked,
		this, [this]() {
		emit DeleteFromDatabaseRequested();
	});

	connect(headerWidget, &ContentHeaderWidget::SortChanged, this, [this](int sortOption) {
		currentSort = static_cast<SortType>(sortOption);
		emit OnListChanged();
	});

	connect(headerWidget, &ContentHeaderWidget::SearchChanged, this, [this](const QString& filter) {
		currentSearchFilter = filter;
		searchTimer->start();
	});

	connect(headerWidget, &ContentHeaderWidget::MonthChanged, this, &Content::OnMonthChanged);
}

void Content::UpdateContent(Database* db) {
	while (QLayoutItem* item = invoiceLayout->takeAt(0)) {
		if (QWidget* widget = item->widget()) {
			widget->deleteLater();
		}
		delete item;
	}

	invoiceCache = db->getAllInvoices();

	switch (currentSort) {
		case SortType::ById:
			std::sort(invoiceCache.begin(), invoiceCache.end(), [](const Invoice& a, const Invoice& b) {
				return a.id > b.id;
			});
		break;
		case SortType::ByName:
			std::sort(invoiceCache.begin(), invoiceCache.end(), [](const Invoice& a, const Invoice& b) {
				return a.nev < b.nev;
			});
			break;
		case SortType::ByAmount:
			std::sort(invoiceCache.begin(), invoiceCache.end(), [](const Invoice& a, const Invoice& b) {
				return a.osszeg > b.osszeg;
			});
			break;
		case SortType::ByDate:
			std::sort(invoiceCache.begin(), invoiceCache.end(), [](const Invoice& a, const Invoice& b) {
				return a.datum > b.datum;
			});
			break;
	}


	for(const Invoice& invoice : invoiceCache){
		InvoiceWidget* widget = new InvoiceWidget(invoice, scrollArea->widget());
		invoiceLayout->addWidget(widget);

		connect(widget, &InvoiceWidget::InvoiceSelected, this, &Content::OnInvoiceSelected);
	}

	previousSelectedId = -1;
	OnSearchChanged(currentSearchFilter);
	OnMonthChanged(currentMonth, currentYear);
}

void Content::OnSearchChanged(const QString& filter)
{
	QWidget* container = scrollArea->widget();
	container->setUpdatesEnabled(false);

	for (int i = 0; i < invoiceLayout->count(); ++i) {
		InvoiceWidget* widgetAtIndex = qobject_cast<InvoiceWidget*>(invoiceLayout->itemAt(i)->widget());
		if (!widgetAtIndex) continue;

		bool monthMatch = widgetAtIndex->GetInvoiceYear() == currentYear
			&& widgetAtIndex->GetInvoiceMonth() == currentMonth;
		bool searchMatch = filter.isEmpty() || invoiceCache[i].nev.contains(filter, Qt::CaseInsensitive);

		widgetAtIndex->setVisible(monthMatch && searchMatch);
	}

	container->setUpdatesEnabled(true);
}

void Content::OnMonthChanged(int month, int year)
{
	currentMonth = month;
	currentYear = year;

	QWidget* container = scrollArea->widget();
	container->setUpdatesEnabled(false);

	for (int i = 0; i < invoiceLayout->count(); ++i) {
		InvoiceWidget* widgetAtIndex = qobject_cast<InvoiceWidget*>(invoiceLayout->itemAt(i)->widget());
		if (!widgetAtIndex) continue;

		bool monthMatch = widgetAtIndex->GetInvoiceYear() == year
			&& widgetAtIndex->GetInvoiceMonth() == month;
		bool searchMatch = currentSearchFilter.isEmpty()
			|| invoiceCache[i].nev.contains(currentSearchFilter, Qt::CaseInsensitive);

		widgetAtIndex->setVisible(monthMatch && searchMatch);
	}

	container->setUpdatesEnabled(true);
}

void Content::OnInvoiceSelected(int InvoiceId){
	selectedInvoiceId = InvoiceId;
	emit InvoiceSelected(InvoiceId);

	QWidget* container = scrollArea->widget();
	container->setUpdatesEnabled(false);

	QString selectedStyle = R"(
		InvoiceWidget {
			border: 2px solid #1B365D;
			background-color: rgba(27, 54, 93, 0.08);
		}
		QLabel {
			color: #1B365D;
			font-size: 16pt;
			font-weight: bold;
			border-bottom: 1px solid rgba(27, 54, 93, 0.15);
			padding: 8px;
		}
	)";

	QString unselectedStyle = R"(
		QLabel {
			color: #4A5568;
			font-size: 16pt;
			border-bottom: 1px solid rgba(74, 85, 104, 0.15);
			padding: 8px;
		}
	)";

	for (int i = 0; i < invoiceLayout->count(); ++i) {
		InvoiceWidget* w = qobject_cast<InvoiceWidget*>(invoiceLayout->itemAt(i)->widget());
		if (!w) continue;
		int wid = w->GetInvoiceId();
		if (wid == InvoiceId || wid == previousSelectedId) {
			w->setStyleSheet(wid == InvoiceId ? selectedStyle : unselectedStyle);
			w->style()->unpolish(w);
			w->style()->polish(w);
			w->update();
		}
	}

	previousSelectedId = InvoiceId;
	container->setUpdatesEnabled(true);
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
	stackedWidget->addWidget(editContentWidget);

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
	label->setAlignment(Qt::AlignLeft);
	label->setStyleSheet(R"(
	font-size: 32pt;
	color: #1B365D;
	font-weight: bold;
	)");
	return label;
}

void Content::SetProfitSum(const QString& profit)
{
	headerWidget->UpdateProfit(profit);
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
			background-color: rgba(74, 85, 104, 0.08);
			width: 10px;
			border: none;
		}

		QScrollBar::handle:vertical {
			background-color: #1B365D;
			min-height: 32px;
			border-radius: 5px;
		}

		QScrollBar::handle:vertical:hover {
			background-color: #2C5282;
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
