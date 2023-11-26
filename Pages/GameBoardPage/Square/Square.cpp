#include "Square.h"

#include "../GameBoard/GameBoard.h"

void Square::setMine() { this->isMine = true; }
bool Square::getIsMine() { return this->isMine; }
bool Square::getIsRevealed() { return this->isRevealed; }
void Square::setAsRevealed() {
    squareRevealed++;
    this->isRevealed = true;
    this->render_square();
}
void Square::setAsNotRevealed() {
    squareRevealed--;
    this->isRevealed = false;
}
void Square::setSquareIcon(const QIcon& icon, int width, int length) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (this) {
        this->setIcon(QIcon(pixmap));
        this->setIconSize(iconSize);
    }
}
void Square::squareClicked(int row, int col) {
    if (this->isMine) {
        GameBoard::revealAllBombs();
        emit result(false);
        return;
    }
    this->render_square();
    GameBoard::breakSurroundingCells(row, col);
    this->setAsRevealed();
    if (Square::squareRevealed ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - GameBoard::MINE_NUMBER) {
        emit result(true);
    }
}
void Square::render_square() {
    QString iconPath;
    if (this->isMine) {
        iconPath = QString("Pages/GameBoardPage/Square/Pictures/bomb.png");
        QIcon icon(iconPath);
        this->setStyleSheet("background-color: red");
    } else {
        iconPath = QString(":/Pages/GameBoardPage/Square/Pictures/number-%1.png")
                       .arg(Square::surroundingMineCount);
        this->setStyleSheet("background-color: green");
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
}