#ifndef SESSION_H
#define SESSION_H
#include <QDataStream>
#include <QFile>
#include <QObject>
#include <QString>
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
    static Session& StopSession();
    static Session& ResumeSession();
    void GetPreviousSession();
    static std::vector<std::vector<Square*>>& GetBoard();
    static int& GetFlag();
    static int& GetMineNumber();
    static void SetMineNumber(int);
    static int& GetSquareRevealed();
    static int& GetCorrectFlag();
    static double& GetCellSize();
    static void SetBoardDimension(int row, int col);
    static std::pair<int, int>& GetBoardDimension();
    static const int& GetRow();
    static const int& GetColumn();
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
    Timer* timer;
    int s_MineNumber;
    std::pair<int, int> s_BoardDimension;
    std::vector<std::vector<Square*>> s_board;

   signals:
    void result(Result result);
   public slots:
    // void handleResult();
};

#endif