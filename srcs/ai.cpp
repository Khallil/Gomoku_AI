# include "ai.hpp"

Board board;
std::map<int, int> first_move;
int alpha = -2000;
int global = 0;
vector last_w;
vector last_b;

Ai::Ai(){}

Ai::~Ai(){}

bool Ai::playTurn(Board &b) // Fonction qui est appelé après le tour du joueur
{
  board = b;
  std::clock_t  t;
  double duration;
  int alpha = -2000;
  int beta = 2000;
  vector chosen_case; // vecteur qui récupère la case à jouer après l'algo de l'IA

  std::cout << "ia turn" << std::endl;
  last_b = b.getLastCase();
  std::vector<vector> v;
  v = getFirstTokenPosition(b);
  //std::vector<vector> test_playable_pos = getPlayablePosition(b, true, v);
  t = std::clock();
  min_max(b, MAX_DEPTH, true, 0, alpha, beta, v);
  std::map<int, int>::iterator save_it;

  int higher_move = -2000;
  for (std::map<int, int>::iterator it = first_move.begin(); it != first_move.end(); it++)
  {
     if ((*it).second > higher_move)
      {
        higher_move = ((*it).second);
        save_it = it;
      }
        //std::cout << "rav" << std::endl;
  }

  std::cout << "best move : " << higher_move << std::endl;
  std::vector<vector> playable_pos = getPlayablePosition(b, true, v);
  Board x = b;
  for (std::vector<vector>::iterator itx = playable_pos.begin(); itx != playable_pos.end(); itx++)
  {
    x.setCase('p',(*itx).x,(*itx).y);
  }
  std::cout << x.getMap();
  int count;
  count = 0;
  std::vector<vector>::iterator it2 = playable_pos.begin();
  while (it2 != playable_pos.end())
  {
    if ((*save_it).first == count)
    {
      b.setLastCase((*it2));
      std::cout << "IA a set Case" << std::endl;
      last_w = vector ((*it2).x, (*it2).y );
      first_move.clear();
      break;
    }
    count++;
    it2++;
  }
  std::cout << "Nombres de branches coupées : " << global << std::endl;
  duration = (std::clock() - t) / (double)CLOCKS_PER_SEC;
  std::cout << "Ia duration = " << duration << std::endl;
  return (true);
}

std::vector<vector> Ai::getFirstTokenPosition(Board &c)
{
  std::vector<vector> token_pos;
  token_pos.push_back(last_b);
  if (last_w.x >= 0 && last_w.y <= 18)
    token_pos.push_back(last_w);

  return token_pos;
}

std::vector<vector> Ai::getPlayablePosition(Board &c, bool white, std::vector<vector> &token_pos)
{
  std::vector<vector> bucket;
  std::vector<vector> token_pos_w = return_aligned(c, true);
  std::vector<vector> token_pos_b = return_aligned(c, false);
  token_pos.insert(token_pos.end(), token_pos_w.begin(), token_pos_w.end());
  token_pos.insert(token_pos.end(), token_pos_b.begin(), token_pos_b.end());

  int count;
  count = 0;
  for(std::vector<vector>:: iterator it = token_pos.begin(); it != token_pos.end(); ++it)
    {
      if(it->x -1 >= 0 && c.getCase(it->x-1, it->y) == 'n')
        bucket.push_back(vector(it->x-1, it->y));
      if(it->x - 1 >= 0 && it->y -1 >= 0 && c.getCase(it->x-1, it->y-1) == 'n')
        bucket.push_back(vector(it->x-1, it->y-1));

      if(it->y -1 >= 0 && c.getCase(it->x, it->y-1) == 'n')
        bucket.push_back(vector(it->x, it->y-1));
      if(it->x + 1 <= 18 && it->y -1 >= 0 && c.getCase(it->x+1, it->y-1) == 'n')
        bucket.push_back(vector(it->x+1, it->y-1));

      if(it->x + 1 <= 18 && c.getCase(it->x+1, it->y) == 'n')
        bucket.push_back(vector(it->x+1, it->y));
      if(it->x + 1 <= 18 && it->y +1 <= 18 && c.getCase(it->x+1, it->y+1) == 'n')
        bucket.push_back(vector(it->x+1, it->y+1));

      if(it->y + 1 <= 18 && c.getCase(it->x, it->y+1) == 'n')
        bucket.push_back(vector(it->x, it->y+1));
      if(it->x - 1 >= 0 && it->y +1 <= 18 && c.getCase(it->x-1, it->y+1) == 'n')
        bucket.push_back(vector(it->x-1, it->y+1));

    }
  return bucket;
}

