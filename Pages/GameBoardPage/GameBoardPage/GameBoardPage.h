#ifndef GAMEBOARD_PAGE_H
#define GAMEBOARD_PAGE_H

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
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

   private:
    QWidget* gameboard;
    QLabel* timer;
    QPushButton* replayButton;
    QLabel* announcementLabel;
    QGridLayout* mainGridLayout;

    std::vector<QLayout*> layoutCollection;

   signals:
    void replayClicked();

   public slots:
    void handleNewGameStart();
    void victoryAnnoucement(Result);
};

#endif