#include "PokemonCenter.h"
#include "Building.h"
#include <iostream>

using namespace std;


PokemonCenter::~PokemonCenter()
{
  cout << "PokemonCenter destructed." << endl;
}

PokemonCenter::PokemonCenter()
{
  this -> display_code = 'C';
  this -> potion_capacity = 100;
  this -> num_potions_remaining = potion_capacity;
  this -> pokedollar_cost_per_potion = 5;
  this -> state = POTIONS_AVAILABLE;

  cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
{
  this -> id_num = in_id;
  this -> location = in_loc;
  this -> pokedollar_cost_per_potion = potion_cost;
  this -> potion_capacity = potion_cap;
  this -> num_potions_remaining = potion_capacity;
  this -> state = POTIONS_AVAILABLE;

  cout << "PokemonCenter constructed" << endl;

}

bool PokemonCenter::HasPotions()
{
  if(this -> num_potions_remaining > 0)
  {
    return true;
  } else {
    return false;
  }
}

unsigned int PokemonCenter::GetNumPotionRemaining()
{
  return this -> num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget)
{
  int potionsum = potion*(this -> pokedollar_cost_per_potion);
  if (budget >= potionsum)
  {
    return true;
  } else {
    return false;
  }
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion)
{
  double cost = potion* (this -> pokedollar_cost_per_potion);
  return cost;
}

unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed)
{
  if (this -> num_potions_remaining >= potion_needed)
  {
    this -> num_potions_remaining = this -> num_potions_remaining - potion_needed;
    return potion_needed;
  } else {
    this -> num_potions_remaining = 0;
    return this -> num_potions_remaining;
  }
}

bool PokemonCenter::Update()
{
  bool returnval;

  if (this -> num_potions_remaining <= 0)
  {
    this -> state = NO_POTIONS_AVAILABLE;
    this -> display_code = 'c';
    cout << "PokemonCenter " << this -> id_num << " has ranout of potions." << endl;

    returnval = true;
  } else {
    returnval = false;
  }
  return returnval;
}

void PokemonCenter::ShowStatus()
{
  cout << "Pokemon Center Status: ";
  Building::ShowStatus();
  cout << "PokeDollars per potion: " << this -> pokedollar_cost_per_potion << endl;
  cout << "has " << this -> num_potions_remaining << " potion(s) remaining." << endl;
}
