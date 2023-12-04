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

   public:
    inline static int BOARD_SIZE = 8;
    inline static int MINE_NUMBER = 0;
    inline static int FLAG_NUMBER = 0;

   private:
    void initializeGameBoard(QGridLayout*);
    void updateSurroundingMineNumber(Square*);

   signals:
    void result(bool);
};
#endif