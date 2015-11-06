using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "points.h"
#include "point.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Points::Points()
{
	// do nothing...
}

/**
 *	(Private) Constructs a vector of points extracted from a
 *	file with the name provided as an argument.
 */
Points::Points(string &filename)
{
	_filename = filename;
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
			vector<double> tmp;

			// Extract the first three segments of each entry
			while (getline(ss, item, '\t') && count < 3)
			{
				tmp.push_back(atof(item.c_str()));
				count++;	// Track no of segments
			}
			
			add(Point::create(tmp));
		}

		file.close();
	}
	else
	{
		throw 1;
	}
}

/**
 *	Factory method using default constructor.
 */
Points_ptr Points::create()
{
	return Points_ptr(new Points());
}

/**
 *	Factory method using the filename constructor.
 */
Points_ptr Points::create(string &filename)
{
	return Points_ptr(new Points(filename));
}

/**
 *	Add a point to the vector.
 */
void Points::add(Point_ptr &point)
{
	_items.push_back(point);
}

/**
 *	Remove a point from the vector.
 */
void Points::remove(Point_ptr point)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (*point == *_items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
}

/**
 *	Retrieve a point by index.
 */
Point_ptr Points::get(int index)
{
	return _items.at(index);
}

Point_ptr Points::first()
{
	return get(0);
}

Point_ptr Points::last()
{
	return get(size() - 1);
}

/**
 *	Return the size of the vector.
 */
int Points::size()
{
	return _items.size();
}

/**
 *	Translate the points in the xy plane and rotate about
 *	the z-axis.
 */
void Points::transform(double matrix[4][4])
{

}

void Points::mirrorX()
{
	mirrorComponent(0);
}

void Points::mirrorY()
{
	mirrorComponent(1);
}

void Points::mirrorZ()
{
	mirrorComponent(2);
}

void Points::mirrorComponent(int index)
{
	for (int i = 0; i < size(); i++)
	{
		get(i)->setComponent(index,
			get(i)->getComponent(index) * -1);
	}
}

/**
 *	Get the vector of points.
 */
vector<Point_ptr> Points::getItems()
{
	return _items;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Points &p)
{
	return strm;
}