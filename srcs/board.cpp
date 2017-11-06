# include "board.hpp"

char Board::Case::getCase()
{
  return state;
}

void Board::Case::setState(const char &c)
{
    state = c;
}

Board::Board()
{
    std::vector<Case> tmp;

    tmp.resize(SIZE_X, NONE);
    _map.resize(SIZE_Y, tmp);
}

Board::~Board()
{
    _map.clear();
}

bool Board::setCase(const char &c, const int &x, const int &y)
{
  if (_map[y][x].getCase() == NONE && c != NONE)
    {
      _map[y][x].setState(c);
      return (true);
    }
  return false;
}

bool Board::resetCase(const char &c, const int &x, const int &y)
{
  if (c != NONE)
    return (false);
  _map[y][x].setState(c);
  return (true);
}

char Board::getCase(const int &x, const int &y)
{
  if (x < 0 || x > 18)
    return 'e';
  if (y < 0 || y > 18)
    return 'e';

  return _map[y][x].getCase();
}

std::vector<std::vector<Board::Case> > &Board::getMap()
{
  return _map;
}


Board::Case &Board::Case::operator<<(const char &c)
{
    this->setState(c);
    return(*this);
}

void Board::setLastCase(const vector &v)
{
  _lastCase = v;
}

std::ostream& operator<<(std::ostream &os, std::vector<std::vector<Board::Case> > &map)
{
  for(std::vector<std::vector<Board::Case> >::iterator it = map.begin();it!=map.end();++it)
  {
        for(std::vector<Board::Case>::iterator it2 = it->begin();it2!=it->end();++it2)
            os << (*it2).getCase() << " ";
        os << std::endl;
  }
  return (os);
}
