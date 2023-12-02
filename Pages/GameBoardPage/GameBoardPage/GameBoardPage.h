#ifndef GAME_BOARD_PAGE_H
#define GAME_BOARD_PAGE_H

#include <QBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <string>

#include "GameBoard/GameBoard.h"
#include "Square/Square.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
class GameBoard;
class Square;

class GameBoardPage : public QWidget {
    Q_OBJECT
   public:
    GameBoardPage(QStackedWidget* parent = nullptr, int level = 0);
    ~GameBoardPage();
    void setupGameBoardPage(int);

   private:
    GameBoard* Board;
    QPushButton* replayButton;
    QLabel* announcementLabel;
    Timer* timer;

   signals:
    void replayClicked();

   public slots:
    void victoryAnnoucement(bool);
};

#endif