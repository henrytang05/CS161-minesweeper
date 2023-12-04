#ifndef SESSION_H
#define SESSION_H
#include <utility>
#include <vector>
class Square;
class Session {
   public:
    static Session& GetInstance();
    static std::vector<std::vector<Square*>>& GetBoard();

   private:
    Session();
    ~Session();

   public:
    double cellSize;
    std::pair<int, int> boardDimension;
    std::vector<std::vector<Square*>> board;

    void setupBoard();
    // add time
};

#endif