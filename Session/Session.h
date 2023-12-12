#ifndef SESSION_H
#define SESSION_H
#include <QDataStream>
#include <QFile>
#include <QString>
#include <utility>
#include <vector>
class Timer;
class Square;
enum class State : int8_t { Playing = -2, Not_Playing = -1 };
class Session {
   public:
    static Session& GetInstance();
    static Session& ResetInstance();
    static std::vector<std::vector<Square*>>& GetBoard();
    static int& GetFlag();  // Done
    static int& GetMineNumber();
    static void SetMineNumber(int);
    static int& GetSquareRevealed();  // Done
    static int& GetCorrectFlag();
    static double& GetCellSize();
    static void SetBoardDimension(int row, int col);
    static std::pair<int, int>& GetBoardDimension();
    static const int& GetRow();
    static const int& GetColumn();

    void startTimer();
    void stopTimer();
    void resetTimer();
    static const QString GetElapsedTimeAsString();
    static const Timer& GetTimer();

    void setupBoard();
    void serialize();
    void deserialize();

    friend QDataStream& operator<<(QDataStream& out, const Session& session);
    friend QDataStream& operator>>(QDataStream& in, Session& session);

   private:
    Session();
    ~Session();

   public:
    double s_CellSize;
    std::vector<std::vector<Square*>> s_board;
    std::pair<int, int> s_BoardDimension;
    int s_MineNumber;
    int s_FlagSet;
    int s_CorrectFlag;
    int s_SquareRevealed;
    Timer* timer;
    // add time
};

#endif