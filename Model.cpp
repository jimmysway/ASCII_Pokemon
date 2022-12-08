#include "Model.h"

using namespace std;


Model::Model()
{
	Master = this->Master; //singleton attempt
	this -> time = 0;

	Point2D t1 = Point2D(5,1);
	Point2D t2 = Point2D(10,1);
	Point2D c1 = Point2D(1,20);
	Point2D c2 = Point2D(10,20);
	Point2D g1 = Point2D(0,0);
	Point2D g2 = Point2D(5,5);
	Point2D w1 = Point2D(10, 12);
	Point2D w2 = Point2D(15, 5);

//std::string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
	Trainer* T1 = new Trainer("Ash", 1, 'T', 1, t1);
	Trainer* T2 = new Trainer("Misty", 2, 'T', 2, t2);
//(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
	PokemonCenter* C1 = new PokemonCenter(1, 1, 100, c1);
	PokemonCenter* C2 = new PokemonCenter(2, 2, 200, c2);
//unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc);
	PokemonGym* G1 = new PokemonGym(10, 1, 2.0, 3, 1, g1);
	PokemonGym* G2 = new PokemonGym(20, 5, 7.5, 4, 2, g2);
//  WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc);
	WildPokemon* W1 = new WildPokemon(20.0, "Mudkip", 2.0, 20.0, true, 1, w1);
	WildPokemon* W2 = new WildPokemon(10.0, "Froakie", 2.0, 20.0, true, 1, w2);

	this->trainer_ptrs.push_back(T1);
	this->trainer_ptrs.push_back(T2);

	this->center_ptrs.push_back(C1);
	this->center_ptrs.push_back(C2);

	this->gym_ptrs.push_back(G1);
	this->gym_ptrs.push_back(G2);

	this->wildpokemon_ptrs.push_back(W1);
	this->wildpokemon_ptrs.push_back(W2);

	this->object_ptrs.push_back(T1);
	this->object_ptrs.push_back(T2);
	this->object_ptrs.push_back(C1);
	this->object_ptrs.push_back(C2);
	this->object_ptrs.push_back(G1);
	this->object_ptrs.push_back(G2);
	this->object_ptrs.push_back(W1);
	this->object_ptrs.push_back(W2);

	cout << "Model default constructed" << endl;
}	

Model* Model::getMaster()
{
	if (!Master)
		Master = new Model;
	return Master;
}
Model::~Model()
{
	cout << "Model destructed" << endl;
}

Trainer* Model::GetTrainerPtr(int id)
{
	list <Trainer*>::iterator i;

	for (i = this->trainer_ptrs.begin(); i != this->trainer_ptrs.end(); i++)
	{
		if ((*i)->GetId() == id)
		{
			return (*i);
		}
	}
	return NULL;
}


PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
	list <PokemonCenter*>::iterator i;

	for (i = this->center_ptrs.begin(); i != this->center_ptrs.end(); i++)
	{
		if ((*i)->GetId() == id)
		{
			return (*i);
		}
	}
	return NULL;
}


PokemonGym * Model::GetPokemonGymPtr(int id)
{
	list <PokemonGym*>::iterator i;

	for (i = this->gym_ptrs.begin(); i != this->gym_ptrs.end(); i++)
	{
		if ((*i)->GetId() == id)
		{
			return (*i);
		}
	}
	return NULL;
}


