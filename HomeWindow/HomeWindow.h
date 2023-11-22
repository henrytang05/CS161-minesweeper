#ifndef MENU_H
#define MENU_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <string>

#include "../Memory/Memory.h"
#include "../Pages/GameBoardPage/GameBoardPage/GameBoardPage.h"
#include "../Pages/HomePage/HomePage.h"
#include "../Pages/LevelSelectionPage/LevelSelectionPage.h"
#include "../Style/Style.h"

class HomeWindow : public QMainWindow {
   public:
    HomeWindow(QMainWindow* parent = nullptr) : QMainWindow(parent) {
        stackedWidget = new QStackedWidget(this);
        styleWindow("Main Window", 500, 500, this, "245344");
        // setupHomePage();
        setCentralWidget(stackedWidget);
        homePage = new ("HomePage") HomePage(this);
        levelSelectionPage = new ("Level Selection Page") LevelSelectionPage(this);
        gameBoard = new ("Game Board Page") GameBoardPage(this);
        // setupLevelSelectionPage();
        stackedWidget->addWidget(homePage);
        stackedWidget->addWidget(levelSelectionPage);
        stackedWidget->addWidget(gameBoard);
        stackedWidget->setCurrentWidget(levelSelectionPage);
    }
    ~HomeWindow() {
        delete homePage;
        delete levelSelectionPage;
        delete stackedWidget;
        delete gameBoard;
    }
    // void setLevel(int level);

   private slots:
    // void setupHomePage();
    void setupLevelSelectionPage();
    void setupGameBoardPage();
    void resumeGame();
    void startGame(int level);
    void restartGame(GameBoard* gameBoard);

   private:
    QStackedWidget* stackedWidget;
    HomePage* homePage;
    LevelSelectionPage* levelSelectionPage;
    GameBoardPage* gameBoard;
};

#endif