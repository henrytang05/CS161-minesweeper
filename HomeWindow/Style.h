#pragma once
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <string>

void setupButton(QPushButton* b, std::string&& color = "FF00000", bool rounded = true);
void setupLabel(QLabel* label, std::string&& color = "FF00000");

void setupWindowTitle(
    std::string&& title, int width, int height, QMainWindow* window,
    std::string&& color = "FF00000"
);
