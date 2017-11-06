# include "ruler.hpp"

Ruler::Ruler() : _nbTurn(0), _countBlack(0), _countWhite(0), _turn(0)
{
  if(!buffer.loadFromFile("TreasureChest.wav"))
    std::cerr << "can't load win ! >< ! " << std::endl;
  win.setBuffer(buffer);
}


void Ruler::Win(char color)
{
  if (color == BLACK)
    std::cout << "Black Won" << std::endl;
  else
    std::cout << "White Won" << std::endl;
  win.play();
  while(win.getStatus() != 0);
}

bool Ruler::check_win(Board &b, char color)
{
  std::vector<int> combo;
  char f = color;
  int count;
  int y;
  int x;
  int t;
  count = 0;
  for (int y = 0; y < 19; y++) // horizontale
    {
      for  (int x = 0; x < 19; x++)
        {
          if (b.getCase(x,y) == f)
            {
              while (b.getCase(x,y) == f)
                {
                  count++;
                  x++;
                  if (x > 18)
                    break;
                }
              if (count >= 5)
                {
                  Win(color);
                  return true;
                };
              count = 0;
            }
        }
    }

  count = 0;
  for (int x = 0; x < 19; x++) // verticale
    {
      for (int y = 0; y < 19; y++)
        {
          if (b.getCase(x,y) == f)
            {
              while (b.getCase(x,y) == f)
                {
                  count++;
                  y++;
                  if (y > 18)
                    break;
                }
              if (count >= 5)
                {
                  Win(color);
                  return true;
                }
              count = 0;
            }
        }
    }

  t = 15;
  count = 0;
  while (t > -1) // down_diagonal first part
    {
      y = t;
      x = 0;
      while (y < 19)
        {
          if (b.getCase(x,y) == f)
            {
              while (b.getCase(x,y) == f)
                {
                  count++;
                  x++;
                  y++;
                  if (y > 18 || x > 18)
                    break;
                }
              if (count >= 5 )
                {
                  Win(color);
                  return true;
                }
              count = 0;
            }
          y++;
          x++;
        }
      t--;
    }

  x = 0;
  y = 0;
  t = 1;
  count = 0;
  while (t < 16) // down_diagonal second part
    {
      x = t;
      y = 0;
      while (x <= 19)
        {
          if (b.getCase(x,y) == f)
            {
              while (b.getCase(x,y) == f)
                {
                  count++;
                  x++;
                  y++;
                  if (y > 18 || x > 18)
                    break;
                }
              if (count >= 5)
                {
                  Win(color);
                  return true;
                }
              count = 0;
            }
          x++;
          y++;
        }
      t++;
    }
  t = 4;
  count = 0;
  while (t < 19) // up_diagonal first part
    {
      y = t;
      x = 0;
      while (y > -1)
        {
          if (b.getCase(x,y) == f)
            {
              while (b.getCase(x,y) == f)
                {
                  count++;
                  x++;
                  y--;
                  if (y < 0 || x > 18)
                    break;
                }
              if (count >= 5)
                {
                  Win(color);
                  return true;
                }
              count = 0;
            }
          y--;
          x++;
        }
      t++;
    }
  t = 1;
  count = 0;
  while (t < 16) // up diagonal second part
    {
      y = 18;
      x = t;
      while (x < 19)
        {
          if (b.getCase(x,y) == f)
            {
              while (b.getCase(x,y) == f)
                {
                  count++;
                  x++;
                  y--;
                  if (y < 0 || x > 18)
                    break;
                }
              if (count >= 5)
                {
                  Win(color);
                  return true;
                }
              count = 0;
            }
          x++;
          y--;
        }
      t++;
    }
  return false;
}
bool Ruler::checkSurronding(Board &b, char color)
{
  std::vector<int> combo;
  char f = color;
  char e;
  int count;
  int y;
  int x;
  int t;
  if (f == WHITE)
    e = BLACK;
  else
    e = WHITE;
  for (int y = 0; y < 19; y++) // horizontale
    {
      for  (int x = 0; x < 19; x++)
        {
          if (b.getCase(x,y) == f)
            {
              if (b.getCase(x + 1, y) == e && b.getCase(x + 2, y) == e && b.getCase(x + 3, y) == f)
                {
                  if (b.getCase(x,y) == WHITE)
                    _countWhite++;
                  if (b.getCase(x,y) == BLACK)
                    _countBlack++;
                  b.resetCase(NONE, x + 1, y);
                  b.resetCase(NONE, x + 2, y);
                }
            }
        }
    }

  for (int x = 0; x < 19; x++) // verticale
    {
      for (int y = 0; y < 16; y++)
        {
          if (b.getCase(x,y) == f)
            {
              if (b.getCase(x, y + 1) == e && b.getCase(x, y + 2) == e && b.getCase(x, y + 3) == f)
                {
                  if (y > 18 || x > 18)
                    break;
                  if (b.getCase(x,y) == WHITE)
                    _countWhite++;
                  if (b.getCase(x,y) == BLACK)
                    _countBlack++;
                  b.resetCase(NONE, x, y + 1);
                  b.resetCase(NONE, x, y + 2);
                }
            }
        }
    }

  t = 15;
  while (t > -1) // down_diagonal first part
    {
      y = t;
      x = 0;
      while (y < 16)
        {
          if (b.getCase(x,y) == f)
            {
              if (b.getCase(x - 1, y + 1) == e && b.getCase(x - 2, y + 2) == e && b.getCase(x - 3, y + 3) == f)
                {
                  if (b.getCase(x,y) == WHITE)
                    _countWhite++;
                  if (b.getCase(x,y) == BLACK)
                    _countBlack++;
                  b.resetCase(NONE, x - 1, y + 1);
                  b.resetCase(NONE, x - 2, y + 2);
                  x++;
                  y++;
                  if (y > 18 || x > 18)
                    break;
                }
            }
          y++;
          x++;
        }
      t--;
    }

  x = 0;
  y = 0;
  t = 1;
  count = 0;
  while (t < 19) // down_diagonal second part
    {
      x = t;
      y = 0;
      while (x < 19)
        {
          if (b.getCase(x,y) == f)
            {
              if (b.getCase(x - 1, y + 1) == e && b.getCase(x - 2, y + 2) == e && b.getCase(x - 3, y + 3) == f)
                {
                  if (b.getCase(x,y) == WHITE)
                    _countWhite++;
                  if (b.getCase(x,y) == BLACK)
                    _countBlack++;
                  b.resetCase(NONE, x - 1, y + 1);
                  b.resetCase(NONE, x - 2, y + 2);
                  x++;
                  y++;
                  if (y > 18 || x > 18)
                    break;
                }
            }
          x++;
          y++;
        }
      t++;
    }

  t = 0;
  while (t < 16) // up_diagonal first part
    {
      y = t;
      x = 0;
      while (y > -1)
        {
          if (b.getCase(x,y) == f)
            {
              if (b.getCase(x + 1, y + 1) == e && b.getCase(x + 2, y + 2) == e && b.getCase(x + 3, y + 3) == f)
                {
                  if (b.getCase(x,y) == WHITE)
                    _countWhite++;
                  if (b.getCase(x,y) == BLACK)
                    _countBlack++;
                  b.resetCase(NONE, x + 1, y + 1);
                  b.resetCase(NONE, x + 2, y + 2);
                  x++;
                  y--;
                  if (y > 18 || x > 18)
                    break;
                }

            }
          y--;
          x++;
        }
      t++;
    }

  t = 0;
  while (t < 16) // up diagonal second part
    {
      y = 15;
      x = t;
      while (x < 16)
        {
          if (b.getCase(x,y) == f)
            {
              if (b.getCase(x + 1, y + 1) == e && b.getCase(x + 2, y + 2) == e && b.getCase(x + 3, y + 3) == f)
                {
                  if (b.getCase(x,y) == WHITE)
                    _countWhite++;
                  if (b.getCase(x,y) == BLACK)
                    _countBlack++;
                  b.resetCase(NONE, x + 1, y + 1);
                  b.resetCase(NONE, x + 2, y + 2);
                  x++;
                  y--;
                  if (y > 18 || x > 18)
                    break;
                }
            }
          x++;
          y--;
        }
      t++;
    }
  if (_countBlack == 20)
    {
      std::cout << "Black Won" << std::endl;
      return true;
    }
  if (_countWhite == 20)
    {
      std::cout << "White Won" << std::endl;
      return true;
    }
  return (false);
}

