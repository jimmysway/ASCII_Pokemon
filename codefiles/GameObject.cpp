#include "GameObject.h"
#include "Point2D.h"
#include <iostream>

using namespace std;


bool GameObject::Update()
{
    return false; //should never be used, as each object has its own "update" from hereon out (manual)
}

void GameObject::DrawSelf(char* pointer)
{
  *pointer = display_code;

  char chnum = static_cast<char>(id_num);

  *(pointer + 1) = '0' + chnum;
}

GameObject::GameObject()
{

}

GameObject::GameObject(char in_code)
{
  display_code = in_code;
  id_num = 1;
  state = '0';
  location = Point2D();
  cout << "GameObject constructed" << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
  display_code = in_code;
  id_num = in_id;
  state = '0';
  location = in_loc;
  cout << "GameObject constructed" << endl;
}

Point2D GameObject::GetLocation()
{
  return location;
}

int GameObject::GetId()
{
  return id_num;
}

char GameObject::GetState()
{
  return state;
}

void GameObject::ShowStatus()
{
  cout << display_code << id_num << " " << "at" << " " << location.x << " " << location.y << endl;
}
