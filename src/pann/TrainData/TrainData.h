#ifndef TRAINDATA_H
#define TRAINDATA_H

#include "Includes/Std.h"
#include "Core/Type.h"

namespace pann
{
    class TrainPattern;

    class TrainData
    {
        /* Public interface */
    public:
        TrainData();
        virtual ~TrainData();

        Float getMse() const;
        void shuffle();

        /* Public members */
    public:
        std::vector<TrainPattern> data;
    };

}; //pann

#endif
