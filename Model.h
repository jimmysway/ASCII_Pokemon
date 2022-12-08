#ifndef MODEL_H
#define MODEL_H

#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "GameObject.h"
#include "Trainer.h"
#include "View.h"
#include "Input_Handling.h"
#include "WildPokemon.h"
#include <list>
#include <iterator>



  class Model
  {
  private:
    int time;

    list <GameObject*> object_ptrs;
    list <Trainer*> trainer_ptrs;
    list <PokemonCenter*> center_ptrs;
    list <PokemonGym*> gym_ptrs;
    list <WildPokemon*> wildpokemon_ptrs;
    static Model* Master;
    Model();

  public:

    ~Model();
    Trainer * GetTrainerPtr(int id);
    PokemonCenter * GetPokemonCenterPtr(int id);
    PokemonGym * GetPokemonGymPtr(int id);
    bool Update();
    void Display(View& view);
    void ShowStatus();
    void NewCommand(char type, int id, int x, int y);
    static Model *getMaster();
  };


#endif
