#include "graphic.hpp"

Graphic::Graphic() : _circle(SQUARE_SIZE)
{
  _window.create(sf::VideoMode(FENx, FENy), "Gomoku");
  Lines();
}

Graphic::~Graphic()
{
    _line.clear();
}

void Graphic::Lines()
{
  std::vector<sf::RectangleShape> tmp;
  sf::RectangleShape t;
  size_t x;

   tmp.resize(2, t);
   for (unsigned int y = 0; y < SIZE_Y - 1; y++)
     for (x = 0; x < SIZE_X - 1; x++)
       for (unsigned int e = 0; e < 2; e++)
            {
                tmp[e].setSize((sf::Vector2f(FENy / SIZE_Y, FENy / SIZE_Y)));
                tmp[e].setPosition(POSx, POSy);
                tmp[e].setFillColor(sf::Color(102, 51, 0));
                tmp[e].setOutlineColor(sf::Color::White);
                tmp[e].setOutlineThickness(1);
                _line.push_back(tmp[e]);
            }
}


void Graphic::addPion(const char &c, const int &x, const int &y)
{
  if (c == BLACK)
    _circle.setFillColor(sf::Color::Black);
  if (c == WHITE)
    _circle.setFillColor(sf::Color::White);
  _circle.setPosition(POSx - SQUARE_SIZE, POSy - SQUARE_SIZE);
  _window.draw(_circle);
}

void Graphic::draw(Board &c)
{
  for(std::vector<sf::RectangleShape>::iterator it = _line.begin();
      it != _line.end(); it++)
    _window.draw(*it);

  update(c);
  //c.setCase(NONE, 10, 10);
  _window.display();
}

bool Graphic::catchEvent(Board &a)
{
  sf::Event event;
  int RecT = round(FENy / SIZE_Y) + 1;

  while (!_window.pollEvent(event));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    close();
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      sf::Vector2i pos = sf::Mouse::getPosition(_window);
      if (pos.x <= ((SQUARE_SIZE * 2) + ((SIZE_X - 1) * RecT)) && pos.x >= SQUARE_SIZE &&
          pos.y <= ((SQUARE_SIZE * 2) + ((SIZE_Y - 1) * RecT)) && pos.y >= SQUARE_SIZE)
        {
          if ((pos.y % RecT >= SQUARE_SIZE - INTERVAL && pos.y % RecT <= SQUARE_SIZE + INTERVAL) &&
              (pos.x % RecT >= SQUARE_SIZE - INTERVAL && pos.x % RecT <= SQUARE_SIZE + INTERVAL))
            {
              pos.x = round(pos.x /= RecT);
              pos.y = round(pos.y /= RecT);
              a.setLastCase(vector(pos.x, pos.y));
              return (true);
            }
        }
    }
  return (false);
}

void Graphic::update(Board &c)
{
  int x = 0, y = 0;


  for(auto i1 = c.getMap().begin(); i1 != c.getMap().end(); ++i1)
    {
      for(auto i2 = i1->begin(); i2 != i1->end(); ++i2)
        {
          if ((*i2).getCase() != NONE)
            addPion((*i2).getCase(), x, y);
          x++;
        }
      x = 0;
      y++;
    }
}

void Graphic::close()
{
  _line.clear();
  _window.close();
}
