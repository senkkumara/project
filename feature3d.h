#ifndef FEATURE3D_H
#define FEATURE3D_H

using namespace std;

#include <memory>
#include <vector>
#include "entity.h"
#include "edges.h"
#include "edge.h"

class Feature3D;
typedef shared_ptr<Feature3D> Feature3D_ptr;

enum Feature3DType
{
	F3D_STRAIGHT,
	F3D_CORNER,
	F3D_HELIX,
	F3D_SPLIT,
	F3D_SPECIAL,
	F3D_TRANSITION
};

class Feature3D
{
protected:
	// Deconstructors
	virtual ~Feature3D();

	// Methods (private)
	void _init();

public:
	
};

class Feature3DStraight;
typedef shared_ptr<Feature3DStraight> Feature3DStraight_ptr;

class Feature3DStraight : public Feature3D
{

};

class Feature3DCorner;
typedef shared_ptr<Feature3DCorner> Feature3DCorner_ptr;

class Feature3DCorner
{

};

class Feature3DHelix;
typedef shared_ptr<Feature3DHelix> Feature3DHelix_ptr;

class Feature3DHelix
{

};

class Feature3DTrans;
typedef shared_ptr<Feature3DTrans> Feature3DTrans_ptr;

class Feature3DTrans
{

};

#endif