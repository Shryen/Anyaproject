#pragma once
#include "Buttons/MainButton.h"

class AddButton : public MainButton {
public:
	explicit AddButton(const QString& text, QWidget* parent = nullptr) : MainButton("Add", parent) {}
    void onClick() override {
        qDebug() << "Add button clicked!";
    }
    void setupStyle() override;
};