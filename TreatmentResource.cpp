#include "TreatmentResource.h"
    
// Constructor
TreatmentResource::TreatmentResource(int i) : id(i), available(true) {}


// Getter for the ID of the treatment Resource.
int TreatmentResource:: getID() const { return id; }

// Check if the resource is available.
bool TreatmentResource :: isAvailable() const { return available; }

// Set the resource as available.
void TreatmentResource :: setAvailable(bool avail) { available = avail; }

// Virtual Destructor.
TreatmentResource::~TreatmentResource() {}