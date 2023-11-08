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
        setStyleSheet("background-color: #c0c0c0");
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
    inline static int squareRevealed = 0;
};
#endif