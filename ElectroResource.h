#ifndef ELECTRORESOURCE_H
#define ELECTRORESOURCE_H
// Electro therapy resource
#include "TreatmentResource.h"
#include <iostream>

class ElectroResource : public TreatmentResource {
public:
    ElectroResource(int i) : TreatmentResource(i) {}
    friend std::ostream& operator<<(std::ostream& os,  const ElectroResource& resource);
};



#endif