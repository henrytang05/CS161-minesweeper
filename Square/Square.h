#ifndef SQUARE_H
#define SQUARE_H
#include <QIcon>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "../Memory/Memory.h"
#include "..Pages/GameBoardPage/GameBoardPage.h"

class Square : public QPushButton {
   public:
    friend class GameBoard;
    Square(QWidget* parent = nullptr) : QPushButton(parent) {
        isMine = false;
        isFlagged = false;
        isRevealed = false;
        bombCount = 0;
        setStyleSheet("background-color: #c0c0c0");
    }
    ~Square() {
        qInstallMessageHandler(customMessageHandler);
        qInfo() << "--------Square deleted\n";
    }
    void setMine();
    bool getIsMine();
    bool getIsRevealed();
    void setAsRevealed();
    void setAsNotRevealed();
   public slots:
    void squareClicked(int row, int col);

   public:
    void setIcon(
        const QIcon& icon, int width = Square::CELL_SIZE / 2,
        int length = Square::CELL_SIZE / 2
    );

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;

   public:
    inline static int MINE_NUMBER = 0;
    inline static constexpr int CELL_SIZE = 50;
    inline static int bombCount = 0;
    inline static int squareRevealed = 0;
    void render_square(int row, int col);
};
#endif