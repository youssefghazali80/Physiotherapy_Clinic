#include"ElectroResource.h"
#include <iostream>
std::ostream& operator<<(std::ostream& os,  const ElectroResource& resource){
     os <<  resource.getID() << ",";
     return os;
}
