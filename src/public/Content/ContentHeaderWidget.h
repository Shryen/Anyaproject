#pragma once
#include <QWidget>

class ContentHeaderWidget : public QWidget {
public:
	explicit ContentHeaderWidget(QWidget* parent = nullptr);

private:
	QWidget* CreateAddButtonWidget();
	QWidget* CreateHeaderWidget();
	QWidget* CreateProfitWidget();
};
