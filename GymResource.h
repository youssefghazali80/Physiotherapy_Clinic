#ifndef GYMRESOURCE_H
#define GYMRESOURCE_H

#include "TreatmentResource.h"
#include <iostream>
// Gym therapy resource with capacity tracking
class GymResource : public TreatmentResource {
private:

    int capacity;           // Maximum patients
    int currentOccupancy;   // Current patients

public:
    GymResource(int i, int cap);

    // Override availability check
    bool isAvailable() const override;


    // Patient leaves gym
    void patientLeft();

    // Gets the capacity of the gym
    int getCapacity() const;

    // Gets the current Ocuupancy.
    int getCurrentOccupancy() const;


    void patientEntered();
    void patientLeaved();
    friend std::ostream& operator<<(std::ostream& os,  const GymResource& resource);
};





#endif // GYMRESOURCE_H
