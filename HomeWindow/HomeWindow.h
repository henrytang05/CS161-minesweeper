#ifndef MENU_H
#define MENU_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <string>

#include "../GameBoard/GameBoard.h"

class HomeWindow : public QMainWindow {
   public:
    HomeWindow(QMainWindow* parent = nullptr) : QMainWindow(parent) { setupHomeWindow(); }
    ~HomeWindow() {}
    void setupHomeWindow();
    void setLevel(int level);

   private slots:
    void setupNewGame();
    void resumeGame();
};

#endif