#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QApplication>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class Square : public QPushButton {
   public:
    Square(QWidget* parent = nullptr) : QPushButton(parent) {
        isMine = false;
        isFlagged = false;
        isRevealed = false;
    }
    ~Square() {}

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;
};

class GameBoard : public QMainWindow {
   public:
    GameBoard(QWidget* parent = nullptr) : QMainWindow(parent) { setupGameBoard(); }
    ~GameBoard() {}

   public slots:
    void squareClicked(QPushButton* square, int row, int col);

   private:
    QGridLayout* mainGridLayout;
    void initializeGameBoard();
    void setupGameBoard();
    std::vector<std::vector<QPushButton*>> grid;
    std::vector<std::pair<int, int>> mines;
};

#endif