/*
 * @file
 * Generic runner realization
 */

#include "Runner.h"

namespace pann
{
    Runner* NullRunner::self = 0;
    Runner* NullBackpropagationRunner::self = 0;
    Runner* FeedforwardPropagationRunner::self = 0;
}; //pann

