#ifndef SQUARE_H
#define SQUARE_H
#pragma once
#include <QIcon>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QWidget>

#include "../../../Memory/Memory.h"
#include "../../../Style/Style.h"
class GameBoard;
class GameBoardPage;
class Square : public QPushButton {
    friend class GameBoard;
    Q_OBJECT
   public:
    Square(QWidget* parent = nullptr) : QPushButton(parent) {
        isMine = false;
        isFlagged = false;
        isRevealed = false;
        surroundingMineCount = 0;
        styleButton(this, "#EEA6B9", false, CELL_SIZE, CELL_SIZE);
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

   public:
    void setSquareIcon(
        const QIcon& icon, int width = Square::CELL_SIZE / 2,
        int length = Square::CELL_SIZE / 2
    );
    void render_square();

   public:
    inline static constexpr int CELL_SIZE = 50;
    int surroundingMineCount = 0;
    inline static int squareRevealed = 0;

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;
   signals:
    void result(bool);
   public slots:
    void squareClicked(int row, int col);
};
#endif