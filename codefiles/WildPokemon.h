#pragma once
#include "Trainer.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <string.h>

using namespace std;

enum PokemonState {
  IN_ENVIRONMENT = 0,
  DEAD = 1,
  IN_TRAINER = 2,
};

class WildPokemon : public GameObject
{
private:
	Vector2D delta;
	Point2D destination;
protected:
  double attack;
  double health;
  double speed;
  bool variant;
  bool in_combat;
  string name;
  void SetupDestination(Point2D);
  bool UpdateLocation();

public:
  void follow(Trainer* current_trainer);
  WildPokemon();
  WildPokemon(double speed, string name, double attack, double health, bool variant, int id, Point2D in_loc);
  bool get_variant();
  double get_attack();
  double get_health();
  double getDistancetoTrainer(Trainer*);
  bool get_in_combat();
  bool Update();
  void ShowStatus();
  bool IsAlive();
  bool ShouldBeVisible();
  string get_name();
};
