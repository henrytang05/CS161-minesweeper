#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QGridLayout>
#include <QWidget>
#include <random>
#include <vector>

#include "Square/Square.h"
#include "Style/Style.h"
class Square;
class GameBoard : public QWidget {
    Q_OBJECT
   public:
    GameBoard(QWidget* parent = nullptr, int level = 0);
    ~GameBoard();

    static void revealAllBombs();
    void setupGameBoard();

   public:
    inline static int BOARD_SIZE = 8;
    inline static int MINE_NUMBER = 0;
    inline static int FLAG_NUMBER = 0;
    static std::vector<std::vector<Square*>> grid;

   private:
    void initializeGameBoard();

   signals:
    void result(bool);
};
#endif