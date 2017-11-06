#ifndef RULER_HPP
#define RULER_HPP

# include "define.hpp"
# include "board.hpp"
# include "ai.hpp"
#include <SFML/Audio.hpp>

class Ruler
{
public:
  Ruler();
  ~Ruler();

  bool itsOVER(Board &);
  void Win(char);
  bool check_win(Board &, char);
  bool checkSurronding(Board &, char);
  void addPlayer(const bool &, const char &);

  void manageTurn();

protected:

  class Player
  {
  public:

    Player(const bool &, const char &);
    ~Player();

    void beginTurn(){ _myTurn = true;}
    void endTurn() {_myTurn = false;}
    bool turn() { return _myTurn;}

    char getColor() { return _color; }
    bool amIaFUCKINGaI() {return _ia;}
  private:
    bool _myTurn;
    char _color;
    bool _ia;
  };

protected:
  std::vector<Player> _players;
  int                 _nbTurn;
  unsigned int        _turn;
  unsigned int        _countWhite;
  unsigned int        _countBlack;
  sf::SoundBuffer buffer;
  sf::Sound win;

};

#endif