bool Ruler::itsOVER(Board &b)
{
  Ai ia;

  if (_nbTurn)
    {

      char   c;
      c = b.getCase(b.getLastCase().x, b.getLastCase().y);
      if (check_win(b, BLACK) || check_win(b, WHITE) || checkSurronding(b, BLACK) || checkSurronding(b, WHITE))
         {
            std::cout << "WHITE : " << _countWhite << std::endl;
            std::cout << "BLACK : " << _countBlack << std::endl;
           return true;
         }
    }
  return (false);
}

void Ruler::addPlayer(const bool &ia, const char &color)
{
  _players.push_back(Player(ia, color));
}

Ruler::~Ruler()
{
  _players.clear();
}

void Ruler::manageTurn()
{
  // OMG J AI HONTE

  if(_players[0].turn())
    {
           std::cout << "WHITE : " << _countWhite << std::endl;
      std::cout << "BLACK : " << _countBlack << std::endl;
      _players[0].endTurn();
      _players[1].beginTurn();
    }
  else if(_players[1].turn())
    {
       std::cout << "WHITE : " << _countWhite << std::endl;
      std::cout << "BLACK : " << _countBlack << std::endl;
      _players[1].endTurn();
      _players[0].beginTurn();
    }
}

/********************************************
                 PLAYER
*********************************************/

Ruler::Player::Player(const bool &isIa, const char &c) : _myTurn(false), _color(c), _ia(isIa)
{
}

Ruler::Player::~Player()
{}
