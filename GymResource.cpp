#include "GymResource.h"
#include "iostream"
// Constructor
GymResource::GymResource(int i, int cap): TreatmentResource(i), capacity(cap), currentOccupancy(0) {}

// Override availability check
bool GymResource::isAvailable() const {
    return currentOccupancy < capacity;
}



// Patient leaves gym
void GymResource::patientLeft() {
    if (currentOccupancy > 0) currentOccupancy--;
    available = true;
}

int GymResource::getCapacity() const {
    return capacity;
}

int GymResource::getCurrentOccupancy() const {
    return currentOccupancy;
}

void GymResource :: patientEntered(){
    currentOccupancy++;
    }
void GymResource :: patientLeaved(){
    currentOccupancy--;
    }

std::ostream& operator<<(std::ostream& os,  const GymResource& resource){
     os << "R"<< resource.getID()<< "[" <<resource.getCurrentOccupancy() <<"," <<resource.getCapacity()
      << "], " ;
     return os;
}