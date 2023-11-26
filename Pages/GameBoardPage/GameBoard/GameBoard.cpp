#include "GameBoard.h"
void GameBoard::setupGameBoard() {
    this->setFixedSize(
        Square::CELL_SIZE * GameBoard::BOARD_SIZE,
        Square::CELL_SIZE * GameBoard::BOARD_SIZE
    );
    grid.resize(
        GameBoard::BOARD_SIZE, std::vector<Square*>(GameBoard::BOARD_SIZE, nullptr)
    );
    QGridLayout* mainGridLayout = new ("mainGridLayout") QGridLayout(this);

    for (int row = 0; row < GameBoard::BOARD_SIZE; row++) {
        for (int col = 0; col < GameBoard::BOARD_SIZE; col++) {
            Square* square = new ("Square in grid") Square(this);
            QObject::connect(square, &QPushButton::clicked, square, [square, row, col]() {
                square->squareClicked(row, col);
            });
            QObject::connect(square, &Square::result, this, &GameBoard::result);
            grid[row][col] = square;
            mainGridLayout->addWidget(square, row, col);
        }
    }
    this->setLayout(mainGridLayout);
    initializeGameBoard();
}
void GameBoard::initializeGameBoard() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, GameBoard::BOARD_SIZE - 1);

    for (int i = 0; i < GameBoard::MINE_NUMBER; i++) {
        int rowRandomNumber = distribution(generator);
        int colRandomNumber = distribution(generator);
        if (isValidBombPosition(rowRandomNumber, colRandomNumber)) {
            grid[rowRandomNumber][colRandomNumber]->setMine();
            countMinesAround(rowRandomNumber, colRandomNumber);
        } else
            --i;
    }
}
bool GameBoard::isValidBombPosition(int row, int col) {
    if (!grid[row][col]->getIsMine()) {
        return true;
    } else {
        return false;
    }
}
void GameBoard::countMinesAround(int row, int col) {
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
        int newRow = row + move[0];
        int newCol = col + move[1];
        if (newRow < 0 || newRow >= GameBoard::BOARD_SIZE || newCol < 0 ||
            newCol >= GameBoard::BOARD_SIZE || grid[newRow][newCol]->getIsMine())
            continue;
        grid[newRow][newCol]->surroundingMineCount++;
    }
}

void GameBoard::breakSurroundingCells(int row, int col) {
    if (row < 0 || row >= GameBoard::BOARD_SIZE || col < 0 ||
        col >= GameBoard::BOARD_SIZE || GameBoard::grid[row][col]->getIsRevealed()) {
        return;
    }
    Square* square = GameBoard::grid[row][col];
    square->setAsRevealed();
    if (square->surroundingMineCount != 0) {
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
        int newRow = row + move[0];
        int newCol = col + move[1];
        breakSurroundingCells(newRow, newCol);
    }
}
void GameBoard::revealAllBombs() {
    for (auto row : grid) {
        for (auto square : row) {
            if (square->getIsMine() && !square->getIsRevealed()) {
                square->setAsRevealed();
            }
        }
    }
}
