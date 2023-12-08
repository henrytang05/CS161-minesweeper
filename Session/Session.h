#ifndef SESSION_H
#define SESSION_H
#include <QDataStream>
#include <QFile>
#include <utility>
#include <vector>
class Square;
class Session {
   public:
    static Session& GetInstance();
    void ResetInstance();
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
    std::pair<int, int> s_BoardDimension;
    std::vector<std::vector<Square*>> s_board;
    int s_MineNumber;
    int s_FlagSet;
    int s_CorrectFlag;
    int s_SquareRevealed;
    // add time
};

#endif