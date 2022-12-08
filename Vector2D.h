#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <cstring>
#include <time.h>
#include <iostream>
#include <cstdlib>

using namespace std;



  class Point2D;

  class Vector2D
  {
  public:
    double x;
    double y;

    Vector2D();
    Vector2D(double in_x, double in_y);

  };

  Vector2D operator*(Vector2D v1, double d);

  Vector2D operator/(Vector2D v1, double d);

  ostream& operator<<(ostream& output, Vector2D v1);




#endif
