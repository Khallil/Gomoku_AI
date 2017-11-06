#ifndef AI_HPP
#define AI_HPP

#include <limits>
#include "board.hpp"
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <map>


class Ai
{
public:
  Ai();
  ~Ai();
  std::vector<vector>  getFirstTokenPosition(Board &);
  std::vector<vector>  getPlayablePosition(Board &, bool, std::vector<vector> &);
  void simulateMove(Board &, bool,int);
  //FONCTION PIERRE CHECK VICTORY
  int min_max(Board &, int, bool, int, int, int, std::vector<vector>);
  int eval(Board &, bool, int, bool);
  bool playTurn(Board &);
  std::vector<int> count_aligned(Board &, bool);
  bool checkSurrounding(Board &, char);
  bool check_win(Board &, bool);
  std::vector<vector> return_aligned(Board &, bool);

private:
  int a;
  int b;
  int depth;
};



#endif
