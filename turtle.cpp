#include "turtle.hpp"
#include <SDL2/SDL.h>
#include <boost/coroutine2/all.hpp>
#include <cmath>
#include <iostream>
#include <tuple>

class Turtle
{
public:
  Turtle();
  static Turtle &instance();
  void forward(float);
  void left(float);
  void right(float);
  void backward(float);
private:
  float x = 1280 / 2;
  float y = 720 / 2;
  float direction = -90;
  void yeld();
  void draw(float x1, float y1, float x2, float y2);
  typedef boost::coroutines2::coroutine<std::tuple<float, float, float, float> > coro_t;
  coro_t::push_type sink;
  void loop(coro_t::pull_type &p);
};

void forward(float value)
{
  Turtle::instance().forward(value);
}

void left(float value)
{
  Turtle::instance().left(value);
}

void right(float value)
{
  Turtle::instance().right(value);
}

void backward(float value)
{
  Turtle::instance().backward(value);
}

Turtle &Turtle::instance()
{
  static Turtle turtle;
  return turtle;
}

const auto Pi = 3.1415926f;

void Turtle::forward(float value)
{
  if (value == 0.0f)
    return;
  auto dx = cos(direction * Pi / 180.0f);
  auto dy = sin(direction * Pi / 180.0f);
  auto newX = x + cos(direction * Pi / 180.0f) * value;
  auto newY = y + sin(direction * Pi / 180.0f) * value;
  while ((newX - x) * dx >= 0 && (newY - y) * dy >= 0)
  {
    draw(x, y, x + dx, y + dy);
    x += dx * 0.1f;
    y += dy * 0.1f;
  }
  x = newX;
  y = newY;
}

Turtle::Turtle():
  sink([this](coro_t::pull_type &p)
       {
         loop(p);
       })
{
}


void Turtle::left(float value)
{
  auto newDirection = direction - value;
  while (value * (newDirection - direction) > 0)
  {
    yeld();
    direction += 1.0f;
  }
  direction = newDirection;
}

void Turtle::right(float value)
{
  left(-value);
}

void Turtle::backward(float value)
{
  forward(-value);
}

void Turtle::yeld()
{
  if (sink)
    sink(std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f));
  else
    throw std::runtime_error("sink");
}

void Turtle::draw(float x1, float y1, float x2, float y2)
{
  if (sink)
    sink(std::make_tuple(x1, y1, x2, y2));
  else
    throw std::runtime_error("sink");
}

void Turtle::loop(coro_t::pull_type &p)
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");
  SDL_CreateWindowAndRenderer(1280, 720, SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_SetWindowPosition(window, 65, 126);
  SDL_Event e;
  bool done = false;
  std::vector<std::tuple<float, float, float, float> > drawing;
  while (!done && p)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        done = true;
      break;
    }
    drawing.push_back(p.get());
    p();
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    for (const auto &i: drawing)
    {
      SDL_RenderDrawLine(renderer,
                         std::get<0>(i),
                         std::get<1>(i),
                         std::get<2>(i),
                         std::get<3>(i));
    }
    SDL_RenderPresent(renderer);
  }
  while (!done)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        done = true;
      break;
    }
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    for (const auto &i: drawing)
    {
      SDL_RenderDrawLine(renderer,
                         std::get<0>(i),
                         std::get<1>(i),
                         std::get<2>(i),
                         std::get<3>(i));
    }
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
