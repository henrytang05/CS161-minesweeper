#include "GameBoard.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
GameBoard::GameBoard(QWidget* parent, int level) : QWidget(parent) {
    int tmp = 0;
    switch (level) {
        case 1:
            tmp = 9;
            break;
        case 2:
            tmp = 16;
            break;
        case 3:
            tmp = 30;
            break;
        default:
            break;
            // TODO: add customization
    }
    Session::SetBoardDimension(tmp, tmp);  //
    setupGameBoard();
}
GameBoard::~GameBoard() {}
void GameBoard::setupGameBoard() {
    auto& board = Session::GetBoard();

    this->setFixedSize(
        Square::CELL_SIZE * Session::GetColumn(), Square::CELL_SIZE * Session::GetRow()
    );

    QGridLayout* mainGridLayout = new QGridLayout(this);

    for (int row = 0, n = Session::GetRow(); row < n; row++) {
        for (int col = 0, m = Session::GetColumn(); col < m; col++) {
            Square* square = new Blank_Square(row, col, this);
            styleSquare(square);
            QObject::connect(square, &Square::result, this, &GameBoard::result);
            board[row][col] = square;
            mainGridLayout->addWidget(square, row, col);
        }
    }
    this->setLayout(mainGridLayout);
    initializeGameBoard(mainGridLayout);
}
void GameBoard::initializeGameBoard(QGridLayout* mainGridLayout) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> row_distribution(0, Session::GetRow() - 1);
    std::uniform_int_distribution<int> col_distribution(0, Session::GetColumn() - 1);
    for (int i = 0; i < Session::GetMineNumber(); i++) {
        auto& board = Session::GetBoard();

        int rowRandomNumber, colRandomNumber;

        do {
            rowRandomNumber = row_distribution(generator);
            colRandomNumber = col_distribution(generator);

        } while (dynamic_cast<Mine_Square*>(board[rowRandomNumber][colRandomNumber]) !=
                 nullptr);

        delete board[rowRandomNumber][colRandomNumber];
        board[rowRandomNumber][colRandomNumber] =
            new Mine_Square(rowRandomNumber, colRandomNumber, this);
        Square* square = board[rowRandomNumber][colRandomNumber];
        QObject::connect(square, &Square::result, this, &GameBoard::result);
        styleSquare(square);
        mainGridLayout->addWidget(
            board[rowRandomNumber][colRandomNumber], rowRandomNumber, colRandomNumber
        );
        updateSurroundingMineNumber(square);
    }
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
