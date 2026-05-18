#include "Buttons/MainButton.h"

MainButton::MainButton(const QString& text, QWidget* parent) : QPushButton(text, parent), buttonText(text) {
	connect(this, &QPushButton::clicked, this, &MainButton::onButtonClicked);
	setupStyle();
}

void MainButton::onButtonClicked() {
	onClick();
	emit buttonPressed();
}

void MainButton::setupStyle() {
		setStyleSheet(R"(
		QPushButton {
			background-color: #007bff;
			color: white;
			border: none;
			border-radius: 5px;
			padding: 10px 20px;
			font-size: 16px;
		}
		QPushButton:hover {
			background-color: #0056b3;
		}
	)");

}