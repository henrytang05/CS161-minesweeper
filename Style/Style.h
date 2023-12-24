#ifndef STYLE_H
#define STYLE_H

#include <QLabel>
#include <QLinearGradient>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QString>
#include <cctype>
#include <string>

class Square;
void styleButton(
    QPushButton* b, std::string&& background_color, std::string&& text_color
);
void styleLabel(QLabel* label, std::string&& color, double size = 40);

void styleWindow(QMainWindow* window);
void styleSquare(Square* square, std::string&& color = "");
void styleTimer(QLabel* timer, std::string&& color, double size = 40);
#endif