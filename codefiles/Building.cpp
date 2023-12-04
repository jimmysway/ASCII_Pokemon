#include "Building.h"
#include "GameObject.h"
#include <iostream>

using namespace std;


Building::Building()
{
  trainer_count = 0;
  display_code = 'B';
}

Building::Building(char in_code, int in_id, Point2D in_loc)
{
  display_code = in_code;
  id_num = in_id;
  location = in_loc;

  cout << "Building constructed" << endl;
}

void Building::AddOneTrainer()
{
  trainer_count = trainer_count++;
}

void Building::RemoveOneTrainer()
{
  trainer_count = trainer_count--;
}

void Building::ShowStatus()
{
  cout << this -> display_code << this ->  id_num << " " << "located at" << " " << this -> location << endl;
  cout << this -> trainer_count << " trainers is/are in this building" << endl;
}

bool Building::ShouldBeVisible()
{
  return true;
}

