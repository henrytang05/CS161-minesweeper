#include "Square.h"

#include "GameBoard/GameBoard.h"
#include "Style/Style.h"

Square::Square(int row, int col, QWidget* parent) : QPushButton(parent) {
    isMine = false;
    isFlagged = false;
    isRevealed = false;
    state = STATE::UnRevealed;
    surroundingMineCount = 0;
    surroundingFlagCount = 0;
    this->row = row;
    this->col = col;

    styleButton(this, "#EEA6B9", false, CELL_SIZE, CELL_SIZE);
    QObject::connect(this, &QPushButton::clicked, this, &Square::squareLeftClickedSlot);
    QObject::connect(this, &Square::rightClicked, this, &Square::squareRightClickedSlot);
    QObject::connect(
        this, &Square::doubleClicked, this, &Square::squareDoubleClickedSlot
    );
}
Square::~Square() {}
void Square::setAsRevealed() {
    SQUARE_REVEALED++;
    this->isRevealed = true;
    this->changeState(STATE::Revealed);
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
void Mine_Square::render_square() {
    QString iconPath;
    if (this->isRevealed) {
        iconPath = QString(":/Images/bomb.png");
        styleSquare(this, "red");
    } else if (state == STATE::Flagged) {
        iconPath = QString(":/Images/flag.png");
        styleSquare(this, "yellow");
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
}
void Blank_Square::render_square() {
    QString iconPath;
    if (this->isFlagged) {
        iconPath = QString(":/Images/flag.png");
        styleSquare(this, "yellow");
    } else {
        iconPath = QString(":/Images/%1.png").arg(Square::surroundingMineCount);
        styleSquare(this, "green");
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
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
            GameBoard::grid[newRow][newCol]->state == STATE::Revealed) {
            continue;
        }
        GameBoard::grid[newRow][newCol]->breakSurroundingCells();
    }
}

void Square::squareRightClickedSlot() {
    char mode;
    if (state == STATE::Revealed) {
        if (!this->isFlagged) {
            this->isFlagged = true;
            this->render_square();
            mode = 'f';

        } else {
            this->isFlagged = false;
            styleSquare(this);
            this->setIcon(QIcon());
            mode = 'u';
        }
        this->updateSurrounding(mode);
    }
}

Mine_Square::Mine_Square(int row, int col, QWidget* parent) : Square(row, col, parent) {}
Mine_Square::~Mine_Square() {}
void Mine_Square::squareLeftClickedSlot() {
    this->setStyleSheet("background-color: red;");
    GameBoard::revealAllBombs();
    emit result(LOSE);
}
void Mine_Square::squareDoubleClickedSlot() {
    if (this->isFlagged)
        return;
    else
        emit result(WIN);
}
Blank_Square::Blank_Square(int row, int col, QWidget* parent)
    : Square(row, col, parent) {}
Blank_Square::~Blank_Square() {}
void Blank_Square::squareLeftClickedSlot() {
    if (this->isFlagged) return;
    this->breakSurroundingCells();
    if (Square::SQUARE_REVEALED ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - GameBoard::MINE_NUMBER) {
        emit result(WIN);
    }
}
void Blank_Square::squareDoubleClickedSlot() {
    if (state == STATE::Flagged &&
        this->surroundingMineCount == this->surroundingFlagCount) {
        this->updateSurrounding('d');
    }
}
void Mine_Square::changeState(STATE newState) {
    this->state = newState;
    switch (newState) {
        case STATE::UnRevealed:
            return;
        case STATE::Revealed:
            this->render_square();
            emit result(LOSE);
            break;
        case STATE::Flagged:
            this->render_square();
            break;
    }
}
void Blank_Square::changeState(STATE newState) {
    this->state = newState;
    render_square();
    switch (newState) {
        case STATE::UnRevealed:
        case STATE::Revealed:
        case STATE::Flagged:
            return;
    }
}