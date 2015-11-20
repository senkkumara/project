/**
 *	surfaces.cpp
 *	-----------------------------------------------------------------------
 *	See "surfaces.h" for a description.
 */

using namespace std;

#include "surfaces.h"
#include "exceptions.h"

Surfaces::Surfaces()
{

}

Surfaces::Surfaces(Geometry_ptr &geometry)
{

}

void Surfaces::_init()
{
	_layers = Layers::create();
	_rises = Rises::create();
}

void Surfaces::_build(Geometry_ptr &geometry)
{

}

void Surfaces::_findInterfaces()
{

}

void Surfaces::_findInterface(Layer_ptr &layer1, Layer_ptr &Layer2)
{

}

Layers_ptr Surfaces::getLayers()
{
	return _layers;
}

Rises_ptr Surfaces::getRises()
{
	return _rises;
}