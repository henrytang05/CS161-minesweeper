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
void styleButton(QPushButton* b, QString background_color, QString text_color);
void styleLabel(QLabel* label, QString color, double size = 40);

void styleWindow(QString title, QMainWindow* window);
void styleSquare(Square* square, QString color);
void styleTimer(QLabel* timer, QString color, double size = 40);
#endif