#pragma once
#include "Buttons/AddButton.h"

void AddButton::setupStyle(){
    setStyleSheet(R"(
            QPushButton {
                background-color: #4CAF50;
                color: white;
                padding: 10px 20px;
                border-radius: 5px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        )");
}