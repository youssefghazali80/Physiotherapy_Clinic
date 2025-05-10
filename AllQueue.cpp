#include "AllQueue.h"




std::ostream& operator<<(std::ostream& os, const AllQueue& all){
    Node <Patient *>* currentNode=all.frontPtr; 
    int count = 0;

    while (currentNode != nullptr && count < 10) {
        os << *(currentNode->getItem());
        currentNode = currentNode->getNext();
        count++;
    }
      cout << endl;
      return os;

}