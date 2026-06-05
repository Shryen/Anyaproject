#pragma once
#include <QWidget>
#include "Invoice.h"

class QLabel;
class QStackedWidget;
class QVBoxLayout;
class Database;
class QScrollArea;
class QPaintEvent;
class AddContentWidget;
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

signals:
	void AddToDatabaseRequested(const Invoice& data);
	void OnListChanged();

private:
	QVBoxLayout* m_layout = nullptr;
	QVBoxLayout* contentLayout = nullptr;
	QVBoxLayout* invoiceLayout = nullptr;
	QWidget* contentWidget = nullptr;
	QScrollArea* scrollArea = nullptr;
	QStackedWidget* stackedWidget = nullptr;
	AddContentWidget* addContentWidget = nullptr;
	ContentHeaderWidget* headerWidget = nullptr;

	SortType currentSort = SortType::ById;

	void TestFillupContent();
	QLabel* SetupTitleLabel();
	void SetupScrollArea();
	void SetupWidget();
	void SetupContentWidget();
};
