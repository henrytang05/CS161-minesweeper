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
    GameboardPage(QStackedWidget* parent = nullptr);
    ~GameboardPage();
    void setupGameboard();
    void reavealAllBombs();
    void cleanBoard();

   private:
    QWidget* gameboard;
    QLabel* timer;
    QLabel* announcementLabel;
    QPushButton* replayButton;
    QLabel* level;
    QLabel* highScore;

    QGridLayout* mainGridLayout;

    std::vector<QLayout*> layoutCollection;

   signals:
    void replayClicked();

   public slots:
    void victoryAnnoucement(Result);
    void handleNewGameStart();
};

#endif