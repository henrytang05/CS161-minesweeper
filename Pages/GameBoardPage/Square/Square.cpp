#include "Square.h"

#include "GameBoard/GameBoard.h"
#include "Session/Session.h"
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
    this->changeState(STATE::Revealed);
}
Mine_Square::Mine_Square(int row, int col, QWidget* parent) : Square(row, col, parent) {}
Mine_Square::~Mine_Square() {}
Blank_Square::Blank_Square(int row, int col, QWidget* parent)
    : Square(row, col, parent) {}
Blank_Square::~Blank_Square() {}

void Square::updateSurroundingFlag(char mode) {
    auto& grid = Session::GetInstance().board;
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
        Square* square = grid[newRow][newCol];
        if (mode == 'f')
            square->surroundingFlagCount++;
        else if (mode == 'u')
            square->surroundingFlagCount--;
        else if (mode == 'd') {
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
    switch (state) {
        case STATE::Revealed:
            iconPath = QString(":/Images/bomb.png");
            styleSquare(this, "red");
            break;
        case STATE::Flagged:
            iconPath = QString(":/Images/flag.png");
            styleSquare(this, "yellow");
            break;
        case STATE::UnRevealed:
            this->setIcon(QIcon());
            styleSquare(this);
            return;
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
}
void Blank_Square::render_square() {
    QString iconPath;
    switch (state) {
        case STATE::Revealed:
            iconPath = QString(":/Images/%1.png").arg(Square::surroundingMineCount);
            styleSquare(this, "green");
            break;
        case STATE::Flagged:
            iconPath = QString(":/Images/flag.png");
            styleSquare(this, "yellow");
            break;
        case STATE::UnRevealed:
            this->setIcon(QIcon());
            styleSquare(this);
            return;
    }
    QIcon icon(iconPath);
    this->setSquareIcon(icon);
}
void Square::breakSurroundingCells() {
    auto& grid = Session::GetInstance().board;

    this->changeState(STATE::Revealed);
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
            grid[newRow][newCol]->state == STATE::Revealed) {
            continue;
        }
        grid[newRow][newCol]->breakSurroundingCells();
    }
}
void Square::squareLeftClickedSlot() {
    if (state == STATE::Flagged) return;
    this->changeState(STATE::Revealed);
}

void Square::squareRightClickedSlot() {
    switch (state) {
        case STATE::UnRevealed:
            this->changeState(STATE::Flagged);
            // TODO: update surrounding cells
            break;
        case STATE::Flagged:
            this->changeState(STATE::UnRevealed);

            // TODO: update surrounding cells
            break;
        case STATE::Revealed:
            return;
    }
}

void Mine_Square::squareDoubleClickedSlot() {
    if (state == STATE::Flagged) return;
    this->changeState(STATE::Revealed);
}

void Blank_Square::squareDoubleClickedSlot() {
    if (state == STATE::Flagged) return;
    if (this->surroundingMineCount == this->surroundingFlagCount) {
        this->updateSurroundingFlag('d');
    }
}

void Mine_Square::changeState(STATE newState) {
    if (this->state == newState) return;
    this->state = newState;
    this->render_square();
    switch (newState) {
        case STATE::UnRevealed:
            updateSurroundingFlag('u');
            break;
        case STATE::Revealed:
            emit result(LOSE);
            return;
        case STATE::Flagged:
            updateSurroundingFlag('f');

            break;
    }
}
void Blank_Square::changeState(STATE newState) {
    if (this->state == newState) return;
    this->state = newState;
    render_square();

    switch (newState) {
        case STATE::UnRevealed:
            updateSurroundingFlag('u');
            break;
        case STATE::Revealed:
            this->breakSurroundingCells();

            break;
        case STATE::Flagged:
            updateSurroundingFlag('f');
            return;
    }
    if (Square::SQUARE_REVEALED ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - GameBoard::MINE_NUMBER) {
        emit result(WIN);
    }
}