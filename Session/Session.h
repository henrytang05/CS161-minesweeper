#ifndef SESSION_H
#define SESSION_H
#include <utility>
#include <vector>
class Square;
class Session {
   public:
    static Session& GetInstance();
    static std::vector<std::vector<Square*>>& GetBoard();
    static int& GetFlag();  // Done
    static int& GetMineNumber();
    static int& GetSquareRevealed();  // Done
    static int& GetCorrectFlag();
    static void SetBoardDimension(int row, int col);
    static std::pair<int, int>& GetBoardDimension();
    static const int& GetRow();
    static const int& GetColumn();
    void setupBoard();
    ~Session();

   private:
    Session();

   public:
    double cellSize;
    std::pair<int, int> s_boardDimension;
    std::vector<std::vector<Square*>> s_board;
    int s_MineNumber;
    int s_FlagSet;
    int s_CorrectFlag;
    int s_SquareRevealed;
    // add time
};

#endif