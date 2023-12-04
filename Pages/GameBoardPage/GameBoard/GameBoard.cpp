#include "GameBoard.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
static auto& grid = Session::GetInstance().board;
GameBoard::GameBoard(QWidget* parent, int level) : QWidget(parent) {
    if (level == 1)
        BOARD_SIZE = 9;
    else if (level == 2)
        BOARD_SIZE = 16;
    else if (level == 3)
        BOARD_SIZE = 30;
    else
        BOARD_SIZE = 9;
    MINE_NUMBER = BOARD_SIZE * BOARD_SIZE / 8;
    FLAG_NUMBER = MINE_NUMBER;

    setupGameBoard();
}
GameBoard::~GameBoard() {}
void GameBoard::setupGameBoard() {
    this->setFixedSize(
        Square::CELL_SIZE * GameBoard::BOARD_SIZE,
        Square::CELL_SIZE * GameBoard::BOARD_SIZE
    );

    QGridLayout* mainGridLayout = new QGridLayout(this);

    for (int row = 0; row < GameBoard::BOARD_SIZE; row++) {
        for (int col = 0; col < GameBoard::BOARD_SIZE; col++) {
            Square* square = new Blank_Square(row, col, this);
            styleSquare(square);
            QObject::connect(square, &Square::result, this, &GameBoard::result);
            grid[row][col] = square;
            mainGridLayout->addWidget(square, row, col);
        }
    }
    this->setLayout(mainGridLayout);
    initializeGameBoard(mainGridLayout);
}
void GameBoard::initializeGameBoard(QGridLayout* mainGridLayout) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, GameBoard::BOARD_SIZE - 1);

    for (int i = 0; i < GameBoard::MINE_NUMBER; i++) {
        int rowRandomNumber, colRandomNumber;

        do {
            rowRandomNumber = distribution(generator);
            colRandomNumber = distribution(generator);

        } while (dynamic_cast<Mine_Square*>(grid[rowRandomNumber][colRandomNumber]) !=
                 nullptr);

        delete grid[rowRandomNumber][colRandomNumber];
        grid[rowRandomNumber][colRandomNumber] =
            new Mine_Square(rowRandomNumber, colRandomNumber, this);
        Square* square = grid[rowRandomNumber][colRandomNumber];
        QObject::connect(square, &Square::result, this, &GameBoard::result);
        styleSquare(square);
        mainGridLayout->addWidget(
            grid[rowRandomNumber][colRandomNumber], rowRandomNumber, colRandomNumber
        );
        updateSurroundingMineNumber(square);
    }
}
void GameBoard::updateSurroundingMineNumber(Square* square) {
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
        if (newRow < 0 || newRow >= GameBoard::BOARD_SIZE || newCol < 0 ||
            newCol >= GameBoard::BOARD_SIZE)
            continue;
        grid[newRow][newCol]->surroundingMineCount++;
    }
}