bool Model::Update()
{

	bool win = false;
	bool lose = false;
	int gymtally = 0;
	int trainertally = 0;
	time ++;

	;

	for (list <PokemonGym*>::iterator i = this->gym_ptrs.begin(); i != this->gym_ptrs.end(); i++)
	{
		bool checkcond = (*i)->passed();
		if (checkcond == true)
		{
			gymtally = gymtally + 1;
		}
	}

;

	for (list <Trainer*>::iterator i = this->trainer_ptrs.begin(); i != this->trainer_ptrs.end(); i++)
	{
		if ((*i)->GetState() == FAINTED)
		{
			trainertally = trainertally + 1;
		}
	}

	if (trainertally == 2)
	{
		lose = true;
	}

	if (gymtally == 2)
	{
		win = true;
	}

	if (lose == true)
	{
		cout << "GAME OVER: You lose! All of your Trainers’ pokemon have fainted!" << endl;
		exit(0);
	}

	if (win == true)
	{
		cout << "GAME OVER: You win! All battles done!" << endl;
		exit(0);
	}

	bool returnval = 0;


	for (list <GameObject*>::iterator i = this->object_ptrs.begin(); i != this->object_ptrs.end() ;i++) //plot all objects for the display
	{
		(*i)->Update();
		if ((*i)->Update() == true)
		{
			returnval = true;
		} else {
			returnval = false;
		}
	}

	return returnval;
}
void Model::Display(View& view)
{
	cout << "time:" << this -> time << endl;
	view.Clear();
	list <GameObject*>::iterator i;
	for (i = this->object_ptrs.begin(); i != this->object_ptrs.end();i++) //plot all objects for the display
	{
		view.Plot(*i);
	}
	view.Draw();
}

void Model::ShowStatus()
{
	list <GameObject*>::iterator i;
	for (i = this->object_ptrs.begin(); i != this->object_ptrs.end();i++)
	{
		(*i)->ShowStatus();
	}
}

void Model::NewCommand(char type, int in_id, int x, int y)
{
	string trainername;
	int speed;
	Point2D newPoint(x, y);
	switch (type) {
	case 'c':
		for (list <PokemonCenter*>::iterator i = this->center_ptrs.begin(); i != this->center_ptrs.end(); i++)
		{
			if ((*i)->GetId() == in_id)
			{
				throw Invalid_Input("Please choose an ID number that doesnt already exist!");
			}
		}
		cout << "New Center Created " << endl;

		PokemonCenter* newCenterPtr;
		newCenterPtr = new PokemonCenter(in_id, 5, 100, newPoint);
		this->center_ptrs.push_back(newCenterPtr);
		this->object_ptrs.push_back(newCenterPtr);
		break;

	case 'g':
		for (list <PokemonGym*>::iterator i = this->gym_ptrs.begin(); i != this->gym_ptrs.end(); i++)
		{
			if ((*i)->GetId() == in_id)
			{
				throw Invalid_Input("Please choose an ID number that doesnt already exist!");
			}
		}
		cout << "New Gym Created " << endl;

		PokemonGym* newGymPtr;
		newGymPtr = new PokemonGym(10, 1, 1, 2, in_id, newPoint);
		this->gym_ptrs.push_back(newGymPtr);
		this->object_ptrs.push_back(newGymPtr);
		break;

	case 't':
		for (list <Trainer*>::iterator i = this->trainer_ptrs.begin(); i != this->trainer_ptrs.end(); i++)
		{
			if ((*i)->GetId() == in_id)
			{
				throw Invalid_Input("Please choose an ID number that doesnt already exist!");
			}
		}

		cout << "Choose name for trainer: ";
		cin >> trainername;
		cout << "Choose speed for trainer: ";
		cin >> speed;

		Trainer* newTrainerPtr;
		newTrainerPtr = new Trainer(trainername, in_id, 'T', speed, newPoint);
		this->trainer_ptrs.push_back(newTrainerPtr);
		this->object_ptrs.push_back(newTrainerPtr);
		break;

	case 'w':

		for (list <WildPokemon*>::iterator i = this->wildpokemon_ptrs.begin(); i != this->wildpokemon_ptrs.end(); i++)
		{
			if ((*i)->GetId() == in_id)
			{
				throw Invalid_Input("Please choose an ID number that doesnt already exist!");
			}
		}

		string Pokemonname;
		double attack;
		double health;

		cout << "Choose name for pokemon: ";
		cin >> Pokemonname;
		cout << "Choose attack for pokemon: ";
		cin >> attack;
		cout << "Choose health for pokemon: ";
		cin >> health;

		WildPokemon* newWildPokemonPtr;
		newWildPokemonPtr = new WildPokemon(20.0, Pokemonname, attack, health, true, in_id, newPoint);
		this->wildpokemon_ptrs.push_back(newWildPokemonPtr);
		this->object_ptrs.push_back(newWildPokemonPtr);
		break;
	}
}
