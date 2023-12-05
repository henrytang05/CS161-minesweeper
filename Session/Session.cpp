#include "Session.h"

#include "Square/Square.h"
Session::Session() {
    cellSize = 0;
    s_FlagSet = 0;
    s_SquareRevealed = 0;
    s_CorrectFlag = 0;

    s_boardDimension = std::make_pair(0, 0);
    s_board.resize(0, std::vector<Square*>(0, nullptr));
    s_MineNumber = 0;
}
Session::~Session() {
    for (auto& row : s_board) {
        for (auto& square : row) {
            delete square;
            square = nullptr;
        }
    }
    s_board.clear();
}

Session& Session::GetInstance() {
    static Session s_instance;
    return s_instance;
}
std::vector<std::vector<Square*>>& Session::GetBoard() {
    return Session::GetInstance().s_board;
}
int& Session::GetFlag() { return Session::GetInstance().s_FlagSet; }
int& Session::GetMineNumber() { return Session::GetInstance().s_MineNumber; }
int& Session::GetSquareRevealed() { return Session::GetInstance().s_SquareRevealed; }
int& Session::GetCorrectFlag() { return Session::GetInstance().s_CorrectFlag; }
void Session::SetBoardDimension(int row, int col) {
    Session::GetBoardDimension() = std::make_pair(row, col);
    Session::GetBoard().resize(row, std::vector<Square*>(col, nullptr));
    // Session::GetMineNumber() = row * col / 6;
    Session::GetMineNumber() = 3;
}
std::pair<int, int>& Session::GetBoardDimension() {
    return Session::GetInstance().s_boardDimension;
}
const int& Session::GetRow() { return Session::GetInstance().s_boardDimension.first; }
const int& Session::GetColumn() { return Session::GetInstance().s_boardDimension.second; }

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