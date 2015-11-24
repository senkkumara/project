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
	Block();

public:
	// Factories
	static Block_ptr create();

};

#endif