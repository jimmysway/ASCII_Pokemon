#include "Point2D.h"
#include <iostream>
#include <cmath>

using namespace std;


Point2D::Point2D()
{
  double x = 0.0;
  double y = 0.0;
}

Point2D::Point2D(double in_x, double in_y)
{
  x = in_x;
  y = in_y;
}

Point2D operator+(Point2D p1, Vector2D v1)
{
    Point2D nPoint = Point2D();
    nPoint.x = p1.x + v1.x;
    nPoint.y = p1.y + v1.y;

    return nPoint;
}

ostream& operator<<(ostream& out, Point2D p1)
{

    out << "(" << p1.x << "," << p1.y << " )";

    return out;
}

Vector2D operator-(Point2D p1, Point2D p2)
{
  Vector2D nVector = Vector2D();
  nVector.x = p1.x - p2.x;
  nVector.y = p1.y - p2.y;

  return nVector;
}

double GetDistanceBetween(Point2D p1, Point2D p2)
{
  double xval = pow((p2.x - p1.x), 2);
  double yval = pow((p2.y - p2.y), 2);
  double distance = sqrt(xval + yval);

  return distance;
}
