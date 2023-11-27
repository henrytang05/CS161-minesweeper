#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <cctype>
#include <string>
void styleButton(
    QPushButton* b, std::string&& background_color = "FF00000", bool rounded = true,
    int width = 100, int height = 50, std::string&& text_color = "0"
);
void styleLabel(QLabel* label, std::string&& color = "FF00000", double size = 40);

void styleWindow(
    std::string&& title, int width, int height, QMainWindow* window,
    std::string&& color = "FF00000"
);
void styleSquare(QPushButton* square, int row, int col, std::string&& color = "");
