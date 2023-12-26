#include "Session.h"

#include <cmath>
#include <random>

#include "GameboardPage/GameboardPage.h"
#include "Square/Square.h"
#include "Timer/Timer.h"
Session::Session(QObject* parent) : QObject(parent) {
    s_state = State::None;
    s_CellSize = 0;
    s_FlagSet = 0;
    s_SquareRevealed = 0;
    s_MineNumber = 0;
    timer = new Timer(this);
    s_BoardDimension = std::make_pair(0, 0);
    s_difficulty = 0;
}
Session::~Session() {}
Session& Session::GetInstance() {
    static Session s_instance;
    return s_instance;
}
Session& Session::ResetInstance() {
    // squares are automically deallocated by qt
    auto& s = GetInstance();
    s.s_state = State::None;
    s.s_CellSize = 0;
    s.s_FlagSet = 0;

    s.s_SquareRevealed = 0;
    s.s_MineNumber = 0;
    s.timer->resetTimer();
    s.s_BoardDimension = std::make_pair(0, 0);
    s.s_board.clear();
    s.s_difficulty = 0;
    return s;
}
Session& Session::ResetForReplay() {
    auto& s = GetInstance();
    s.s_state = State::Playing;
    s.s_FlagSet = 0;
    s.s_SquareRevealed = 0;
    s.timer->resetTimer();
    s.setupBoard();
    return s;
}
Session& Session::StartSession() {
    auto& s = GetInstance();
    s.changeState(State::Playing);
    s.s_difficulty = std::max(
        (int)std::round(GetMineNumber() * 100 / (1.0f * GetRow() * GetColumn())), 1
    );
    s.setupBoard();
    return s;
}
Session& Session::StopSession() {
    auto& s = GetInstance();
    s.stopTimer();
    s.serialize();
    // TODO: save session
    return s;
}
Session& Session::ResumeSession() {
    auto& s = GetInstance();
    s.deserialize();
    s.startTimer();
    return s;
}
Session::State& Session::GetState() { return Session::GetInstance().s_state; }
std::vector<std::vector<Square*>>& Session::GetBoard() {
    return Session::GetInstance().s_board;
}
const int& Session::GetFlag() { return GetInstance().s_FlagSet; }
void Session::IncrementFlag() { GetInstance().s_FlagSet++; }
void Session::DecrementFlag() { GetInstance().s_FlagSet--; }
const int& Session::GetMineNumber() { return GetInstance().s_MineNumber; }
void Session::SetMineNumber(int mineNumber) { GetInstance().s_MineNumber = mineNumber; }
const int& Session::GetSquareRevealed() { return GetInstance().s_SquareRevealed; }
void Session::IncrementSquareRevealed() { GetInstance().s_SquareRevealed++; }

const double& Session::GetCellSize() { return GetInstance().s_CellSize; }

void Session::SetCellSize(double size) { Session::GetInstance().s_CellSize = size; }

void Session::SetBoardDimension(int row, int col) {
    Session::GetInstance().s_BoardDimension = std::make_pair(row, col);
}

const int& Session::GetRow() { return GetInstance().s_BoardDimension.first; }
const int& Session::GetColumn() { return GetInstance().s_BoardDimension.second; }
const int& Session::GetDifficulty() { return GetInstance().s_difficulty; }

std::string Session::GetHighScoreAsString() {
    if (!GetInstance().highScores.contains(Session::GetDifficulty())) return "00:00";
    return Session::GetInstance()
        .highScores[Session::GetDifficulty()]
        .toString("mm:ss")
        .toStdString();
}
void Session::changeState(State newstate) {
    if (s_state == newstate) return;
    s_state = newstate;
    switch (newstate) {
        case State::Win:
            this->stopTimer();
            if (highScores.contains(s_difficulty)) {
                if (highScores[s_difficulty] > timer->elapsedTime) {
                    highScores[s_difficulty] = timer->elapsedTime;
                }
            } else {
                highScores[s_difficulty] = timer->elapsedTime;
            }
            emit this->result(Result::Win);
            break;
        case State::Lose:
            this->stopTimer();
            emit this->result(Result::Lose);
            break;
        default:
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
    QFile file(":/Data/Session.dat");
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

    out << session.s_SquareRevealed;
    out << session.s_MineNumber;
    out << session.timer->elapsedTime;
    out << session.s_BoardDimension.first;
    out << session.s_BoardDimension.second;
    for (int i = 0; i < session.GetInstance().s_BoardDimension.first; i++) {
        for (int j = 0; j < session.GetInstance().s_BoardDimension.second; j++) {
            out << *(session.s_board[i][j]);
        }
    }
    out << session.s_difficulty;

    return out;
}
void Session::deserialize() {
    QFile file(":/Data/Session.dat");
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
    in >> session.s_SquareRevealed;
    in >> session.s_MineNumber;
    in >> session.timer->elapsedTime;

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
    in >> session.s_difficulty;

    return in;
}
void Session::startTimer() { timer->startTimer(); }
void Session::stopTimer() { timer->stopTimer(); }
void Session::resetTimer() { timer->resetTimer(); }
std::string Session::GetElapsedTimeAsString() {
    return GetInstance().timer->elapsedTime.toString("mm:ss").toStdString();
}
Timer* Session::GetTimer() { return GetInstance().timer; }

void Session::SaveHighScores() {
    QFile file(":/Data/Highscores.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing: " << qPrintable(file.errorString())
                 << '\n';
        return;
    }
    QDataStream out(&file);
    out << Session::GetInstance().highScores;
}
void Session::GetHighScores() {
    QFile file(":/Data/Highscores.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading: " << qPrintable(file.errorString())
                 << '\n';
        return;
    }
    file.seek(0);
    QDataStream in(&file);
    in >> Session::GetInstance().highScores;
}