int Ai::min_max(Board &b, int depth, bool ia, int id, int alpha, int beta, std::vector<vector> v)
{
  char f = (ia) ? 'w' : 'b';
  if (check_win(b, !ia))
  {
      int a = eval(b, !ia, depth, true);
      return (a);
  }
  if (checkSurrounding(b, WHITE) == true)
    return (500);
  if (checkSurrounding(b, BLACK) == true)
    return (-500);
  if (depth == 0)
  {
      int e = (eval(b, !ia, depth, false) + eval(b, ia, depth, false));
      return (e);
  }
  Board c = b;
  Board d = b;
  std::vector<vector> new_v;
  if (depth < MAX_DEPTH)
      new_v.push_back( v.back() );

  std::vector<vector> playable_pos = getPlayablePosition(c, ia, v);
  std::vector<int> values;
  for(std::vector<vector>:: iterator _it = playable_pos.begin(); _it != playable_pos.end(); ++_it)
    {
      c.setCase(f, (*_it).x, (*_it).y);
      if (depth == MAX_DEPTH)
      {
        if (v.size() == 1)
          v.push_back(vector((*_it).x, (*_it).y));
        new_v = v;
      }
      else
        new_v.push_back(vector((*_it).x, (*_it).y ) );

      int value = min_max(c, depth - 1, !ia, id, alpha, beta, new_v);
      values.push_back(value);
      
      if (ia == true && value >= alpha)
        alpha = value;
      if (ia == false && value <= beta)
       beta = value;
      if (alpha >= beta)
      {
        c = d;
        global++;
        break;
      }

      c = d;
      if (depth == MAX_DEPTH)
      {
          first_move[id] = value;
          id++;
      }
    }
  std::vector<int>::iterator n;
  if (ia == true)
    n = std::max_element(values.begin(), values.end());
  else
    n = std::min_element(values.begin(), values.end());
  return *n;
}

int  Ai::eval(Board &b, bool ia, int depth, bool win)
{
  if (win == true && ia == true)
    return (1000 /*- (-depth) */);
  if (win == true && ia == false)
    return (-1000 /*- (-depth)*/);
  else if (depth == 0)
  {
    std::vector<int> num = count_aligned(b,ia);
    int sum = 0;
    for(int count = 0; count < num.size();count++)
      sum += num[count];
    if (ia == true)
      return (sum);
    else
      return (sum * -1);
  }
  else
    return 1;
}

