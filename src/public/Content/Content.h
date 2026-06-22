#pragma once
#include <QDate>
#include <QWidget>
#include "Invoice.h"

class QLabel;
class QStackedWidget;
class QTimer;
class QVBoxLayout;
class Database;
class QScrollArea;
class QPaintEvent;
class AddContentWidget;
class EditContentWidget;
class ContentHeaderWidget;

enum class SortType {
	ById,
	ByName,
	ByAmount,
	ByDate
};

class Content : public QWidget {
	Q_OBJECT
public:
	explicit Content(QWidget* parent = nullptr);

	void BindDependencies();

	void paintEvent(QPaintEvent* event) override;

	void UpdateContent(Database* db);

	void SetProfitSum(const QString& profit);

signals:
	void AddToDatabaseRequested(const Invoice& data);
	void DeleteFromDatabaseRequested();
	void EditFromDatabaseRequested(const Invoice& data);
	void OnListChanged();
	void InvoiceSelected(int invoiceId);


private slots:
	void OnInvoiceSelected(int invoiceId);
	void OnSearchChanged(const QString& filter);
	void OnMonthChanged(int month, int year);

private:
	QVBoxLayout* m_layout = nullptr;
	QVBoxLayout* contentLayout = nullptr;
	QVBoxLayout* invoiceLayout = nullptr;
	QWidget* contentWidget = nullptr;
	QScrollArea* scrollArea = nullptr;
	QStackedWidget* stackedWidget = nullptr;
	QTimer* searchTimer = nullptr;
	AddContentWidget* addContentWidget = nullptr;
	EditContentWidget* editContentWidget = nullptr;
	ContentHeaderWidget* headerWidget = nullptr;


	QLabel* SetupTitleLabel();
	void SetupScrollArea();
	void SetupWidget();
	void SetupContentWidget();

	// Searching and filtering
	int selectedInvoiceId = -1;
	int previousSelectedId = -1;
	SortType currentSort = SortType::ById;
	QVector<Invoice> invoiceCache;
	QString currentSearchFilter;
	int currentMonth{ QDate::currentDate().month() };
	int currentYear{ QDate::currentDate().year() };
};
