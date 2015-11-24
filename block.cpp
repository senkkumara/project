using namespace std;

#include "block.h"

Block::Block()
{

}

Block_ptr Block::create()
{
	return Block_ptr(new Block());
}