#pragma once
#include <QWidget>

class ContentHeaderWidget : public QWidget {
	Q_OBJECT
public:
	explicit ContentHeaderWidget(QWidget* parent = nullptr);

signals:
	void AddButtonClicked();

private:
	QWidget* CreateAddButtonWidget();
	QWidget* CreateHeaderWidget();
	QWidget* CreateProfitWidget();
};
