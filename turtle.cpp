#include "turtle.hpp"
#include <SDL.h>
#include <boost/coroutine2/all.hpp>
#include <cmath>
#include <tuple>
#include <vector>

class Turtle
{
public:
  Turtle();
  ~Turtle();
  static Turtle &instance();
  void back(float);
  void background(Color);
  void clearScreen();
  void draw();
  void forward(float);
  void hideTurtle();
  void left(float);
  void penColor(Color);
  void penDown();
  void penUp();
  void right(float);
  void setX(float);
  void setXY(float, float);
  void setY(float);
  void showTurtle();
private:
  enum { Width = 1280, Height = 720 };
  float x = Width / 2;
  float y = Height / 2;
  float direction = -90;
  Color pen = Color::Black;
  Color bg = Color::White;
  bool isVisible = true;
  bool isPenDown = true;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  void yeld();
  void move(float x1, float y1, float x2, float y2);
  enum Command { Draw, Clear, Yeld, Drain };
  typedef boost::coroutines2::coroutine<Command> coro_t;
  coro_t::push_type sink;
  std::vector<std::tuple<float, float, float, float, Color> > drawing;
  void loop(coro_t::pull_type &p);
  void setRenderDrawColor(Color);
};

void back(float value)
{
  Turtle::instance().back(value);
}
void background(Color value)
{
  Turtle::instance().background(value);
}
void clearScreen()
{
  Turtle::instance().clearScreen();
}
void draw()
{
  Turtle::instance().draw();
}
void forward(float value)
{
  Turtle::instance().forward(value);
}
void hideTurtle()
{
  Turtle::instance().hideTurtle();
}
void left(float value)
{
  Turtle::instance().left(value);
}
void penColor(Color value)
{
  Turtle::instance().penColor(value);
}
void penDown()
{
  Turtle::instance().penDown();
}
void penUp()
{
  Turtle::instance().penUp();
}
void right(float value)
{
  Turtle::instance().right(value);
}
void setX(float value)
{
  Turtle::instance().setX(value);
}
void setXY(float x, float y)
{
  Turtle::instance().setXY(x, y);
}
void setY(float value)
{
  Turtle::instance().setY(value);
}
void showTurtle()
{
  Turtle::instance().showTurtle();
}
Turtle &Turtle::instance()
{
  static Turtle turtle;
  return turtle;
}

const auto Pi = 3.1415926f;

Turtle::Turtle():
  sink([this](coro_t::pull_type &p)
       {
         loop(p);
       })
{
}
Turtle::~Turtle()
{
  while (sink)
  {
    sink(Drain);
  }
}

void Turtle::back(float value)
{
  forward(-value);
}
void Turtle::background(Color value)
{
  bg = value;
  yeld();
}
void Turtle::clearScreen()
{
  drawing.clear();
  if (sink)
    sink(Clear);
  else
    throw std::runtime_error("sink");
}
void Turtle::move(float x1, float y1, float x2, float y2)
{
  if (sink)
  {
    if (isPenDown)
      drawing.push_back(std::make_tuple(x1, y1, x2, y2, pen));
    sink(Draw);
  }
  else
    throw std::runtime_error("sink");
}
void Turtle::draw()
{
  drawing.clear();
  x = Width / 2;
  y = Height / 2;
  direction = -90;
  pen = Color::Black;
  bg = Color::White;
  isVisible = true;
  isPenDown = true;
  if (sink)
    sink(Clear);
  else
    throw std::runtime_error("sink");
}
void Turtle::forward(float value)
{
  if (value == 0.0f)
    return;
  auto d = direction;
  if (value < 0)
  {
    d = d + 180;
    value *= -1;
  }
  auto dx = cos(d * Pi / 180.0f);
  auto dy = sin(d * Pi / 180.0f);
  auto newX = x + cos(d * Pi / 180.0f) * value;
  auto newY = y + sin(d * Pi / 180.0f) * value;
  if (isVisible)
    while ((newX - x) * dx >= 0 && (newY - y) * dy >= 0)
    {
      move(x, y, x + dx, y + dy);
      x += dx;
      y += dy;
    }
  move(x, y, newX, newY);
  x = newX;
  y = newY;
}
void Turtle::hideTurtle()
{
  isVisible = false;
  yeld();
}
void Turtle::left(float value)
{
  auto newDirection = direction - value;
  if (isVisible)
    while (value * (newDirection - direction) < 0)
    {
      yeld();
      if (value > 0)
        direction -= 1.0f;
      else
        direction += 1.0f;
    }
  direction = newDirection;
  while (direction < 0)
    direction += 360;
  while (direction >= 360)
    direction -= 360;
}
void Turtle::penColor(Color value)
{
  pen = value;
  yeld();
}
void Turtle::penDown()
{
  isPenDown = true;
  yeld();
}
void Turtle::penUp()
{
  isPenDown = false;
  yeld();
}
void Turtle::right(float value)
{
  left(-value);
}
void Turtle::setX(float value)
{
  setXY(value, y);
}
void Turtle::setXY(float newX, float newY)
{
  auto distance = hypot(newX - x, newY - y);
  auto dx = (newX - x) / distance;
  auto dy = (newY - y) / distance;
  if (dx == 0 && dy == 0)
    return;
  if (isVisible)
    while ((newX - x) * dx >= 0 && (newY - y) * dy >= 0)
    {
      move(x, y, x + dx, y + dy);
      x += dx * 0.5f;
      y += dy * 0.5f;
    }
  move(x, y, newX, newY);
  x = newX;
  y = newY;

}
void Turtle::setY(float value)
{
  setXY(x, value);
}
void Turtle::showTurtle()
{
  isVisible = true;
  yeld();
}
void Turtle::yeld()
{
  if (sink)
    sink(Yeld);
  else
    throw std::runtime_error("sink");
}

