#pragma once
#include <QWidget>

class QVBoxLayout;
class Database;

class Content : public QWidget {
	Q_OBJECT
public:
	explicit Content(QWidget* parent = nullptr);

	void SetupMainLayout();

	void SetupContentWidget();

	void paintEvent(QPaintEvent* event) override;

	void UpdateContent(Database* db);

private:
	QVBoxLayout* m_layout = nullptr;
	QVBoxLayout* contentLayout = nullptr;
	QWidget* contentWidget = nullptr;

	void TestFillupContent();
};