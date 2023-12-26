#ifndef SESSION_H
#define SESSION_H
#include <QDataStream>
#include <QFile>
#include <QMap>
#include <QObject>
#include <QString>
#include <QTime>
#include <utility>
#include <vector>

#include "Result.h"
class Timer;
class Square;

class Session : public QObject {
    Q_OBJECT
   public:
    enum class State : int8_t { Playing = 4, Win, Lose, None };
    static Session& GetInstance();
    static Session& ResetInstance();
    static Session& ResetForReplay();
    static Session& StartSession();
    static Session& StopSession();
    static Session& ResumeSession();

    static Session::State& GetState();

    static std::vector<std::vector<Square*>>& GetBoard();

    static const int& GetFlag();
    static void IncrementFlag();
    static void DecrementFlag();

    static const int& GetMineNumber();
    static void SetMineNumber(int);

    static const int& GetSquareRevealed();
    static void IncrementSquareRevealed();

    static const double& GetCellSize();
    static void SetCellSize(double);

    static void SetBoardDimension(int row, int col);
    static const int& GetRow();
    static const int& GetColumn();

    static const int& GetDifficulty();

    static std::string GetHighScoreAsString();
    static void SaveHighScores();
    static void GetHighScores();

    void changeState(State);

    void startTimer();
    void stopTimer();
    void resetTimer();
    static std::string GetElapsedTimeAsString();
    static Timer* GetTimer();

    void setupBoard();
    void serialize();
    void deserialize();

    friend QDataStream& operator<<(QDataStream& out, const Session& session);
    friend QDataStream& operator>>(QDataStream& in, Session& session);

   private:
    Session(QObject* parent = nullptr);
    ~Session();

   private:
    State s_state;
    double s_CellSize;
    int s_FlagSet;
    int s_SquareRevealed;
    int s_MineNumber;
    Timer* timer;
    std::pair<int, int> s_BoardDimension;
    std::vector<std::vector<Square*>> s_board;
    int s_difficulty;
    QMap<int, QTime> highScores;  // difficulty, time

   signals:
    void result(Result);
};

#endif