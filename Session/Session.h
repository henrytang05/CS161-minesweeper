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
    static void SaveHighScores();
    static void GetHighScores();

    static std::vector<std::vector<Square*>>& GetBoard();
    static int& GetFlag();
    static const int& GetMineNumber();
    static void SetMineNumber(int);
    static int& GetSquareRevealed();
    static int& GetCorrectFlag();
    static double& GetCellSize();
    static void SetBoardDimension(int row, int col);
    static std::pair<int, int>& GetBoardDimension();
    static const int& GetRow();
    static const int& GetColumn();
    static const int& GetDifficulty();
    static const QString GetHighScoreAsString();
    void changeState(State);

    void startTimer();
    void stopTimer();
    void resetTimer();
    static const QString GetElapsedTimeAsString();
    static Timer* GetTimer();

    void setupBoard();
    void serialize();
    void deserialize();

    friend QDataStream& operator<<(QDataStream& out, const Session& session);
    friend QDataStream& operator>>(QDataStream& in, Session& session);

   private:
    Session(QObject* parent = nullptr);
    ~Session();

   public:
    State s_state;
    double s_CellSize;
    int s_FlagSet;
    int s_CorrectFlag;
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