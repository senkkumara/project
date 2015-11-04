using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "points.h"
#include "point.h"

Points::Points()
{

}

Points::Points(string &filename)
{
	std::string line;
	ifstream file(filename);
	std::vector<std::string> entry;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			stringstream ss(line);
			string item;
			int count = 0;
			char delim = '\t';
			vector<double> tmp;

			while (getline(ss, item, delim) && count < 3)
			{
				tmp.push_back(atof(item.c_str()));
				count++;
			}
			
			add(Point::create(tmp));
		}

		file.close();
	}
	else
	{
		cout << "File is not open...";
	}
}

Points::~Points()
{
	//TODO: Add destructor
}

Points_ptr Points::create()
{
	return Points_ptr(new Points());
}

Points_ptr Points::create(string &filename)
{
	return Points_ptr(new Points(filename));
}

vector<Point_ptr> Points::getItems()
{
	return _items;
}

/**
 *	Add a point to the list.
 */
void Points::add(Point_ptr &pnt)
{
	_items.push_back(pnt);
}

/**
 *	Remove a point from the list.
 */
void Points::remove(Point_ptr &pnt)
{

}

/**
 *	Retrieve a point by index.
 */
Point_ptr Points::get(int index)
{
	return _items.at(index);
}

/**
 *	Return the size of the list.
 */
int Points::size()
{
	return _items.size();
}