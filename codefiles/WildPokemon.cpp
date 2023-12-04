#include "WildPokemon.h"
#include "GameObject.h"
#include "Trainer.h"
#include <cstdlib>
#include "Model.h"
#include <iostream>

using namespace std;
WildPokemon::WildPokemon()
{
 
}

WildPokemon::WildPokemon(double in_speed, string in_name, double in_attack, double in_health, bool in_variant, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, 'W')
{
 this->display_code = 'W';
 this->in_combat = false;
 this->speed = in_speed;
 this->name = in_name;
 this->attack = in_attack;
 this->variant = in_variant;
 this->health = in_health;
 this->id_num = in_id;
 this->location = in_loc;
 this->state = IN_ENVIRONMENT;

 cout << "Pokemon constructed " << endl;
}
void WildPokemon::SetupDestination(Point2D dest)
{
    destination = dest;

    delta = (dest - location) * (speed / GetDistanceBetween(dest, location));
}
double WildPokemon::getDistancetoTrainer(Trainer* Trainer)
{
   double distance = GetDistanceBetween(this->GetLocation(), Trainer->GetLocation());
   return distance;
}

void WildPokemon::follow(Trainer* t)
{
    Point2D dest = t->GetLocation();

        this->state = IN_TRAINER;

        if (this->location.x == dest.x && this->location.y == dest.y)
        {
            cout << this->name << " " << this->id_num << ": has approached " << t->GetName() << endl;
        }
        else
        {
            cout << "A wild pokemon follows." << endl;
            SetupDestination(dest);
        }

}
string WildPokemon::get_name()
{
  return this->name;
}

bool WildPokemon::get_variant()
{
  return this->variant;
}

double WildPokemon::get_attack()
{
  return this->attack;
}

double WildPokemon::get_health()
{
  return this->health;
}

bool WildPokemon::get_in_combat()
{
  return this->in_combat;
}

bool WildPokemon::Update()
{
    Model* M = Model::getMaster();
    double distance1 = WildPokemon::getDistancetoTrainer(M->GetTrainerPtr(1));
    double distance2 = WildPokemon::getDistancetoTrainer(M->GetTrainerPtr(2));

    if (distance1 < 5)
    {
        this->state = IN_TRAINER;
        WildPokemon::follow(M->GetTrainerPtr(1));

    }
    else if (distance2 < 5)
    {
        this->state = IN_TRAINER;
        WildPokemon::follow(M->GetTrainerPtr(2));
    }
    else
    {
        this->state = IN_ENVIRONMENT;
    }
  bool returnval = false;
  switch(this->state)
{
  case IN_ENVIRONMENT:
  returnval = false;
  break;

  case DEAD:
  returnval = true;
  break;

  case IN_TRAINER:
      WildPokemon::UpdateLocation();
  WildPokemon::ShowStatus();
  returnval = true;
  break;

  default:
  break;

  return returnval;
}

}

bool WildPokemon::UpdateLocation()
{
    double xval = fabs(this->destination.x - this->location.x);
    double yval = fabs(this->destination.y - this->location.y);
    if (xval <= fabs(delta.x) && yval <= fabs(delta.y))
    {
        this->location = destination;
        cout << "arrived." << endl;
        return true;
    }
    else
    {
        this->location.x += delta.x;
        this->location.y += delta.y;
        cout << "moved. " << endl;
        return false;
    }
    if (this->location.x == destination.x && this->location.y == destination.y)
    {
        cout << this->display_code << " " << this->id_num << ": " << "Wild Pokemon has approached!" << endl;
    }
    else
    {
        cout << this->display_code << " " << this->id_num << ": " << "Wild Pokemon step..." << endl;
    }
}


bool WildPokemon::IsAlive()
{
  bool returnval = true;
  if(this->health <= 0)
  {
    this->state = DEAD;
    returnval = false;
  }
  return returnval;
}

bool WildPokemon::ShouldBeVisible()
{
    bool returnval = false;
    if (this->state != DEAD)
    {
        returnval = false;
    }
    else {
        returnval = true;
    }
    return returnval;
}

void WildPokemon::ShowStatus()
{
  GameObject::ShowStatus();

  switch(state)
  {
    case IN_ENVIRONMENT:
    cout << "This Wild Pokemon " << this->GetId() << " " << this -> get_name() << "is chilling. " << endl;
    cout << "Health: " << this->get_health() << endl;
    break;

    case DEAD:
    cout << "This Wild Pokemon " << this->GetId() << " " << this -> get_name() << "dead. " << endl;

    break;

    case IN_TRAINER:
    cout << "This Wild Pokemon is following a trainer" << endl;
    break;
  }
}