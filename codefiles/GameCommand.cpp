#include "GameCommand.h"


using namespace std;

void DoMoveCommand(Model & model, int trainer_id, Point2D p1)
{
  Trainer *T = model.GetTrainerPtr(trainer_id);
  T -> StartMoving(p1);

  cout << "Moving " << T -> GetName() << " to " << p1 << endl;
}
void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id)
{
  Trainer* T = model.GetTrainerPtr(trainer_id);
  PokemonCenter* C = model.GetPokemonCenterPtr(center_id);

  T -> StartMovingToCenter(C);

  cout << "Moving " << T -> GetName() << " to " << C -> GetId() << endl;
}
void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id)
{
  Trainer* T = model.GetTrainerPtr(trainer_id);
  PokemonGym* G = model.GetPokemonGymPtr(gym_id);
  T -> StartMovingToGym(G);

  cout << "Moving " << T -> GetName() << " to " << G -> GetId() << endl;
}

void DoStopCommand(Model & model, int trainer_id)
{
  Trainer* T = model.GetTrainerPtr(trainer_id);

  T -> Stop();

  cout << "Stopping " << T -> GetName() << endl;
}

void DoBattleCommand(Model & model, int trainer_id, unsigned int battles)
{
  Trainer* T = model.GetTrainerPtr(trainer_id);

  T -> StartBattling(battles);
  cout << T->GetName() << " is battling" << endl;
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int_potions_needed)
{
  Trainer* T = model.GetTrainerPtr(trainer_id);

  T -> StartRecoveringHealth(int_potions_needed);
  cout <<"Recovering "<< T->GetName() << "'s Pokemon's health" << endl;
}

void DoAdvanceCommand(Model& model, View& view)
{
	model.Update();
	model.ShowStatus();
	cout << "Advancing one tick..." << endl;
}

void DoRunCommand(Model& model, View& view)
{
	int i = 0;
	cout << "Advancing to next event..." << endl;
	while (model.Update() != true && i < 5)
	{
		i++;
	}
}

void DoNewCommand(Model& model, char type, int in_id, int x, int y)
{
	if (cin.fail() || in_id == 0 || in_id > 9 || x < 0 || y < 0)
	{
		cout << "Please enter a valid type, ID number, or coordinates! (ID number has to be and integer less than 10)";
	}

	char returntype;
		switch (type) {
		case 'c':
			returntype = 'c';
			model.NewCommand(returntype, in_id, x, y);
			break;
		case 'g':
			returntype = 'g';
			model.NewCommand(returntype, in_id, x, y);
			break;
		case 't':
			returntype = 't';
			model.NewCommand(returntype, in_id, x, y);
			break;
		case 'w':
			returntype = 'w';
			model.NewCommand(returntype, in_id, x, y);
			break;
		default:
			cout << "Please enter a valid input. ";
			break;

	}
	
}