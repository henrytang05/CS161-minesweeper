#include "GameBoard.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
GameBoard::GameBoard(QWidget* parent, int level) : QWidget(parent) { setupGameBoard(); }
GameBoard::~GameBoard() {}
void GameBoard::setupGameBoard() {
    auto& board = Session::GetBoard();
    this->setFixedSize(
        Session::GetCellSize() * Session::GetColumn(),
        Session::GetCellSize() * Session::GetRow()
    );

    QGridLayout* mainGridLayout = new QGridLayout(this);

    for (auto& row : board) {
        for (auto& square : row) {
            styleSquare(square);
            QObject::connect(square, &Square::result, this, &GameBoard::result);
            mainGridLayout->addWidget(square, square->row, square->col);
            if (dynamic_cast<Mine_Square*>(square) != nullptr)
                updateSurroundingMineNumber(square);
        }
    }
    this->setLayout(mainGridLayout);
}

void GameBoard::updateSurroundingMineNumber(Square* square) {
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
        int newRow = square->row + move[0];
        int newCol = square->col + move[1];
        if (newRow < 0 || newRow >= Session::GetRow() || newCol < 0 ||
            newCol >= Session::GetColumn())
            continue;
        board[newRow][newCol]->surroundingMineCount++;
    }
}
