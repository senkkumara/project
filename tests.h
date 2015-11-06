#ifndef TEST_H
#define TEST_H

#include "layer.h"

namespace Tests
{
	bool HasLayerGotFourPoints(Layer_ptr layer);
	bool HasLayerGotFivePoints(Layer_ptr layer);
	bool HasLayerGotSixOrMorePoints(Layer_ptr layer);
	bool AreTheInterfacesParallel(Layer_ptr layer);
};

#endif