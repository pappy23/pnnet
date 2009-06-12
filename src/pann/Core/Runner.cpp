//Runner.cpp

#include "Includes/BoostSerialization.h"
#include "Runner.h"

REGISTER_SINGLETON_CPP(NullFeedforwardRunner);
REGISTER_SINGLETON_CPP(NullBackpropagationRunner);
REGISTER_SINGLETON_CPP(FeedforwardPropagationRunner);
REGISTER_SINGLETON_CPP(BackpropagationRunner);
REGISTER_SINGLETON_CPP(PyramidalNeuronFeedforwardRunner);

