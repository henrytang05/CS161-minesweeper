#include "Square.h"

#include "GameBoard/GameBoard.h"
#include "Style/Style.h"

Square::Square(int row, int col, QWidget* parent) : QPushButton(parent) {
    isMine = false;
    isFlagged = false;
    isRevealed = false;
    this->row = row;
    this->col = col;
    surroundingMineCount = 0;
    styleButton(this, "#EEA6B9", false, CELL_SIZE, CELL_SIZE);
}
Square::~Square() {}
void Square::setAsRevealed() {
    SQUARE_REVEALED++;
    this->isRevealed = true;
    this->render_square();
}
void Square::updateSurrounding(char mode) {
    int direction[8][2] = {
        {-1, -1},  // Up-Left
        {-1, 0},   // Up
        {-1, 1},   // Up-Right
        {0, -1},   // Left
        {0, 1},    // Right
        {1, -1},   // Down-Left
        {1, 0},    // Down
        {1, 1}     // Down-Right
    };
    for (auto& move : direction) {
        int newRow = this->row + move[0];
        int newCol = this->col + move[1];
        if (newRow < 0 || newRow >= GameBoard::BOARD_SIZE || newCol < 0 ||
            newCol >= GameBoard::BOARD_SIZE)
            continue;
        Square* square = GameBoard::grid[newRow][newCol];
        if (mode == 'm')
            square->surroundingMineCount++;
        else if (mode == 'f')
            square->surroundingFlagCount++;
        else if (mode == 'u')
            square->surroundingFlagCount--;
        else if (mode == 'd') {
            if (square->isFlagged && square->isMine) continue;
            if (square->isFlagged) {
                square->isFlagged = false;
                square->setIcon(QIcon());
                FLAG_SET--;
            }
            square->squareLeftClickedSlot();
        }
    }
}

void Square::setSquareIcon(const QIcon& icon, int width, int length) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (this) {
        this->setIcon(QIcon(pixmap));
        this->setIconSize(iconSize);
    }
}
void Square::render_square() {
    QString iconPath;
    if (this->isFlagged) {
        iconPath = QString(":/Images/flag.png");
        styleSquare(this, "yellow");
    } else if (this->isMine) {
        iconPath = QString(":/Images/bomb.png");
        styleSquare(this, "red");
    } else {
        iconPath = QString(":/Images/%1.png").arg(Square::surroundingMineCount);
        styleSquare(this, "green");
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
}
void Square::squareLeftClickedSlot() {
    if (this->isFlagged) return;
    if (this->isMine) {
        GameBoard::revealAllBombs();
        emit result(LOSE);
        return;
    }
    this->breakSurroundingCells();
    if (Square::SQUARE_REVEALED ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - GameBoard::MINE_NUMBER) {
        emit result(WIN);
    }
}
void Square::breakSurroundingCells() {
    this->setAsRevealed();
    if (this->surroundingMineCount != 0) {
        return;
    }
    int direction[8][2] = {
        {-1, -1},  // Up-Left
        {-1, 0},   // Up
        {-1, 1},   // Up-Right
        {0, -1},   // Left
        {0, 1},    // Right
        {1, -1},   // Down-Left
        {1, 0},    // Down
        {1, 1}     // Down-Right
    };
    for (auto& move : direction) {
        int newRow = this->row + move[0];
        int newCol = this->col + move[1];
        if (newRow < 0 || newRow >= GameBoard::BOARD_SIZE || newCol < 0 ||
            newCol >= GameBoard::BOARD_SIZE ||
            GameBoard::grid[newRow][newCol]->isRevealed) {
            continue;
        }
        GameBoard::grid[newRow][newCol]->breakSurroundingCells();
    }
}
void Square::squareRightClickedSlot() {
    char mode;
    if (!this->isRevealed) {
        if (FLAG_SET == GameBoard::FLAG_NUMBER && !this->isFlagged) return;
        if (!this->isFlagged) {
            this->isFlagged = true;
            this->render_square();
            mode = 'f';
            FLAG_SET++;
        } else {
            this->isFlagged = false;
            styleSquare(this);
            this->setIcon(QIcon());
            mode = 'u';
            FLAG_SET--;
        }
        this->updateSurrounding(mode);
    }
}
void Square::squareDoubleClickedSlot() {
    if (this->isRevealed && this->surroundingMineCount == this->surroundingFlagCount) {
        this->updateSurrounding('d');
    }
}