#ifndef CORE_HPP
#define CORE_HPP

# include "ruler.hpp"
# include "board.hpp"
# include "graphic.hpp"
# include "define.hpp"
# include "ai.hpp"

class Core : public Ruler, public Board, public Ai
{
public:
  Core();
  ~Core();

  bool run();
  void update();
  void playRound();
  bool cleaner();
  void nextTurn();

  int getTotalTurn();

private:
  Graphic _graphics;
  sf::Sound click;
  sf::Music music;
  sf::SoundBuffer buffer;
};


#endif
