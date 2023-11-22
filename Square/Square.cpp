#include "Square.h"
void Square::setMine() { this->isMine = true; }
bool Square::getIsMine() { return this->isMine; }
bool Square::getIsRevealed() { return this->isRevealed; }
void Square::setAsRevealed() {
    squareRevealed++;
    this->isRevealed = true;
}
void Square::setAsNotRevealed() {
    squareRevealed--;
    this->isRevealed = false;
}
void Square::setIcon(const QIcon& icon, int width, int length) {
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
        return;
    }
    this->setAsRevealed();
    this->render_square(row, col);
    if (Square::squareRevealed ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - Square::MINE_NUMBER) {
        GameBoard::announcement("You Win!");
    }
}
void Square::render_square(int row, int col) {
    switch (Square::bombCount) {
        case 1:
            this->setIcon(QIcon("Pictures/number-1.png"));
            break;
        case 2:
            this->setIcon(QIcon("Pictures/number-2.png"));
            break;
        case 3:
            this->setIcon(QIcon("Pictures/number-3.png"));
            break;
        case 4:
            this->setIcon(QIcon("Pictures/number-4.png"));
            break;
        case 5:
            this->setIcon(QIcon("Pictures/number-5.png"));
            break;
        case 6:
            this->setIcon(QIcon("Pictures/number-6.png"));
            break;
        case 7:
            this->setIcon(QIcon("Pictures/number-7.png"));
            break;
        case 8:
            this->setIcon(QIcon("Pictures/number-8.png"));
            break;
        default:
            this->setAsNotRevealed();
            GameBoard::breakSurroundingCells(row, col);
    }
}