void Turtle::loop(coro_t::pull_type &p)
{
  SDL_Window *window;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window, &renderer);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

  SDL_SetWindowPosition(window, 65, 126);
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);
  SDL_Event e;
  bool done = false;
  auto currentTick = SDL_GetTicks();
  while (!done)
  {
    if (isVisible)
    {
      SDL_Delay(1000 / 120);
    }
    if (!isVisible || SDL_GetTicks() > currentTick)
    {
      for (int i = 0; i < 10; ++i)
        if (p)
        {
          switch (p.get())
          {
          case Clear:
            SDL_SetRenderTarget(renderer, texture);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            break;
          default:
            break;
          }
          p();
        }
      SDL_SetRenderTarget(renderer, texture);
      for (const auto &i: drawing)
      {
        setRenderDrawColor(std::get<4>(i));
        SDL_RenderDrawLine(renderer,
                           std::get<0>(i),
                           std::get<1>(i),
                           std::get<2>(i),
                           std::get<3>(i));
      }
      SDL_SetRenderTarget(renderer, nullptr);
      drawing.clear();
    }
    if (SDL_GetTicks() > currentTick)
    {
      while (SDL_PollEvent(&e))
      {
        if (e.type == SDL_QUIT)
          done = true;
        break;
      }
      if (SDL_GetTicks() > currentTick)
        currentTick += 1000 / 60;
      setRenderDrawColor(bg);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, nullptr, nullptr);
      if (isVisible)
      {
        setRenderDrawColor(pen);
        auto x1 = x + 20 * cos((direction - 120.0f) * Pi / 180.0f);
        auto y1 = y + 20 * sin((direction - 120.0f) * Pi / 180.0f);
        auto x2 = x + 20 * cos((direction) * Pi / 180.0f);
        auto y2 = y + 20 * sin((direction) * Pi / 180.0f);
        auto x3 = x + 20 * cos((direction + 120.0f) * Pi / 180.0f);
        auto y3 = y + 20 * sin((direction + 120.0f) * Pi / 180.0f);
        SDL_RenderDrawLine(renderer, x, y, x1, y1);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
        SDL_RenderDrawLine(renderer, x3, y3, x, y);
      }
      SDL_RenderPresent(renderer);
    }
  }
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Turtle::setRenderDrawColor(Color value)
{
  switch (value)
  {
  case Color::Black:
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    break;
  case Color::White:
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    break;
  case Color::Green:
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    break;
  case Color::Violet:
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
    break;
  case Color::Orange:
    SDL_SetRenderDrawColor(renderer, 0xff, 0x80, 0x00, 0xff);
    break;
  case Color::Blue:
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
    break;
  }
}
