#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include "feature.h"

class Block;
typedef shared_ptr<Block> Block_ptr;

class Block
{
private:
	// Constructors
	Block(Feature_ptr feature);

	// Member variables (private)
	Feature_ptr _feature;

public:
	// Factories
	static Block_ptr create(Feature_ptr feature);

	// Getters
	Feature_ptr getFeature();
};

#endif