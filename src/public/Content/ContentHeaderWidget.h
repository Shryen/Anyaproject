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
	void DeleteButtonClicked();
	void SortChanged(int sortOption);
	void SearchChanged(const QString& filter);
	void MonthChanged(int month, int year);

private:
	QWidget* CreateToolBarWidget();
	QPushButton* CreateAddButton(QWidget* parent = nullptr);
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


	QString ButtonStyling = R"(
		QPushButton {
			font-size: 22pt;
			font-weight: bold;
			color: #f0ead6;
			background-color: #5fa8d3;
			border-radius: 8px;
			border: 2px solid #4f98c3;
			padding: 0px;
			text-align: center;
		}

		QPushButton:hover {
			background-color: #4f98c3;
			border-color: #3f88b3;
		}

		QPushButton:pressed {
			background-color: #3f88b3;
			border-color: #2f789f;
		})";
};
