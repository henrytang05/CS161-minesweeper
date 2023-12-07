#include "Session.h"

#include <random>

#include "Square/Square.h"
Session::Session() {
    s_CellSize = 35;
    s_FlagSet = 0;
    s_SquareRevealed = 0;
    s_CorrectFlag = 0;
    s_boardDimension = std::make_pair(0, 0);
    s_MineNumber = 0;
}
Session::~Session() {}
Session& Session::GetInstance() {
    static Session s_instance;
    return s_instance;
}
void Session::ResetInstance() {
    for (auto& row : s_board) {
        for (auto& square : row) {
            delete square;
            square = nullptr;
        }
    }
    s_board.clear();
    s_FlagSet = 0;
    s_SquareRevealed = 0;
    s_CorrectFlag = 0;
    s_boardDimension = std::make_pair(0, 0);
    s_MineNumber = 0;
}
std::vector<std::vector<Square*>>& Session::GetBoard() {
    return Session::GetInstance().s_board;
}
int& Session::GetFlag() { return GetInstance().s_FlagSet; }
int& Session::GetMineNumber() { return GetInstance().s_MineNumber; }
void Session::SetMineNumber(int n) { GetInstance().s_MineNumber = n; }
int& Session::GetSquareRevealed() { return GetInstance().s_SquareRevealed; }
int& Session::GetCorrectFlag() { return GetInstance().s_CorrectFlag; }
double& Session::GetCellSize() { return GetInstance().s_CellSize; }
void Session::SetBoardDimension(int row, int col) {
    Session::GetBoardDimension() = std::make_pair(row, col);
    // Session::GetMineNumber() = row * col / 6;
    GetMineNumber() = GetRow() * GetColumn() / 9;
    GetInstance().setupBoard();
}
std::pair<int, int>& Session::GetBoardDimension() {
    return GetInstance().s_boardDimension;
}
const int& Session::GetRow() { return GetInstance().s_boardDimension.first; }
const int& Session::GetColumn() { return GetInstance().s_boardDimension.second; }

void Session::setupBoard() {
    s_board.resize(
        s_boardDimension.first, std::vector<Square*>(s_boardDimension.second, nullptr)
    );
    for (int row = 0, n = s_boardDimension.first; row < n; row++) {
        for (int col = 0, m = s_boardDimension.second; col < m; col++) {
            s_board[row][col] = new Blank_Square(row, col);
        }
    }
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> row_distribution(0, Session::GetRow() - 1);
    std::uniform_int_distribution<int> col_distribution(0, Session::GetColumn() - 1);
    int rowRandomNumber, colRandomNumber;
    for (int i = 0; i < Session::GetMineNumber(); i++) {
        do {
            rowRandomNumber = row_distribution(generator);
            colRandomNumber = col_distribution(generator);

        } while (dynamic_cast<Mine_Square*>(s_board[rowRandomNumber][colRandomNumber]) !=
                 nullptr);

        delete s_board[rowRandomNumber][colRandomNumber];
        s_board[rowRandomNumber][colRandomNumber] =
            new Mine_Square(rowRandomNumber, colRandomNumber);
    }
}