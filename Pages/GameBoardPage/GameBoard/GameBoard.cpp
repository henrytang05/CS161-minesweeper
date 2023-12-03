#include "GameBoard.h"

#include "Square/Square.h"
#include "Style/Style.h"
std::vector<std::vector<Square*>> GameBoard::grid;
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
GameBoard::~GameBoard() {
    for (auto& row : grid) {
        for (auto& square : row) {
            delete square;
            square = nullptr;
        }
    }
    grid.clear();
}
void GameBoard::setupGameBoard() {
    this->setFixedSize(
        Square::CELL_SIZE * GameBoard::BOARD_SIZE,
        Square::CELL_SIZE * GameBoard::BOARD_SIZE
    );
    grid.resize(
        GameBoard::BOARD_SIZE, std::vector<Square*>(GameBoard::BOARD_SIZE, nullptr)
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
        grid[rowRandomNumber][colRandomNumber]->updateSurrounding('m');
        mainGridLayout->addWidget(
            grid[rowRandomNumber][colRandomNumber], rowRandomNumber, colRandomNumber
        );
    }
}

void GameBoard::revealAllBombs() {
    for (auto row : grid) {
        for (auto square : row) {
            if (square->isMine && square->state == Square::STATE::UnRevealed) {
                if (!square->isFlagged)
                    square->render_square();
                else
                    styleSquare(square, "red");
            }
        }
    }
}
