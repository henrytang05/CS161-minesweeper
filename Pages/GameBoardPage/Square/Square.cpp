#include "Square.h"

#include "GameBoard/GameBoard.h"
#include "Session/Session.h"
#include "Style/Style.h"
static auto& board = Session::GetBoard();

Square::Square(int row, int col, QWidget* parent) : QPushButton(parent) {
    state = STATE::UnRevealed;
    surroundingMineCount = 0;
    surroundingFlagCount = 0;
    this->row = row;
    this->col = col;

    styleButton(this, "#EEA6B9", false, Session::GetCellSize(), Session::GetCellSize());
    QObject::connect(this, &Square::leftClick, this, &Square::squareLeftClickedSlot);
    QObject::connect(this, &Square::rightClick, this, &Square::squareRightClickedSlot);
    QObject::connect(this, &Square::doubleClick, this, &Square::squareDoubleClickedSlot);
}
Square::~Square() {
    QObject::disconnect(this, &Square::leftClick, this, &Square::squareLeftClickedSlot);
    QObject::disconnect(this, &Square::rightClick, this, &Square::squareRightClickedSlot);
    QObject::disconnect(
        this, &Square::doubleClick, this, &Square::squareDoubleClickedSlot
    );
}

Mine_Square::Mine_Square(int row, int col, QWidget* parent) : Square(row, col, parent) {}
Mine_Square::~Mine_Square() {}
Blank_Square::Blank_Square(int row, int col, QWidget* parent)
    : Square(row, col, parent) {}
Blank_Square::~Blank_Square() {}

void Square::updateSurroundingFlag(char mode) {
    auto& board = Session::GetBoard();
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
        if (newRow < 0 || newRow >= Session::GetRow() || newCol < 0 ||
            newCol >= Session::GetColumn())
            continue;
        Square* square = board[newRow][newCol];
        if (mode == 'f')
            square->surroundingFlagCount++;
        else if (mode == 'u')
            square->surroundingFlagCount--;
        else if (mode == 'd') {
            square->squareLeftClickedSlot();
        }
    }
}

void Square::setSquareIcon(const QIcon& icon) {
    double width, length;
    width = length = Session::GetCellSize() / 2;
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
        if (newRow < 0 || newRow >= Session::GetRow() || newCol < 0 ||
            newCol >= Session::GetColumn() ||
            board[newRow][newCol]->state == STATE::Revealed) {
            continue;
        }
        board[newRow][newCol]->breakSurroundingCells();
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
    int& s_correctFlagged = Session::GetCorrectFlag();
    int& s_flagged = Session::GetFlag();
    switch (newState) {
        case STATE::Revealed:
            emit result(LOSE);
            break;

        // this mean you unflag it
        case STATE::UnRevealed:
            updateSurroundingFlag('u');
            s_flagged--;
            s_correctFlagged--;
            break;

        case STATE::Flagged:
            updateSurroundingFlag('f');
            s_flagged++;
            s_correctFlagged++;
            break;
    }
    if (Session::GetSquareRevealed() + s_correctFlagged ==
        Session::GetRow() * Session::GetColumn()) {
        emit result(WIN);
    }
}
void Blank_Square::changeState(STATE newState) {
    if (this->state == newState) return;
    this->state = newState;
    render_square();
    int& s_revealed = Session::GetSquareRevealed();
    int& s_correctFlagged = Session::GetCorrectFlag();
    int& s_flagged = Session::GetFlag();
    switch (newState) {
        case STATE::Revealed:
            s_revealed++;
            this->breakSurroundingCells();
            break;
        // this mean you unflag it
        case STATE::UnRevealed:
            updateSurroundingFlag('u');
            s_flagged--;
            break;
        case STATE::Flagged:
            updateSurroundingFlag('f');
            s_flagged++;
            break;
    }
    if (s_revealed + s_correctFlagged == Session::GetRow() * Session::GetColumn()) {
        emit result(WIN);
    }
}