#pragma once
#include "HomeWindow.h"

void setupButton(QPushButton* b, std::string&& color = "FF00000", bool rounded = true) {
    if (color[0] == '#') color.erase(0, 1);
    b->setFixedSize(100, 50);
    if (!rounded)
        b->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
    else
        b->setStyleSheet(
            QString(("background-color: #" + color + "; border-radius: 15px ;").c_str())
        );
}
void setupLabel(QLabel* label, std::string&& color = "FF00000") {
    if (color[0] == '#') color.erase(0, 1);
    QFont font = label->font();
    font.setPointSize(30);
    font.setBold(true);
    font.setFamily("Arial");

    label->setFont(font);
    label->setFont(font);
    label->setStyleSheet(QString::fromStdString("color: #" + color + ";"));
    label->setAlignment(Qt::AlignCenter);
}

void setupWindowTitle(
    std::string&& title, int width, int height, QMainWindow* window,
    std::string&& color = "FF00000"
) {
    window->setWindowTitle(QString::fromStdString(title));
    window->setFixedSize(height, width);
    window->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
}
