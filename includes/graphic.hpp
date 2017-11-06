#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "board.hpp"
#include "define.hpp"
#include "AWindow.hpp"

class Graphic
{
public:
  Graphic();
  ~Graphic();

  void Lines();
  void draw(Board &);
  void addPion(const char &, const int &, const int &);
  bool catchEvent(Board &);
  void update(Board &);

  void close();

  sf::RenderWindow *getWindow() { return (&_window);}

protected:
  std::vector<sf::RectangleShape> _line;
  sf::CircleShape                            _circle;
  sf::RenderWindow                _window;
};

#endif
