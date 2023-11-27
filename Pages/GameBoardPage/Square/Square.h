#ifndef SQUARE_H
#define SQUARE_H
#include <QIcon>
#include <QMouseEvent>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QWidget>
// #include "../../../Memory/Memory.h"
#include "../../../Style/Style.h"
#include "../GameBoard/GameBoard.h"

class Square : public QPushButton {
    friend class GameBoard;
    Q_OBJECT
   public:
    Square(int row, int col, QWidget* parent = nullptr);
    ~Square();
    void setAsRevealed();
    void breakSurroundingCells();
    enum { LOSE, WIN };

   public:
    inline static constexpr int CELL_SIZE = 35;

   private:
    void setSquareIcon(
        const QIcon& icon, int width = Square::CELL_SIZE / 2,
        int length = Square::CELL_SIZE / 2
    );
    void render_square();
    void updateSurrounding(char mode);

   public:
    int row;
    int col;

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;
    int surroundingMineCount = 0;
    int surroundingFlagCount = 0;
    inline static int FLAG_SET = 0;
    inline static int SQUARE_REVEALED = 0;
   signals:
    void result(bool);
    void rightClicked();
    void doubleClicked();

   protected:
    void mouseReleaseEvent(QMouseEvent* e) {
        if (e->button() == Qt::RightButton)
            emit rightClicked();
        else if (e->button() == Qt::LeftButton)
            emit clicked();
    }
    void mouseDoubleClickEvent(QMouseEvent* e) override {
        if (e->button() == Qt::LeftButton) emit doubleClicked();
    }

   public slots:
    void squareLeftClickedSlot();
    void squareRightClickedSlot();
    void squareDoubleClickedSlot();
};
#endif