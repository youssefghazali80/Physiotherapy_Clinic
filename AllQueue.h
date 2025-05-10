#ifndef ALLQUEUE_H
#define ALLQUEUE_H

#include "LinkedQueue.h"
#include "Patient.h"


class AllQueue : public LinkedQueue<Patient *>
{
    public:
    friend std::ostream& operator<<(std::ostream& os,  const AllQueue& all);



};

#endif