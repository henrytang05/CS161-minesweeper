#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QGridLayout>
#include <QWidget>
#include <random>
#include <vector>

class Square;
class GameBoard : public QWidget {
    Q_OBJECT
   public:
    GameBoard(QWidget* parent = nullptr, int level = 0);
    ~GameBoard();

    void setupGameBoard();

   private:
    void updateSurroundingMineNumber(Square*);

   signals:
    void result(bool);
};
#endif