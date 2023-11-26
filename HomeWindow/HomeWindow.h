#ifndef MENU_H
#define MENU_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <string>

#include "../Memory/Memory.h"
#include "../Pages/GameBoardPage/GameBoardPage/GameBoardPage.h"
#include "../Pages/HomePage/HomePage.h"
#include "../Pages/LevelSelectionPage/LevelSelectionPage.h"
#include "../Style/Style.h"
class HomeWindow;
class Pages : public QStackedWidget {
    Q_OBJECT
   public:
    Pages(QWidget* parent = nullptr) : QStackedWidget(parent) { setupPages(); }
    void setupPages();
    void createGameBoardPage(int difficulty);
    void makeconnection();

   private:
    HomePage* homePage;
    LevelSelectionPage* levelSelectionPage;
    GameBoardPage* gameBoardPage;

   signals:
    void newGameSignal();
    void replaySignal();

   public slots:
    void replayGameSlot();
    void startNewGameSlot(int difficulty);
};

class HomeWindow : public QMainWindow {
    Q_OBJECT
   public:
    HomeWindow(QMainWindow* parent = nullptr) : QMainWindow(parent) {
        stackedPages = new Pages(this);
        styleWindow("Main Window", windowWidth, windowHeight, this, "E36387");
        setCentralWidget(stackedPages);
        makeconnection();
    }
    ~HomeWindow() {}
    void makeconnection();

   private:
    Pages* stackedPages;
    double windowWidth = Square::CELL_SIZE * GameBoard::BOARD_SIZE + 200;
    double windowHeight = Square::CELL_SIZE * GameBoard::BOARD_SIZE + 100;
};

#endif