#include "turtle.hpp"
#include <exception>
#include <iostream>

int main()
{
  try
  {
    float a = -1;
    for(;;)
    {
      forward(1);
      left(a);
      a += 0.01;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
