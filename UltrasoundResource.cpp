#include "UltrasoundResource.h"
#include "iostream"
std::ostream& operator<<(std::ostream& os,  const UltrasoundResource& resource){
     os <<  resource.getID() << ",";
     return os;
}