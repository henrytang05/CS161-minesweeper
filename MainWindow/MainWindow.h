#ifndef MENU_H
#define MENU_H
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
class MainWindow;
class LevelSelectionPage;
class HomePage;
class GameBoardPage;
class Pages : public QStackedWidget {
    Q_OBJECT
   public:
    Pages(QWidget* parent = nullptr);
    ~Pages();
    void setupPages();

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
    void startNewGameSlot();
    void resumeGameSlot();
};

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(double width = 0, double height = 0, QMainWindow* parent = nullptr);
    ~MainWindow();
    void makeconnection();

   private:
    Pages* stackedPages;
    double windowWidth = 900;
    double windowHeight = 900;
};

#endif