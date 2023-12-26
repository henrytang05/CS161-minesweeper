#ifndef GAMEBOARD_PAGE_H
#define GAMEBOARD_PAGE_H

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <memory>
#include <string>

#include "Session/Result.h"
class Square;
class Timer;
class Session;
class MainWindow;
class GameboardPage : public QWidget {
    Q_OBJECT
    friend class MainWindow;

   public:
    GameboardPage(QWidget* parent = nullptr);
    ~GameboardPage();
    void cleanBoard();

   private:
    void setupGameboard();
    void reavealAllBombs();

   private:
    QWidget* gameboard;
    QLabel* announcementLabel;
    QLabel* timer;
    QPushButton* newGameButton;
    QPushButton* replayButton;
    QPushButton* exitButton;
    QLabel* level;
    QLabel* highScore;
    QGridLayout* mainGridLayout;

   signals:
    void newGameSignal();
    void replayClicked();
    void exitSignal();

   public slots:
    void resultAnnoucement(Result);
    void handleNewGameStart();
    void handleReplay();
};

#endif