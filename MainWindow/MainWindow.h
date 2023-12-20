#ifndef MENU_H
#define MENU_H
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
class MainWindow;
class LevelSelectionPage;
class HomePage;
class GameboardPage;
class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();
    void makeConnection();

   public:
    QStackedWidget* Pages;
    HomePage* homePage;
    LevelSelectionPage* levelSelectionPage;
    GameboardPage* gameboardPage;

   signals:
    void newGameSignal();
    void replaySignal();

   public slots:
    void startNewGameSlot();
    void resumeGameSlot();
    void endGameSlot();
};

#endif