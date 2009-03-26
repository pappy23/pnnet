#ifndef TRAINDATA_H
#define TRAINDATA_H

#include "Core/Includes.h"
#include "Core/Type.h"
#include "TrainPattern.h"

namespace pann
{
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