std::vector<vector> Ai::return_aligned(Board &b, bool ia)
{
  std::vector<vector> combo;
  char f = (ia) ? 'w' : 'b';
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
        if (count > 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y));
          if ( (x - (count + 1) ) >= 0)
          {
          if (b.getCase(x - (count + 1), y) == NONE)  
            combo.push_back(vector(x - count, y));
          }
        }
        if (count == 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y));        
          if ( (x - (count + 1) ) >= 0)
          {
          if (b.getCase(x - (count + 1), y) == NONE)  
            combo.push_back(vector(x - count, y));
          }
        }
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
        if (count > 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x,y - 1));
          if ( (y - (count + 1) ) >= 0)
          {
          if (b.getCase(x, y - (count + 1)) == NONE)            
            combo.push_back(vector(x,y - count));
          }
        }  
        
        if (count == 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x,y - 1));
          if ( (y - (count + 1) ) >= 0)
          {
          if (b.getCase(x, y - (count + 1)) == NONE)  
            combo.push_back(vector(x,y - count));
          }
        }
        count = 0;
      }
    }
  }

  count = 0;
  t = 15;
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
        if (count > 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y - 1));
          if (x - (count + 1) >= 0 && y - (count + 1) >= 0)
          {
            if (b.getCase(x - (count + 1), y - (count + 1)) == NONE)
            combo.push_back(vector(x - count ,y - count));
          }
        }
        if (count == 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y - 1));
          if (x - (count + 1) >= 0 && y - (count + 1) >= 0)
          {
          if (b.getCase(x - (count + 1), y - (count + 1)) == NONE)
            combo.push_back(vector(x - count ,y - count ));
          }
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
        if (count > 3)
         {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y - 1));
          if (x - (count + 1) >= 0 && y - (count + 1) >= 0)          
          {
          if (b.getCase(x - (count + 1), y - (count + 1)) == NONE)
            combo.push_back(vector(x - count ,y - count));
          }
         }
         if (count == 3)
         {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y - 1));
          if (x - (count + 1) >= 0 && y - (count + 1) >= 0)
          {          
          if (b.getCase(x - (count + 1), y - (count + 1)) == NONE)
            combo.push_back(vector(x - count ,y - count));
          }
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
        if (count > 3)
          {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y + 1));
          if (x - (count + 1) >= 0 && y + (count + 1) <= 18)          
          {
            if (b.getCase(x - (count + 1), y + (count + 1)))            
              combo.push_back(vector(x - count, y + count));
          }
          }
        if (count == 3)
          {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y + 1));
           if (x - (count + 1) >= 0 && y + (count + 1) <= 18)          
            {
            if (b.getCase(x - (count + 1), y + (count + 1)))            
              combo.push_back(vector(x - count, y + count));
            }
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
        if (count > 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y + 1));
          if (x - (count + 1) >= 0 && y + (count + 1) <= 18)
          {          
            if (b.getCase(x - (count + 1), y + (count + 1)))                      
              combo.push_back(vector(x - count, y + count));
          }
        }
        if (count == 3)
        {
          if (b.getCase(x,y) == NONE)
            combo.push_back(vector(x - 1,y + 1));
          if (x - (count + 1) >= 0 && y + (count + 1) <= 18)          
          {
          if (b.getCase(x - (count + 1), y + (count + 1)))                      
            combo.push_back(vector(x - count, y + count));
          }
        }        
        count = 0;
      }
      x++;
      y--;
    }
    t++;
  }

  if (combo.size() > 0)
    return (combo);
}

std::vector<int> Ai::count_aligned(Board &b, bool ia)
{
  std::vector<int> combo;
  char f = (ia) ? 'w' : 'b';
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
          combo.push_back(5);
          return combo;
        }
        if (count > COUNT)
          combo.push_back(count);
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
          combo.push_back(5);
          return combo;
        }
        if (count > COUNT)
          combo.push_back(count);
        count = 0;
      }
    }
  }

  count = 0;
  t = 15;
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
        if (count >= 5)
          {
            combo.push_back(5);
            return combo;
          }
        if (count > COUNT)
            combo.push_back(count);
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
            combo.push_back(5);
            return combo;
          }
        if (count > COUNT)
          combo.push_back(count);
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
            combo.push_back(5);
            return combo;
          }
        if (count > COUNT)
            combo.push_back(count);
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
          combo.push_back(5);
          return combo;
        }
        if (count > COUNT)
          combo.push_back(count);
        count = 0;
      }
      x++;
      y--;
    }
    t++;
  }
  if (combo.size() > 0)
    return (combo);
}

bool Ai::check_win(Board &b, bool ia)
{
  std::vector<int> combo;
  char f = (ia) ? 'w' : 'b';
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
          return true;
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
          return true;
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
            return true;
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
            return true;
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
            return true;
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
          return true;
        count = 0;
      }
      x++;
      y--;
    }
    t++;
  }
  return (false);
}

bool Ai::checkSurrounding(Board &b, char color)
{
  std::vector<int> combo;
  char f = color;
  char e;
  int _count;
  int y;
  int x;
  int t;
  _count = 0;
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
                  if (b.getCase(x,y) == f)
                    _count++;
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
                  if (b.getCase(x,y) == f)
                    _count++;
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
                  if (b.getCase(x,y) == f)
                    _count++;
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
                  if (b.getCase(x,y) == f)
                    _count++;
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
                  if (b.getCase(x,y) == f)
                    _count++;
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
                  if (b.getCase(x,y) == f)
                    _count++;
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
  if (_count >  0)
      return true;
  return (false);
}