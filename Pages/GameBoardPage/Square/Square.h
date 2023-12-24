#ifndef SQUARE_H
#define SQUARE_H
#include <QDataStream>
#include <QIcon>
#include <QMouseEvent>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QWidget>

#include "Session/Result.h"
class Gameboard;
class Session;
enum class Square_Type : int8_t { Mine = -2, Blank };
class Square : public QPushButton {
    friend class Gameboard;
    friend class Session;

   public:
    enum class State : int8_t { Revealed = -3, UnRevealed, Flagged };
    Q_OBJECT
   public:
    Square(int row, int col, Square_Type type);
    virtual ~Square();

    friend QDataStream& operator<<(QDataStream& out, const Square& square);
    friend QDataStream& operator>>(QDataStream& out, Square& square);

    enum { LOSE, WIN };
    virtual void changeState(State newState) = 0;
    virtual void render_square() = 0;

   protected:
    void breakSurroundingCells();
    void setSquareIcon(const QIcon& icon);
    void updateSurroundingFlag(char mode);

   public:
    int row;
    int col;
    State state;
    Square_Type type;

   protected:
    int surroundingMineCount = 0;
    int surroundingFlagCount = 0;

   signals:
    void leftClick();
    void rightClick();
    void doubleClick();

   protected:
    void mouseReleaseEvent(QMouseEvent* e) {
        if (e->button() == Qt::RightButton)
            emit rightClick();
        else if (e->button() == Qt::LeftButton)
            emit leftClick();
    }
    void mouseDoubleClickEvent(QMouseEvent* e) override {
        if (e->button() == Qt::LeftButton) emit doubleClick();
    }

   public slots:
    void squareLeftClickedSlot();
    void squareRightClickedSlot();
    virtual void squareDoubleClickedSlot() = 0;
};
QDataStream& operator<<(QDataStream& out, const Square& square);
QDataStream& operator>>(QDataStream& out, Square& square);
class Mine_Square : public Square {
    Q_OBJECT
   public:
    Mine_Square(int row, int col);
    ~Mine_Square();

   private:
    virtual void squareDoubleClickedSlot() override;
    virtual void render_square() override;
    virtual void changeState(State state) override;
};
class Blank_Square : public Square {
    Q_OBJECT
   public:
    Blank_Square(int row, int col);
    ~Blank_Square();

   private:
    virtual void squareDoubleClickedSlot() override;
    virtual void render_square() override;
    virtual void changeState(State state) override;
};

#endif