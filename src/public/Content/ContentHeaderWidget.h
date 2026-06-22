#pragma once
#include <QDate>
#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;
class QLineEdit;

class ContentHeaderWidget : public QWidget {
	Q_OBJECT
public:
	explicit ContentHeaderWidget(QWidget* parent = nullptr);

	void SetupSortComboBox();

	void UpdateProfit(const QString& profit);

signals:
	void AddButtonClicked();
	void EditButtonClicked();
	void DeleteButtonClicked();
	void SortChanged(int sortOption);
	void SearchChanged(const QString& filter);
	void MonthChanged(int month, int year);

private:
	QWidget* CreateToolBarWidget();
	QPushButton* CreateAddButton(QWidget* parent = nullptr);
	QPushButton* CreateEditButton(QWidget* parent = nullptr);
	QPushButton* CreateDeleteButton(QWidget* parent = nullptr);

	QWidget* CreateHeaderWidget();
	QWidget* CreateProfitWidget();

	QComboBox* SortComboBox;
	QDate currentDate;

	QLineEdit* searchLineEdit = nullptr;
	QLineEdit* CreateSearchLineEdit(QWidget* parent = nullptr);

	void UpdateMonthLabel();
	QWidget* CreateMonthWidget();
	QPushButton* monthLeftButton = nullptr;
	QLabel* monthLabel = nullptr;
	QPushButton* monthRightButton = nullptr;

	QLabel* profitLabel;

	QString NavyButtonStyle = R"(
		QPushButton {
			font-size: 22pt;
			font-weight: bold;
			color: white;
			background-color: #1B365D;
			border-radius: 8px;
			border: none;
			padding: 0px;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #2C5282;
		}
		QPushButton:pressed {
			background-color: #14294A;
		})";

	QString GreenButtonStyle = R"(
		QPushButton {
			font-size: 22pt;
			font-weight: bold;
			color: white;
			background-color: #059669;
			border-radius: 8px;
			border: none;
			padding: 0px;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #047857;
		}
		QPushButton:pressed {
			background-color: #065F46;
		})";
};
