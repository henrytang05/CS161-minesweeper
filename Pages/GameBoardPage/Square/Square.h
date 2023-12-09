#ifndef SQUARE_H
#define SQUARE_H
#include <QIcon>
#include <QMouseEvent>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QWidget>

class GameBoard;
enum class Square_Type : char { Mine, Blank };
class Square : public QPushButton {
   public:
    enum class STATE : char { Revealed, UnRevealed, Flagged };
    friend class GameBoard;
    Q_OBJECT
   public:
    Square(int row, int col);
    virtual ~Square();

    void breakSurroundingCells();
    virtual void changeState(STATE newState) = 0;
    enum { LOSE, WIN };

   protected:
    void setSquareIcon(const QIcon& icon);
    virtual void render_square() = 0;
    void updateSurroundingFlag(char mode);

   public:
    int row;
    int col;

   public:
    STATE state;
    Square_Type type;
    int surroundingMineCount = 0;
    int surroundingFlagCount = 0;

   signals:
    void result(bool);
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
class Mine_Square : public Square {
    Q_OBJECT
   public:
    Mine_Square(int row, int col);
    ~Mine_Square();
    virtual void squareDoubleClickedSlot() override;
    virtual void render_square() override;
    virtual void changeState(STATE state) override;
};
class Blank_Square : public Square {
    Q_OBJECT
   public:
    Blank_Square(int row, int col);
    ~Blank_Square();
    virtual void squareDoubleClickedSlot() override;
    virtual void render_square() override;
    virtual void changeState(STATE state) override;
};

#endif