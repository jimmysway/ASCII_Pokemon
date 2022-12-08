#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"


  class Building : public GameObject
  {
  public:
    Building();
    Building(char in_code, int in_id, Point2D in_loc);
    void AddOneTrainer();
    void RemoveOneTrainer();
    void ShowStatus();
    bool ShouldBeVisible();
  private:
    unsigned int trainer_count = 0;
  };


#endif
