#pragma once

enum class Color { Black, White, Green, Violet, Orange, Blue };

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

inline void b(float value) { back(value); }
inline void bg(Color value) { background(value); }
inline void cs() { clearScreen(); }
inline void f(float value) { forward(value); }
inline void ht() { hideTurtle(); }
inline void l(float value) { left(value); }
inline void pc(Color value) { penColor(value); }
inline void pd() { penDown(); }
inline void pu() { penUp(); }
inline void r(float value) { right(value); }
inline void st() { showTurtle(); }
