#include "Trainer.h"
#include "Vector2D.h"
#include "Point2D.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>


using namespace std;

string Trainer::GetName()
{
	return this->name;
}

static double GetRandomAmountOfPokeDollars()
{
	srand(time(NULL));
	double num = (double)rand() / RAND_MAX;
	return 0.0 + num * (2.0);
}

Trainer::~Trainer()
{
	cout << "Trainer destructed." << endl;
}
Trainer::Trainer() :GameObject('T')
{
	this->speed = 5;
	cout << "Trainer default constructed" << endl;
}
Trainer::Trainer(char in_code) :GameObject('T')
{
	this->speed = 5;
	cout << "Trainer constructed" << endl;
	this->display_code = in_code;

	this->PokeDollars = 0;
	this->experience = 0;
	this->state = STOPPED;
	this->battles_to_buy = 0;
	this->potions_to_buy = 0;
	this->health = 20;

}
Trainer::Trainer(std::string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) :GameObject(in_loc, in_id, 'T')
{
	this->display_code = in_code;
	this->speed = in_speed;
	this->name = in_name;

	this->PokeDollars = 0;
	this->experience = 0;
	this->state = STOPPED;
	this->battles_to_buy = 0;
	this->potions_to_buy = 0;
	this->health = 20;

	this->location = in_loc;

	cout << "Trainer constructed" << endl;
	cout << "ID: " << this->GetId() << endl;
}
void Trainer::StartMoving(Point2D dest)
{

	if (this->location.x == dest.x && this->location.y == dest.y)
	{
		cout << this->display_code << " " << this->id_num << ": I'm already there. See?" << endl;
		this->state = STOPPED;
	}
	else if (HasFainted())
	{
		cout << this->display_code << " " << this->id_num << ": My pokemon have fainted. I may move but you cannot see me" << endl;
		this->state = FAINTED;
	}
	else
	{
		cout << "On my way." << endl;
		Trainer::SetupDestination(dest);
		this->state = MOVING;
	}
}
void Trainer::StartMovingToCenter(PokemonCenter* center)
{

	if (this->location.x == center->GetLocation().x && this->location.y == center->GetLocation().y)
	{
		cout << this->display_code << " " << this->id_num << ": I'm already at the PokemonGym" << endl;
		this->state = AT_CENTER;
	}
	else if (this->HasFainted())
	{
		cout << this->display_code << " " << this->id_num << ": My pokemon have fainted. I may move but you cannot see me" << endl;
		this->state = FAINTED;
	}
	else
	{
		cout << "On my way." << endl;
		this->current_center = center;
		Trainer::SetupDestination(center->GetLocation());
		this->state = MOVING_TO_CENTER;
	}
}

void Trainer::StartMovingToGym(PokemonGym* gym)
{
	if (this->location.x == gym->GetLocation().x && this->location.y == gym->GetLocation().y)
	{
		cout << this->display_code << " " << this->id_num << ": I'm already at the PokemonGym" << endl;
		this->state = AT_CENTER;
	}
	else if (this->HasFainted())
	{
		cout << this->display_code << " " << this->id_num << ": My pokemon have fainted. I may move but you cannot see me" << endl;
		this->state = FAINTED;
	}
	else
	{
		cout << "On my way." << endl;
		this->current_gym = gym;
		Trainer::SetupDestination(gym->GetLocation());
		this->state = MOVING_TO_GYM;
	}
}

void Trainer::StartBattling(unsigned int num_battles)
{
	if (this->state != IN_GYM)
	{
		cout << this->display_code << " " << this->id_num << "I can only battle in a Pokemon Gym!" << endl;

	}
	else {

		if (HasFainted())
		{
			cout << this->display_code << " " << this->id_num << "My Pokemon have fainted so no more battles for me..." << endl;
			this->state = FAINTED;
		}
		else if (!current_gym->IsAbleToBattle(num_battles, PokeDollars, health))
		{
			cout << this->display_code << " " << this->id_num << "Not enough money/health for battles " << endl;
		}
		else if (current_gym->GetState() == DEFEATED)
		{
			cout << this->display_code << " " << this->id_num << "Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
		}

		else
		{
			this->state = BATTLING_IN_GYM;
			cout << this->display_code << " Started to battle at the PokemonGym " << current_gym->GetId() << " with " << current_gym->GetNumBattlesRemaining() << " battles" << endl;

			battles_to_buy = min(num_battles, current_gym->GetNumBattlesRemaining()); // suggested by friend.
		}
	}
}

void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
	if (this->state != AT_CENTER)
	{
		cout << this->display_code << " " << this->id_num << "I can only recover health at a Pokemon Center!" << endl;

	}
	else {

		if ((current_center->GetPokeDollarCost(num_potions)) > PokeDollars)
		{
			cout << this->display_code << " " << this->id_num << "Not enough money to recover health." << endl;

		}
		else if (current_center->GetNumPotionRemaining() == 0)
		{
			cout << this->display_code << " " << this->id_num << "Cannot recover! No potion remaining in this Pokemon Center" << endl;
		}
		else if (current_gym->GetState() == DEFEATED)
		{
			cout << this->display_code << " " << this->id_num << "Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
		}

		else
		{
			this->state = RECOVERING_HEALTH;
			cout << this->display_code << " Started to battle at the PokemonGym " << current_gym->GetId() << " with " << current_gym->GetNumBattlesRemaining() << " battles" << endl;

			potions_to_buy = min(num_potions, current_center->GetNumPotionRemaining()); // suggested by friend.
		}
	}
}

