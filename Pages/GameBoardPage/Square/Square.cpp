#include "Square.h"

#include "../GameBoard/GameBoard.h"

void Square::setAsRevealed() {
    squareRevealed++;
    this->isRevealed = true;
    this->render_square();
}
void Square::setSquareIcon(const QIcon& icon, int width, int length) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (this) {
        this->setIcon(QIcon(pixmap));
        this->setIconSize(iconSize);
    }
}
void Square::squareLeftClicked(int row, int col) {
    if (this->isFlagged) return;
    if (this->isMine) {
        GameBoard::revealAllBombs();
        emit result(false);
        return;
    }
    GameBoard::breakSurroundingCells(row, col);
    if (Square::squareRevealed ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - GameBoard::MINE_NUMBER) {
        emit result(true);
    }
}
void Square::squareRightClicked(int row, int col) {
    if (!this->isRevealed) {
        if (!this->isFlagged) {
            this->isFlagged = true;
            this->render_square();
        } else {
            this->isFlagged = false;
            styleSquare(this, row, col);
            this->setIcon(QIcon());
        }
    }
}
void Square::render_square() {
    QString iconPath;
    if (this->isFlagged) {
        iconPath = QString("Pictures/flag.png");
        QIcon icon(iconPath);
        this->setStyleSheet("background-color: yellow");
    } else if (this->isMine) {
        iconPath = QString("Pictures/bomb.png");
        QIcon icon(iconPath);
        this->setStyleSheet("background-color: red");
    } else {
        iconPath = QString("Pictures/number-%1.png").arg(Square::surroundingMineCount);
        this->setStyleSheet("background-color: green");
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
}