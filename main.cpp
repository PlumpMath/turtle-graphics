#include "turtle.hpp"
#include <exception>
#include <iostream>

int main()
{
  try
  {
    float a = -90;
    penColor(Color::Orange);
    for(;;)
    {
      forward(10);
      left(a);
      a += 0.1;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