void Trainer::Stop()
{
	this->state = STOPPED;
	cout << display_code << " " << id_num << " : Stopping..." << endl;
}

bool Trainer::HasFainted()
{

	if (this->health == 0)
	{
		this->state = FAINTED;
		return true;
	}
	else {
		return false;
	}
}
bool Trainer::ShouldBeVisible()
{
	if (state == FAINTED)
	{
		return false;
	}
	else {
		return true;
	}
}

void Trainer::ShowStatus()
{
	cout << name << "Status:" << endl;
	GameObject::ShowStatus();
	switch (state)
	{
	case STOPPED:
		cout << "stopped" << endl;

		break;

	case MOVING:
		cout << "moving at a speed of " << speed << " to destination <" << destination.x << ", " << destination.y << ">"
			<< " at each step of " << delta << endl;

		break;

	case MOVING_TO_CENTER:
		cout << "heading to Pokemon Center " << current_center->GetId() << " at a speed of " << " " << speed
			<< "at each step of " << delta;

		break;

	case MOVING_TO_GYM:
		cout << "heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << " " << speed
			<< "at each step of " << delta;

		break;

	case AT_CENTER:
		cout << "inside Pokemon Center" << current_center->GetId() << endl;

		break;

	case IN_GYM:
		cout << "inside Pokemon Gym" << current_gym->GetId() << endl;

		break;

	case BATTLING_IN_GYM:
		cout << "battling in Pokemon Gym" << current_gym->GetId() << endl;

		break;

	case RECOVERING_HEALTH:
		cout << "recovering health in Pokemon Center" << current_center->GetId() << endl;

		break;
	default:
		break;


	}

	cout << " Health: " << this->health << endl;
	cout << " Pokemon Dollars:" << this->PokeDollars << endl;
	cout << " Experience Points: " << this->experience << endl;
}

bool Trainer::Update()
{
	bool boolval = false;
	switch (state)
	{
	case STOPPED:
		Trainer::ShowStatus();
		boolval = false;
		break;

	case MOVING:
		Trainer::ShowStatus();
		Trainer::UpdateLocation();
		if (this->location.x == destination.x && this->location.y == destination.y)
		{
			state = STOPPED;
			boolval = true;
		}
		else
		{
			state = MOVING;
		}

		if (this->is_at_center)
		{
			current_center->RemoveOneTrainer();
		}
		else if (this->IS_IN_GYM)
		{
			current_gym->RemoveOneTrainer();
		}

		break;

	case MOVING_TO_CENTER:
		Trainer::ShowStatus();
		Trainer::UpdateLocation();
		if (this->location.x == destination.x && this->location.y == destination.y)
		{
			state = AT_CENTER;
			current_center->AddOneTrainer();
			boolval = true;
		}
		else
		{
			this->PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
			state = MOVING;
		}

		if (this->IS_IN_GYM)
		{
			current_gym->RemoveOneTrainer();
		}

		break;

	case MOVING_TO_GYM:
		Trainer::ShowStatus();
		Trainer::UpdateLocation();

		if (this->location.x == destination.x && this->location.y == destination.y)
		{
			this->state = IN_GYM;
			current_gym->AddOneTrainer();
			boolval = true;
		}
		else
		{
			this->PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
			state = MOVING_TO_GYM;
		}

		if (this->is_at_center)
		{
			current_center->RemoveOneTrainer();
		}
		break;

	case AT_CENTER:
		Trainer::ShowStatus();
		this->is_at_center = true;
		boolval = false;
		break;

	case IN_GYM:
		Trainer::ShowStatus();
		this->IS_IN_GYM = false;
		boolval = false;
		break;

	case BATTLING_IN_GYM:
		Trainer::ShowStatus();

		this->PokeDollars -= current_gym->GetPokeDollarCost(battles_to_buy);
		this->experience += current_gym->TrainPokemon(battles_to_buy);
		cout << "** " << this->name << "completed " << this->battles_to_buy << "battle(s)!**" << endl;
		cout << "** " << this->name << "gained " << current_gym->TrainPokemon(battles_to_buy) << "experience point(s)!" << endl;

		state = IN_GYM;
		boolval = true;
		break;

	case RECOVERING_HEALTH:
		Trainer::ShowStatus();
		this->health += current_center->DistributePotion(this->potions_to_buy);
		this->PokeDollars -= current_center->GetPokeDollarCost(this->potions_to_buy);


		cout << "** " << this->name << "recovered" << current_center->DistributePotion(this->potions_to_buy)
			<< " health!" << endl;
		state = AT_CENTER;

		boolval = true;

		break;
	case FAINTED:

		cout << this->name << " is out of health and can't move" << endl;
		this->state = FAINTED;
		boolval = false;

		break;
	default:
		boolval = false;
		break;
	}

	return boolval;
}

bool Trainer::UpdateLocation()
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
		cout << this->display_code << " " << this->id_num << ": " << "I'm there!" << endl;
	}
	else
	{
		cout << this->display_code << " " << this->id_num << ": " << "step..." << endl;
	}
}

void Trainer::SetupDestination(Point2D dest)
{
	destination = dest;

	delta = (dest - location) * (speed / GetDistanceBetween(dest, location));
	state = MOVING;
}
