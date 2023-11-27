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
    ~Square() {}
    void setAsRevealed();
    enum { LOSE, WIN };

   public:
    inline static constexpr int CELL_SIZE = 35;

   private:
    void setSquareIcon(
        const QIcon& icon, int width = Square::CELL_SIZE / 2,
        int length = Square::CELL_SIZE / 2
    );
    void render_square();
    void updateSurrounding(int row, int col, char mode);

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
    void squareLeftClickedSlot(int row, int col);
    void squareRightClickedSlot(int row, int col);
    void squareDoubleClickedSlot(int row, int col);
};
#endif