#ifndef GAME_BOARD_PAGE_H
#define GAME_BOARD_PAGE_H

#include <QBoxLayout>
#include <QStackedWidget>
#include <string>

#include "../../../Style/Style.h"
#include "../GameBoard/GameBoard.h"

class GameBoardPage : public QWidget {
    Q_OBJECT
   public:
    GameBoardPage(QStackedWidget* parent = nullptr, int level = 0) : QWidget(parent) {
        setupGameBoardPage(level);
    }
    ~GameBoardPage() {}
    void setupGameBoardPage(int);

   private:
    GameBoard* Board;
    QPushButton* replayButton;
    QLabel* announcementLabel;

   signals:
    void replayClicked();

   public slots:
    void victoryAnnoucement(bool);
};

#endif