#ifndef EUWAITLIST_H
#define EUWAITLIST_H

#include "LinkedQueue.h"
#include "Patient.h"


class EU_WaitList : public LinkedQueue<Patient *>
{
    public:

    // Constructor
    EU_WaitList ();

    // Add Insert Sorted function.
    void insertSorted(Patient * patient);

    // Add calc latency
    int calcTreatmentLatency();

    // Using friendships relation to overload the <<
    friend std::ostream& operator<<(std::ostream& os, const EU_WaitList& list);

};







#endif