#include "Session.h"

#include "Square/Square.h"
Session::Session() {
    cellSize = 35;
    boardDimension = std::make_pair(9, 9);
    board.resize(9, std::vector<Square*>(9, nullptr));
}
Session::~Session() {
    for (auto& row : board) {
        for (auto& square : row) {
            delete square;
            square = nullptr;
        }
    }
    board.clear();
}

Session& Session::GetInstance() {
    static Session instance;
    return instance;
}
void Session::setupBoard() {
    // board.resize(
    //     boardDimension.first, std::vector<Square*>(boardDimension.second, nullptr)
    // );
    // for (int row = 0; row < boardDimension.first; row++) {
    //     for (int col = 0; col < boardDimension.second; col++) {
    //         Square* square = new Blank_Square(row, col, this);
    //         styleSquare(square);
    //         QObject::connect(square, &Square::result, this, &GameBoard::result);
    //         grid[row][col] = square;
    //         mainGridLayout->addWidget(square, row, col);
    //     }
    // }
}