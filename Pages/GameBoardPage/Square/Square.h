#ifndef SQUARE_H
#define SQUARE_H
#pragma once
#include <QIcon>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "../../../Memory/Memory.h"
#include "../../../Style/Style.h"
// class GameBoard;
class Square : public QPushButton {
    friend class GameBoard;
    Q_OBJECT
   public:
    Square(QWidget* parent = nullptr) : QPushButton(parent) {
        isMine = false;
        isFlagged = false;
        isRevealed = false;
        surroundingMineCount = 0;
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
    void render_square(int, int);

   public:
    inline static constexpr int CELL_SIZE = 50;
    int surroundingMineCount = 0;
    inline static int squareRevealed = 0;

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;
};
#endif