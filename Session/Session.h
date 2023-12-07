#ifndef SESSION_H
#define SESSION_H
#include <QString>
#include <utility>
#include <vector>

#include "Timer/Timer.h"
class Square;
class LevelSelectionPage;
class Session {
   public:
    static Session& GetInstance();
    void ResetInstance();
    static std::vector<std::vector<Square*>>& GetBoard();
    static int& GetFlag();  // Done
    static const int& GetMineNumber();
    static int& GetSquareRevealed();  // Done
    static int& GetCorrectFlag();
    static double& GetCellSize();
    static void SetBoardDimension(int row, int col);
    static std::pair<int, int>& GetBoardDimension();
    static const int& GetRow();
    static const int& GetColumn();
    static Timer& GetTimer();
    static QString GetElapsedTimeAsString();
    static void StopTimer();

   private:
    Session();
    ~Session();
    void setupBoard();

   public:
    double s_CellSize;
    std::pair<int, int> s_boardDimension;
    std::vector<std::vector<Square*>> s_board;
    int s_MineNumber;
    int s_FlagSet;
    int s_CorrectFlag;
    int s_SquareRevealed;
    Timer s_timer;
};

#endif