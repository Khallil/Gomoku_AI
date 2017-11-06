#include "core.hpp"

Core::Core() : Ruler::Ruler(), Board::Board(), Ai::Ai()
{
  addPlayer(false, BLACK); // si false n'est pas une ia
  addPlayer(true, WHITE); // si true -> est une ia

  if(!buffer.loadFromFile("click.wav"))
    std::cerr << "can't load click >< ! " << std::endl;
  click.setBuffer(buffer);


  if (!music.openFromFile("AruarianDance.ogg"))
    std::cerr << "can't load Music !! ><' " << std::endl;
  else
    {
      music.play();
      std::cout << "played" << std::endl;
    }
  //music.stop();
  //while(music.getStatus() != 0)
  click.setVolume(100.00);
  std::cout << music.getStatus() << std::endl;
  _players.begin()->beginTurn();
}

Core::~Core()
{
  _players.clear();
  _map.clear();
}

void Core::nextTurn()
{
  click.play();
  std::cout << "click status : " << click.getStatus() << std::endl;
  std::cout << "music status : " << music.getStatus() << std::endl;
  Ruler::manageTurn();
  if (Ruler::itsOVER(*this))
    cleaner();
  _nbTurn++;
}


void Core::playRound()
{
  for (std::vector<Player>::iterator it = _players.begin(); it != _players.end(); it++)
    {
      if ((*it).turn() && !(*it).amIaFUCKINGaI())
        {
          if (_graphics.catchEvent(*this)) // set lastCase
              if (setCase((*it).getColor(), _lastCase.x, _lastCase.y))
                nextTurn();
        }
      else if ((*it).turn() && (*it).amIaFUCKINGaI())
          if (Ai::playTurn(*this))
            if (setCase((*it).getColor(), _lastCase.x, _lastCase.y))
            {
                //last_w.x = _lastCase.x, last_w.y = _lastCase.y;
                nextTurn();
            }
    }
}

bool Core::cleaner()
{
  _graphics.close();
  _players.clear();
  _map.clear();
  exit(0);
}

bool Core::run()
{

  while (_graphics.getWindow()->isOpen())
    {
      if (Ruler::itsOVER(*this))
        {
          //    _graphics.draw(*this);
          return (cleaner());
        }
      _graphics.getWindow()->clear();
      playRound();
      _graphics.draw(*this);
    }
}

int Core::getTotalTurn()
{
  return (_nbTurn);
}
