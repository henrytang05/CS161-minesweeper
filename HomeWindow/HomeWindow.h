#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

#include "../GameBoard/GameBoard.h"
class HomeWindow : public QWidget {
   public:
    HomeWindow(QWidget* parent = nullptr) : QWidget(parent) { setupHomeWindow(); }
    ~HomeWindow() {}
    void setupHomeWindow();
    void setLevel(int level);
};

#endif