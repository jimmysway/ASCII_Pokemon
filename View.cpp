#include "View.h"
#include "Point2D.h"
#include "Vector2D.h"



View::View()
{
	origin = Point2D();
	size = 11;
	scale = 2;
}

void View::Clear()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			grid[i][j][0] = '.';
			grid[i][j][1] = ' ';
		}
	}
}

void View::Plot(GameObject *ptr) {
	bool valid;
	int in_x;
	int in_y;
	valid = GetSubscripts(in_x, in_y, ptr->GetLocation());
	if (valid && grid[in_x][in_y][0] == '.')
	{
		ptr->DrawSelf(grid[in_x][in_y]);
	}
	else if (valid)
	{
		grid[in_x][in_y][0] = '*';
		grid[in_x][in_y][1] = ' ';
	}
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
	Vector2D vSubs;
	vSubs.x = int(location.x) - int(origin.x);
	vSubs.y = int(location.y) - int(origin.y);
	vSubs = vSubs/scale;
	vSubs.x = int(vSubs.x);
	vSubs.y = int(vSubs.y);

	out_x = int(vSubs.x);
	out_y = int(vSubs.y);

	double bounds = size*scale;
	if(vSubs.x < bounds && vSubs.y < bounds)
	{
		return true;
	}
	else
	{
		cout << "an object is out of bounds!!" << endl;
		return false;
	}
}

void View::Draw() //got help from friends and tas on this one
{
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = -1; j < size; j++)
		{
			if (j == -1)
			{
				if (i % 2 == 0)
				{
					if (i * scale < 10)
					{
						cout << i * scale << " ";
					}
					else
					{
						cout << i * scale;
					}
				}
				else
				{
					cout << "  ";
				}
			}
			else
			{
				cout << grid[j][i][0] << grid[j][i][1];
			}
		}

		cout << " " << endl;
	}
	cout << " ";
	for (int j = -1; j < size; j++)
	{
		if (j % 2 == 0)
		{
			if (j * scale < 10)
			{
				cout << j * scale << " ";
			}
			else
			{
				cout << j * scale;
			}
		}
		else
		{
			cout << "  ";
		}
	}
}
