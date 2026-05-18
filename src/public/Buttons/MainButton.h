#pragma once
#include <QPushButton>

class MainButton : public QPushButton {
	Q_OBJECT
public:
	explicit MainButton(const QString& text, QWidget* parent = nullptr);
	virtual ~MainButton() = default;

	virtual void onClick() = 0;

	virtual void setupStyle();

signals:
	void buttonPressed();

protected:
	QString buttonText;

private slots:
	void onButtonClicked();
};