#pragma once
#include <QWidget>

class QLabel;
class QStackedWidget;
class QVBoxLayout;
class Database;
class QScrollArea;
class QPaintEvent;
class AddContentWidget;
class ContentHeaderWidget;

class Content : public QWidget {
	Q_OBJECT
public:
	explicit Content(QWidget* parent = nullptr);

	void BindDependencies();

	void paintEvent(QPaintEvent* event) override;

	void UpdateContent(Database* db);

private:
	QVBoxLayout* m_layout = nullptr;
	QVBoxLayout* contentLayout = nullptr;
	QVBoxLayout* invoiceLayout = nullptr;
	QWidget* contentWidget = nullptr;
	QScrollArea* scrollArea = nullptr;
	QStackedWidget* stackedWidget = nullptr;
	AddContentWidget* addContentWidget = nullptr;
	ContentHeaderWidget* headerWidget = nullptr;


	void TestFillupContent();
	QLabel* SetupTitleLabel();
	void SetupScrollArea();
	void SetupWidget();
	void SetupContentWidget();
};
