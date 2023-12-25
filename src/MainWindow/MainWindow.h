#ifndef MENU_H
#define MENU_H
#include <QGraphicsEffect>
#include <QLinearGradient>
#include <QMainWindow>
#include <QPalette>
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

   private:
    void makeConnection();

   private:
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