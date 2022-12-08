#include "Vector2D.h"
#include <iostream>

using namespace std;


Vector2D::Vector2D()
{
  x = 0.0;
  y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y)
{
  x = in_x;
  y = in_y;
}

Vector2D operator*(Vector2D v1, double d)
{
    Vector2D nVector;

    nVector.x = v1.x * d;
    nVector.y = v1.y * d;

    return nVector;
}

Vector2D operator/(Vector2D v1, double d)
{
   if(d==0)
   {
       v1.x = v1.x;
       v1.y = v1.y;

       return v1;
   }
    else
    {
        Vector2D nVector;
        nVector.x = v1.x / d;
        nVector.y = v1.y / d;

        return nVector;
    }

}

ostream& operator<<(ostream& output, Vector2D v1)
{
    output <<  "(" << v1.x << ", " << v1.y << ")";
    return output;
}
