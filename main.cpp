#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "GameCommand.h"
#include "Input_Handling.h"




using namespace std;

Model* Model::Master = 0;

int main()
{
	Model *M = M->getMaster();
	View V = View();

	cout << "EC327" << endl;
	cout << "PA3" << endl;

	M->ShowStatus();
	M->Display(V);

	char userinput;
  bool loopval = true;

	while(loopval)
	{
		cout << "\n PA3 Pokemon Instructions: " << endl;
		cout << "Valid Game Commands are as follows: "  << endl;
		cout << "m \\ Move Trainer to location X,Y " << endl;
		cout <<  "g \\ Move Trainer to Pokemon Gym " << endl;
		cout << "c \\ Move Trainer to Pokemon Center " << endl;
		cout << "s \\ Stops Trainer" << endl;
		cout << "p \\ Trainer to buy potions at a Pokemon Center " << endl;
		cout << "b \\ Trainer to battle at a Pokemon Gym" << endl;
		cout << "a \\ Advance one time by updating each object once." << endl;
		cout << "n \\ Create new objects. " << endl;
		cout << "r \\ advance one-time step and update each object, and repeat until either the update function returns true for at least one of the objects, or 5 time steps have been done. " << endl;
		cout << "q \\ terminate the program" << endl;

		cout << "Please enter your command: ";
		cin >> userinput;

		Point2D P1;
		int x, y;
		int in_id;
		int gym_id;
		int center_id;
		int potioncount;
		int battlenumber;
		char in_type;
		try
		{
			switch (userinput)
			{

			case 'n':
				cout << "Enter object type c, g, t, m: ";
				cin >> in_type;
				cout << "Enter object ID: ";
				cin >> in_id;
				cout << "Please enter x coords: ";
				cin >> x;
				cout << "Please enter y coords: ";
				cin >> y;

				DoNewCommand(*M, in_type, in_id, x, y);

				break;
			case 'm':


				cout << "Please enter Trainer ID: ";
				cin >> in_id;
				cout << "Please enter x coords: ";
				cin >> x;
				cout << "Please enter y coords: ";
				cin >> y;

				P1.x = x;
				P1.y = y;

				DoMoveCommand(*M, in_id, P1);
				cout << "Moving Trainer " << in_id << " to " << P1;
				break;

			case 'g':

				cout << "Please enter Trainer ID: ";
				cin >> in_id;
				cout << "Please enter Gym ID: ";
				cin >> gym_id;

				DoMoveToGymCommand(*M, in_id, gym_id);
				cout << "Moving Trainer " << in_id << " to Gym " << gym_id;
				break;

			case 'c':

				cout << "Please enter Trainer ID: ";
				cin >> in_id;
				cout << "Please enter Center ID: ";
				cin >> center_id;

				DoMoveToGymCommand(*M, in_id, center_id);
				cout << "Moving Trainer " << in_id << " to Center " << center_id;
				break;

			case 'p':

				cout << "Please enter Trainer ID: ";
				cin >> in_id;
				cout << "Please enter Potion Count ";
				cin >> potioncount;

				DoRecoverInCenterCommand(*M, in_id, potioncount);
				cout << "Recovering Trainer " << in_id << " with potion quantity " << potioncount;
				break;

			case 's':

				cout << "Please enter Trainer ID: ";
				cin >> in_id;

				DoStopCommand(*M, in_id);
				cout << "Stopped Trainer: " << in_id << endl;;
				break;

			case 'b':

				cout << "Please enter Trainer ID: ";
				cin >> in_id;
				cout << "Please enter Battle Count: ";
				cin >> battlenumber;

				DoBattleCommand(*M, in_id, battlenumber);
				cout << "Trainer " << in_id << " is battling " << battlenumber << " times. " << endl;;
				break;

			case 'a':

				DoAdvanceCommand(*M, V);
				break;

			case 'r':

				DoRunCommand(*M, V);
				break;

			case 'q':

				cout << "Quit" << endl;
				loopval = false;
				exit(0);
				break;

			default:
				cout << "INVALID INPUT" << endl;
				throw("Invalid command! Please enter a valid command. ");
				break;
			}
		}
		catch (Invalid_Input& except)
		{
			cout << "Invalid input - " << except.msg_ptr << endl;
		}


		if (userinput != 'r' || userinput != 'a')
		{
			//M->Display(V); // THIS WOULD ALWAYS THROW AN ALLOCATION ERROR
		}
			

	}
}
