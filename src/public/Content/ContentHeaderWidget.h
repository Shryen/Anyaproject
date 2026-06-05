#pragma once
#include <QWidget>

class QComboBox;

class ContentHeaderWidget : public QWidget {
	Q_OBJECT
public:
	explicit ContentHeaderWidget(QWidget* parent = nullptr);

	void SetupSortComboBox();

signals:
	void AddButtonClicked();
	void SortChanged(int sortOption);

private:
	QWidget* CreateAddButtonWidget();
	QWidget* CreateHeaderWidget();
	QWidget* CreateProfitWidget();

	QComboBox* SortComboBox;
};
