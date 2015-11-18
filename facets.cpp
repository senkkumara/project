using namespace std;

#include "facets.h"
#include <fstream>
#include <sstream>
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facets::Facets()
{
	// do nothing...
}

/**
 *	(Private) Constructs a vector of facets extracted from a
 *	file with the name provided as an argument.
 */
Facets::Facets(std::string &filename)
{
	//TODO: implement method
}

/**
 *	Factory method using default constructor.
 */
Facets_ptr Facets::create()
{
	return Facets_ptr(new Facets());
}

/**
 *	Factory method using the filename constructor.
 */
Facets_ptr Facets::create(std::string &filename)
{
	return Facets_ptr(new Facets(filename));
}

/**
 *	Add a facet to the vector.
 */
void Facets::add(Facet_ptr &facet)
{
	_items.push_back(facet);
}

/**
 *	Remove a facet from the vector.
 */
void Facets::remove(Facet_ptr facet)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (*facet == *_items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
}

/**
 *	Retrieve a facet by index.
 */
Facet_ptr Facets::get(int index)
{
	return _items.at(index);
}

Facet_ptr Facets::first()
{
	return get(0);
}

Facet_ptr Facets::last()
{
	return get(size() - 1);
}

/**
 *	Return the size of the vector.
 */
int Facets::size()
{
	return _items.size();
}

void Facets::_extractFromDXF(std::string &filename)
{

}

void Facets::_extractFromSTL(string &filename)
{
	std::string line;
	ifstream file(filename);
	
	if (!file.is_open())
	{
		throw FileNotFoundException();
	}

	//Facets_ptr facets;
	Points_ptr points;
	//Edges_ptr edges;
	Facet_ptr facet;
	Point_ptr point;
	Edge_ptr edge;
	bool inFacet = false;
	bool inLoop = false;

	while (getline(file, line))
	{
		// Look for start of a facet - start compiling a loop
		if (line.find("facet") != std::string::npos)
		{
			inFacet = true;
			continue;
		}

		// Look for end of a facet - stop compiling a loop
		if (line.find("endfacet") != std::string::npos)
		{
			inFacet = false;
			continue;
		}

		// Look for start of a facet loop - start collecting vertices
		if (inFacet && line.find("outer loop") != std::string::npos)
		{
			inLoop = true;
			continue;
		}

		// Look for the end of a facet loop - stop collecting vertices
		if (inFacet && line.find("endloop") != std::string::npos)
		{
			inLoop = false;
			continue;
		}

		// Get vertices
		if (inFacet && inLoop && line.find("vertex") != std::string::npos)
		{
			// Remove "      vertex " prefix
			std::stringstream ss(line.substr(line.find("vertex") + 7));
			std::string item;
			int count = 0;		// Only extract three entries (x, y, z)
			std::vector<double> coords;

			while (getline(ss, item, ' ') && count < 3)
			{
				coords.push_back(atof(item.c_str()));
				count++;
			}
		}
	}

	file.close();
}