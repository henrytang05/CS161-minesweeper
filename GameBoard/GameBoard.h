#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
class GameBoard;
class Square;
constexpr int CELL_SIZE = 50;
constexpr int BOARD_SIZE = 8;
constexpr int MINE_NUMBER = BOARD_SIZE * BOARD_SIZE / 8;
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

   public:
    static int squareRevealed;

   private:
    std::vector<std::vector<Square*>> grid;
    std::vector<std::pair<int, int>> mines;
    QPushButton* replayButton;
    void initializeGameBoard();
    void setupGameBoard(int);
    bool isValidBombPosition(int row, int col);
    void updateSurroundingCells(int row, int col);
    void render_square(Square* square, int row, int col);
    void breakSurroundingCells(int row, int col);
    void revealAllBombs();
    void announcement(std::string);
    QGridLayout* mainGridLayout;
};
class Square : public QPushButton {
   public:
    Square(QWidget* parent = nullptr) : QPushButton(parent) {
        isMine = false;
        isFlagged = false;
        isRevealed = false;
        bombCount = 0;
    }
    ~Square() {}

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;

   public:
    int bombCount;

    void setMine() { this->isMine = true; }
    bool getIsMine() { return this->isMine; }
    bool getIsRevealed() { return this->isRevealed; }

    void setAsRevealed() {
        GameBoard::squareRevealed++;
        this->isRevealed = true;
    }
    void setAsNotRevealed() {
        GameBoard::squareRevealed--;
        this->isRevealed = false;
    }
};

#endif