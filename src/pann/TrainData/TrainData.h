#ifndef TRAINDATA_H
#define TRAINDATA_H

#include <vector>

#include "Core/Type.h"

namespace pann
{
    class TrainPattern;

    class TrainData
    {
        /* Public interface */
    public:
        TrainData() throw();
        virtual ~TrainData() throw();

        Float getMse() const;
        void shuffle() throw();

        /* Public members */
    public:
        std::vector<TrainPattern> data;
    };

}; //pann

#endif

