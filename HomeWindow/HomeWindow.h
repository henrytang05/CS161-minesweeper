#ifndef MENU_H
#define MENU_H

#include "../Pages/GameBoardPage/GameBoard/GameBoard.h"
#include "../Pages/GameBoardPage/GameBoardPage/GameBoardPage.h"
#include "../Pages/GameBoardPage/Square/Square.h"
#include "../Pages/HomePage/HomePage.h"
#include "../Pages/LevelSelectionPage/LevelSelectionPage.h"
#include "../Style/Style.h"

class HomeWindow;
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

class HomeWindow : public QMainWindow {
    Q_OBJECT
   public:
    HomeWindow(QMainWindow* parent = nullptr);
    ~HomeWindow();
    void makeconnection();

   private:
    Pages* stackedPages;
    double windowWidth = 520;
    double windowHeight = 420;
};

#endif