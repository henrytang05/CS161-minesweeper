#include "Session.h"

#include <random>

#include "Square/Square.h"
Session::Session() {
    s_CellSize = 35;
    s_FlagSet = 0;
    s_SquareRevealed = 0;
    s_CorrectFlag = 0;
    s_BoardDimension = std::make_pair(0, 0);
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
    s_BoardDimension = std::make_pair(0, 0);
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
}
std::pair<int, int>& Session::GetBoardDimension() {
    return GetInstance().s_BoardDimension;
}
const int& Session::GetRow() { return GetInstance().s_BoardDimension.first; }
const int& Session::GetColumn() { return GetInstance().s_BoardDimension.second; }

void Session::setupBoard() {
    s_board.resize(
        s_BoardDimension.first, std::vector<Square*>(s_BoardDimension.second, nullptr)
    );
    for (int row = 0, n = s_BoardDimension.first; row < n; row++) {
        for (int col = 0, m = s_BoardDimension.second; col < m; col++) {
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
void Session::serialize() {
    QFile file("save.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing: " << qPrintable(file.errorString())
                 << '\n';
        return;
    }
    QDataStream out(&file);
    auto& session = Session::GetInstance();
    out << session;
    file.close();
}

QDataStream& operator<<(QDataStream& out, const Session& session) {
    out << session.s_CellSize;
    out << session.s_BoardDimension.first;
    out << session.s_BoardDimension.second;
    out << session.s_MineNumber;
    out << session.s_FlagSet;
    out << session.s_CorrectFlag;
    out << session.s_SquareRevealed;
    for (int i = 0; i < session.GetInstance().s_BoardDimension.first; i++) {
        for (int j = 0; j < session.GetInstance().s_BoardDimension.second; j++) {
            out << session.s_board[i][j]->state;
            out << session.s_board[i][j]->row;
            out << session.s_board[i][j]->col;
            out << session.s_board[i][j]->surroundingMineCount;
            out << session.s_board[i][j]->surroundingFlagCount;
        }
    }
    return out;
}
void Session::deserialize() {
       QFile file("save.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading: " << qPrintable(file.errorString())
                 << '\n';
        return;
    }
    QDataStream in(&file);
    auto& session = Session::GetInstance();
    in >> session;
    file.close();
}
QDataStream& operator>>(QDataStream& in, Session& session) {
    in >> session.s_CellSize;
    in >> session.s_BoardDimension.first;
    in >> session.s_BoardDimension.second;
    in >> session.s_MineNumber;
    in >> session.s_FlagSet;
    in >> session.s_CorrectFlag;
    in >> session.s_SquareRevealed;
    // Add deserialization for s_board here
    session.s_board.resize(
        session.s_BoardDimension.first,
        std::vector<Square*>(session.s_BoardDimension.second, nullptr)
    );
    for (int i = 0; i < session.GetInstance().s_BoardDimension.first; i++) {
        for (int j = 0; j < session.GetInstance().s_BoardDimension.second; j++) {
            in >> session.s_board[i][j]->state;
            in >> session.s_board[i][j]->row;
            in >> session.s_board[i][j]->col;

            in >> session.s_board[i][j]->surroundingMineCount;
            in >> session.s_board[i][j]->surroundingFlagCount;
        }
    }
    return in;
}