#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

#include "../Square/Square.h"
class GameBoard;

constexpr int CELL_SIZE = 50;
constexpr int BOARD_SIZE = 8;
constexpr int MINE_NUMBER = 1;
class GameBoard : public QMainWindow {
   public:
    GameBoard(QWidget* parent = nullptr, int level = 0) : QMainWindow(parent) {
        setupGameBoard(level);
        this->show();
    }
    ~GameBoard() {}
   public slots:
    void squareClicked(Square* square, int row, int col);
    void restartClicked(GameBoard*);

   private:
    void initializeGameBoard();
    void setupGameBoard(int);
    bool isValidBombPosition(int row, int col);
    void updateSurroundingCells(int row, int col);
    void render_square(Square* square, int row, int col);
    void breakSurroundingCells(int row, int col);
    void revealAllBombs();
    void announcement(std::string);
    QGridLayout* mainGridLayout;

   public:
    static int squareRevealed;

   private:
    std::vector<std::vector<Square*>> grid;
    std::vector<std::pair<int, int>> mines;
    QPushButton* replayButton;
};
#endif