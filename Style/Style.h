#pragma once
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <string>

void styleButton(QPushButton* b, std::string&& color = "FF00000", bool rounded = true);
void styleLabel(QLabel* label, std::string&& color = "FF00000");

void styleWindow(
    std::string&& title, int width, int height, QMainWindow* window,
    std::string&& color = "FF00000"
);
