#ifndef SQUARE_H
#define SQUARE_H
#include <QIcon>
#include <QMouseEvent>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QWidget>

class GameBoard;
class Square : public QPushButton {
   public:
    enum class STATE : char { Reavealed, UnRevealed, Flagged };
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

   protected:
    void setSquareIcon(
        const QIcon& icon, int width = Square::CELL_SIZE / 2,
        int length = Square::CELL_SIZE / 2
    );
    virtual void render_square() = 0;
    void updateSurrounding(char mode);

   public:
    int row;
    int col;

   protected:
    bool isMine;
    bool isFlagged;
    bool isRevealed;
    int surroundingMineCount = 0;
    int surroundingFlagCount = 0;

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
    virtual void squareLeftClickedSlot() = 0;
    void squareRightClickedSlot();
    virtual void squareDoubleClickedSlot() = 0;
};
class Mine_Square : public Square {
    Q_OBJECT
   public:
    Mine_Square(int row, int col, QWidget* parent = nullptr);
    ~Mine_Square();
    virtual void squareLeftClickedSlot() override;
    virtual void squareDoubleClickedSlot() override;
    virtual void render_square() override;
};
class Blank_Square : public Square {
    Q_OBJECT
   public:
    Blank_Square(int row, int col, QWidget* parent = nullptr);
    ~Blank_Square();
    virtual void squareLeftClickedSlot() override;
    virtual void squareDoubleClickedSlot() override;
    virtual void render_square() override;
};

#endif