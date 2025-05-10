#ifndef ULTRASOUNDRESOURCE_H
#define ULTRASOUNDRESOURCE_H
#include "TreatmentResource.h"
#include <iostream>


// Ultrasound therapy resource
class UltrasoundResource : public TreatmentResource {
public:
    UltrasoundResource(int i) : TreatmentResource(i) {}
    friend std::ostream& operator<<(std::ostream& os,  const UltrasoundResource& resource);
};



#endif
