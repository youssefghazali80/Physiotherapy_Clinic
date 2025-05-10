#include "EU_WaitList.h"
#include "Node.h"

// Constructor
EU_WaitList::EU_WaitList() :LinkedQueue(){};



// Function to insert the new patient in a sorted way.


void EU_WaitList::insertSorted(Patient * patient){
    Node <Patient *>* newNode = new Node<Patient *>(patient);
        itemCount++;

        // Insert at head if highest priority
        if (frontPtr == nullptr || patient->getPT() > (frontPtr->getItem())->getPT()) {
            newNode->setNext(frontPtr);
            frontPtr = newNode;
            return;
        }

        // Find correct position in queue
        Node<Patient *> * current = frontPtr;
        while (current->getNext() && patient->getPT() <= (current->getItem())->getPT()) {
            current = current->getNext();
        }
        
        newNode->setNext(current->getNext());
        current->setNext(newNode);
}

// function to calculate the total latency of the current queue.
int EU_WaitList::calcTreatmentLatency(){

    // the treatment latency time.
    int latencytime=0;

    Node <Patient *>* currentNode =frontPtr;
    Patient * currentPatient;
    //loop on the queue and calculate the total latency time for the patients
    for (int i=1; i<=itemCount;i++){

        currentPatient=currentNode->getItem();
        latencytime+=currentPatient->getNextTreatment();
        currentNode=currentNode->getNext();

    }
    return latencytime;
}
std::ostream& operator<<(std::ostream& os, const EU_WaitList& list){
        Node <Patient *>* currentNode= list.frontPtr; 


        while (currentNode != nullptr ) {
        os << *(currentNode->getItem()) << std::endl;
        currentNode = currentNode->getNext();
         }
        return os; 

}




