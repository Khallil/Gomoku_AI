#include <SFML/Graphics.hpp>
#include "core.hpp"


int usage(const std::string &msg)
{
  std::cerr << msg << std::endl;
  return (-1);
}

int main()
{
    Core a;
    std::srand(std::time(0));
    if (a.run())
      return (0);
}
