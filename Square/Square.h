#ifndef SQUARE_H
#define SQUARE_H
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class Square : public QPushButton {
   public:
    Square(QWidget* parent = nullptr) : QPushButton(parent) {
        isMine = false;
        isFlagged = false;
        isRevealed = false;
        bombCount = 0;
    }
    ~Square() {}
    void setMine();
    bool getIsMine();
    bool getIsRevealed();
    void setAsRevealed();
    void setAsNotRevealed();

   private:
    bool isMine;
    bool isFlagged;
    bool isRevealed;

   public:
    int bombCount;
    static int squareRevealed;
};
#endif