#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Point2D.h"


  class GameObject
  {
  public:
    GameObject();
    GameObject(char in_code);
    GameObject(Point2D in_loc, int in_id, char in_code);
    Point2D GetLocation();
    int GetId();
    virtual void ShowStatus();
    virtual bool Update() = 0;
    virtual bool ShouldBeVisible() = 0;
    char GetState();
    void DrawSelf(char *ptr);

  protected:
    Point2D location;
    int id_num;
    char display_code;
    char state;
  };


#endif
