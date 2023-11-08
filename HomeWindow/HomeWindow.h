#ifndef MENU_H
#define MENU_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <string>

#include "../GameBoard/GameBoard.h"

class HomeWindow : public QMainWindow {
   public:
    HomeWindow(QMainWindow* parent = nullptr) : QMainWindow(parent) {
        stackedWidget = new QStackedWidget(this);
        setupHomeWindow();
        setCentralWidget(stackedWidget);
        setupNewGame();
        stackedWidget->addWidget(homePage);
        stackedWidget->addWidget(levelSelectionPage);
        stackedWidget->setCurrentWidget(homePage);
    }
    ~HomeWindow() {
        delete homePage;
        delete levelSelectionPage;
        delete stackedWidget;
    }
    void setupHomeWindow();
    void setLevel(int level);

   private slots:
    void setupNewGame();
    void resumeGame();
    void startGame(int level);

   private:
    QStackedWidget* stackedWidget;
    QWidget* homePage;
    QWidget* levelSelectionPage;
    GameBoard* gameBoard;
}

#endif