#include "turtle.hpp"

void square(float value = 50)
{
  for (auto i = 0; i < 4; ++i)
  {
    forward(value);
    right(90);
  }
}

void triangle()
{
  for (auto i = 0; i < 3; ++i)
  {
    forward(50);
    right(90 + 30);
  }
}

void pentagon()
{
  for (auto i = 0; i < 5; ++i)
  {
    forward(50);
    right(72);
  }
}

void hexagon()
{
  for (auto i = 0; i < 6; ++i)
  {
    forward(50);
    right(60);
  }
}

void octagon()
{
  for (auto i = 0; i < 8; ++i)
  {
    forward(50);
    right(45);
  }
}

void circle()
{
  for (auto i = 0; i < 360; ++i)
  {
    forward(1);
    right(1);
  }
}

void house()
{
  square();
  forward(50);
  right(30);
  triangle();
}

void sunflower()
{
  for (auto i = 0; i < 18; ++i)
  {
    house();
    left(30);
    back(50);
    right(201);
  }
}

void orbit(float size, float angle)
{
  for(;;)
  {
    forward(size);
    right(angle);
  }
}

void orbit1()
{
  for(;;)
  {
    forward(50);
    right(120);
  }
}

void orbit2()
{
  for(;;)
  {
    forward(50);
    right(90);
  }
}

void orbit3()
{
  for(;;)
  {
    forward(50);
    right(72);
  }
}

void orbit4()
{
  for(;;)
  {
    forward(50);
    right(160);
  }
}

void orbit5()
{
  for(;;)
  {
    forward(50);
    right(144);
  }
}

void orbit6()
{
  for(;;)
  {
    forward(60);
    right(3);
  }
}

void jump(float value)
{
  forward(value);
  right(90);
  forward(value / 4);
  left(90);
}

void tower(float s = 40)
{
  for (auto i = 0; i < 4; ++i)
  {
    square(s);
    jump(s);
    s /= 2;
  }
  // square(20);
  // jump(20);
  // square(10);
  // jump(10);
  // square(5);
  // jump(5);
}

void pisa()
{
  right(10);
  tower(80);
}

void experiment1(float size, float angle)
{
  for (;;)
  {
    square(size);
    right(angle);
  }
}

void experiment2(float size, float angle)
{
  for (;;)
  {
    forward(size);
    right(angle);
    size += 3;
  }
}

void experiment3(float size, float angle)
{
  for (;;)
  {
    forward(size);
    right(angle);
    angle += 5;
  }
}

void experiment4(float size, float angle)
{
  for (;;)
  {
    square(size);
    right(angle);
    size += 3;
  }
}


int main()
{
  experiment4(10, 10);
  // experiment3(10, 5);
  // experiment2(1, 123);
  // experiment1(150, 20);
  // experiment1(40, 144);
  // orbit(90, 100);
  // pisa();
  // hideTurtle();
  
  // forward(50);
  // right(90);
  // forward(50);
  // right(90);
  // forward(50);
  // right(90);
  // forward(50);
  // right(90);
  
  // setY(200);

  // penColor(Color::Green);
  // background(Color::Blue);
  
  // forward(40);
  // back(20);
  // right(90);
  // left(180);
  // forward(5);
  // forward(20);
  // left(90);
  // forward(20);
  // back(40);

  // draw();
  // forward(40);
  // left(45);
  // back(20);
  // right(90);
  // forward(20);
  // left(45);
  // back(40);

  // penUp();
  // right(90);
  // forward(20);
  // left(90);
  // penDown();

  // forward(40);
  // back(40);
  // right(45);
  // forward(40);
  // forward(16);
  // left(45);
  // back(40);

  // penUp();
  // right(90);
  // forward(20);
  // left(90);
  // penDown();

  // forward(40);
  // right(90);
  // forward(30);
  // right(90);
  // forward(20);
  // right(90);
  // forward(30);
}
