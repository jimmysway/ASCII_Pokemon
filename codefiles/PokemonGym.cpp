#include "Building.h"
#include "PokemonGym.h"
#include "GameObject.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



PokemonGym::~PokemonGym()
{
  cout << "PokemonGym destructed." << endl;
}

PokemonGym::PokemonGym()
{
  display_code = 'G';
  state = NOT_DEFEATED;
  max_number_of_battles = 10;
  num_battle_remaining = max_number_of_battles;
  health_cost_per_battle = 1;
  PokeDollar_cost_per_battle = 1.0;
  experience_per_battle = 2;

  cout << "PokemonGym default constructed" << endl;

}

PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost,
   unsigned int exp_per_battle, int in_id, Point2D in_loc)
{
    display_code = 'G';
    state = NOT_DEFEATED;
  id_num = in_id;
  max_number_of_battles = max_battle;
  num_battle_remaining = max_number_of_battles;
  health_cost_per_battle = health_loss;
  experience_per_battle = exp_per_battle;
  PokeDollar_cost_per_battle = PokeDollar_cost;
  location = in_loc;

  cout << "PokemonGym constructed" << endl;

}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty)
{
  double value = battle_qty*PokeDollar_cost_per_battle;
  return value;
}

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty)
{
  double value = battle_qty*health_cost_per_battle;
  return value;
}

unsigned int PokemonGym::GetNumBattlesRemaining()
{
  return num_battle_remaining;
}

bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health)
{
  double cost = battle_qty*PokeDollar_cost_per_battle;
  double healthcost = battle_qty*health_cost_per_battle;

  if (budget >= cost && health >= healthcost){
    return true;
  } else {
    return false;
  }

}

unsigned int PokemonGym::TrainPokemon(unsigned int battle_units)
{
  int experience;
  if (num_battle_remaining >= battle_units)
  {
    num_battle_remaining = num_battle_remaining - battle_units;
    experience = battle_units*experience_per_battle;
    return experience;
  } else {
    experience = num_battle_remaining*experience_per_battle;
    num_battle_remaining = 0;
    return experience;
  }
}

bool PokemonGym::Update()
{
  if (state == DEFEATED)
  {
    return false;
  }
  if(num_battle_remaining == 0)
  {
    state = DEFEATED;
    display_code = 'g';
    cout << display_code << " " << id_num << "has been beaten." << endl;

    return true;
  } else {
    return false;
  }

}
bool PokemonGym::passed()
{
    bool returnval = false;
  if(num_battle_remaining == 0)
  {
    returnval = true;
  } else {
    returnval = false;
  }
  cout << returnval << endl;
  return returnval;
}

void PokemonGym::ShowStatus()
{
  cout << "PokemonGymStatus: ";
  Building::ShowStatus();

  cout << "Max number of battles: " << max_number_of_battles << endl;
  cout << "Health cost per battle: " << health_cost_per_battle << endl;
  cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
  cout << "Experience per battle: " << experience_per_battle << endl;
  cout << num_battle_remaining << " battle(s) are remaining for this PokemonGym" << endl;
}