#include "Session.h"

#include <random>

#include "GameboardPage/GameboardPage.h"
#include "Square/Square.h"
#include "Timer/Timer.h"
Session::Session(QObject* parent) : QObject(parent) {
    s_state = State::None;
    s_CellSize = 35;
    s_FlagSet = 0;
    s_CorrectFlag = 0;
    s_SquareRevealed = 0;
    s_MineNumber = 0;
    s_BoardDimension = std::make_pair(0, 0);
    timer = new Timer;
}
Session::~Session() { delete timer; }
Session& Session::GetInstance() {
    static Session s_instance;
    return s_instance;
}
Session& Session::ResetInstance() {
    // squares are automically deallocated by qt
    auto& s = GetInstance();
    s.s_board.clear();
    // s.s_CellSize = 0;
    s.s_BoardDimension = std::make_pair(0, 0);
    s.s_MineNumber = 0;
    s.s_FlagSet = 0;
    s.s_CorrectFlag = 0;
    s.s_SquareRevealed = 0;
    s.timer->resetTimer();

    return s;
}
void Session::GetPreviousSession() { Session::GetInstance().deserialize(); }
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
}
std::pair<int, int>& Session::GetBoardDimension() {
    return GetInstance().s_BoardDimension;
}
const int& Session::GetRow() { return GetInstance().s_BoardDimension.first; }
const int& Session::GetColumn() { return GetInstance().s_BoardDimension.second; }

void Session::changeState(State newstate) {
    if (s_state == newstate) return;
    s_state = newstate;

    switch (newstate) {
        case State::Win:
            this->stopTimer();
            emit this->result(Win);
            break;
        case State::Lose:
            this->stopTimer();
            emit this->result(Result::Lose);
            break;
    }
}

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

        } while (s_board[rowRandomNumber][colRandomNumber]->type == Square_Type::Mine);

        delete s_board[rowRandomNumber][colRandomNumber];
        s_board[rowRandomNumber][colRandomNumber] =
            new Mine_Square(rowRandomNumber, colRandomNumber);

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
            int newRow = rowRandomNumber + move[0];
            int newCol = colRandomNumber + move[1];
            if (newRow < 0 || newRow >= Session::GetRow() || newCol < 0 ||
                newCol >= Session::GetColumn())
                continue;
            s_board[newRow][newCol]->surroundingMineCount++;
        }
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
    out << Session::GetInstance();
    file.close();
}

QDataStream& operator<<(QDataStream& out, const Session& session) {
    out << session.s_state;
    out << session.s_CellSize;
    out << session.s_FlagSet;
    out << session.s_CorrectFlag;
    out << session.s_SquareRevealed;
    out << session.s_MineNumber;
    out << session.s_BoardDimension.first;
    out << session.s_BoardDimension.second;
    for (int i = 0; i < session.GetInstance().s_BoardDimension.first; i++) {
        for (int j = 0; j < session.GetInstance().s_BoardDimension.second; j++) {
            out << *(session.s_board[i][j]);
        }
    }
    out << session.timer->elapsedTime;
    return out;
}
void Session::deserialize() {
    QFile file("save.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading: " << qPrintable(file.errorString())
                 << '\n';
        return;
    }
    file.seek(sizeof(State));
    QDataStream in(&file);

    in >> Session::GetInstance();
    file.close();
}
QDataStream& operator>>(QDataStream& in, Session& session) {
    in >> session.s_CellSize;
    in >> session.s_FlagSet;
    in >> session.s_CorrectFlag;
    in >> session.s_SquareRevealed;
    in >> session.s_MineNumber;
    in >> session.s_BoardDimension.first;
    in >> session.s_BoardDimension.second;
    session.s_board.resize(
        session.s_BoardDimension.first,
        std::vector<Square*>(session.s_BoardDimension.second, nullptr)
    );
    for (int i = 0; i < session.GetInstance().s_BoardDimension.first; i++) {
        for (int j = 0; j < session.GetInstance().s_BoardDimension.second; j++) {
            Square_Type type;
            in >> type;
            if (type == Square_Type::Blank) {
                session.s_board[i][j] = new Blank_Square(i, j);
            } else if (type == Square_Type::Mine) {
                session.s_board[i][j] = new Mine_Square(i, j);
            }
            session.s_board[i][j]->type = type;
            in >> *(session.s_board[i][j]);
            session.s_board[i][j]->render_square();
        }
    }
    in >> session.timer->elapsedTime;
    return in;
}
void Session::startTimer() { timer->startTimer(); }
void Session::stopTimer() { timer->stopTimer(); }
void Session::resetTimer() { timer->resetTimer(); }
const QString Session::GetElapsedTimeAsString() {
    return GetInstance().timer->elapsedTime.toString("mm:ss");
}
Timer* Session::GetTimer() { return GetInstance().timer; }

Session& Session::StopSession() {
    auto& s = GetInstance();
    s.stopTimer();
    return s;
}
Session& Session::ResumeSession() {
    auto& s = GetInstance();
    s.deserialize();
    s.startTimer();
    return s;
}
Session& Session::StartSession() {
    auto& s = GetInstance();
    s.changeState(State::Playing);
    s.setupBoard();
    s.startTimer();
    return s;
}