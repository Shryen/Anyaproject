#pragma once
#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;

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

private:
	QWidget* CreateButtonWidget();
	QPushButton* CreateAddButton(QWidget* parent = nullptr);
	QPushButton* CreateDeleteButton(QWidget* parent = nullptr);

	QWidget* CreateHeaderWidget();
	QWidget* CreateProfitWidget();

	QComboBox* SortComboBox;

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
