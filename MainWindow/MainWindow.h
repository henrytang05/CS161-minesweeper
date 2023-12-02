#ifndef MENU_H
#define MENU_H

#include "GameBoard/GameBoard.h"
#include "GameBoardPage/GameBoardPage.h"
#include "HomePage/HomePage.h"
#include "LevelSelectionPage/LevelSelectionPage.h"
#include "Square/Square.h"
#include "Style/Style.h"

class MainWindow;
class Pages : public QStackedWidget {
    Q_OBJECT
   public:
    Pages(QWidget* parent = nullptr);
    ~Pages();
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

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();
    void makeconnection();

   private:
    Pages* stackedPages;
    double windowWidth = 520;
    double windowHeight = 420;
};

#endif