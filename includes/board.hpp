# ifndef BOARD
# define BOARD

# include <vector>
# include "define.hpp"
# include <iostream>
#include <SFML/Audio.hpp>

class Board
{
    public:
    Board();
    ~Board();
  sf::Sound click;

    class Case
    {
        public:
      Case(char c) : state(c) {}

      char getCase();
      void setState(const char &c);

      Case &operator<<(const char &);

    protected:
      char state;
    };

  void setLastCase(const vector &v);
  bool setCase(const char &, const int &, const int &);
  char getCase(const int &, const int &);
  std::vector<std::vector<Case> > &getMap();
  bool resetCase(const char &c, const int &x, const int &y);
  vector getLastCase() {return _lastCase;}

protected:
  std::vector<std::vector<Case> > _map;
  vector                          _lastCase;
};

std::ostream& operator<<(std::ostream&, std::vector<std::vector<Board::Case> >&);



#endif
