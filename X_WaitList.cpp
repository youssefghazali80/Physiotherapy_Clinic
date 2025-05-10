#include "X_WaitList.h"
#include <random>
#include "Node.h"

using namespace std;
Patient * X_WaitList:: cancel(){
    if (itemCount == 0 ){
        //return false if the early patients list has no patient (empty list)
        return nullptr; 
    }
    else
    {
    random_device rd;                                   // Get a random seed.
    mt19937 gen(rd());                                  // Mersenne Twister generator.
    uniform_int_distribution <> dist1(0,itemCount-1);   // Range[1,itemCount]

    int randomPatient = dist1(gen);                     // Generate the number.
    Node<Patient *> * currentNode = frontPtr; 
    Node<Patient *> * previousNode = nullptr;          
    // Loop Till We stop on the current patient.
    // Traverse to the random node
    for (int i = 0; i < randomPatient; ++i) {
        previousNode = currentNode;
        currentNode = currentNode->getNext();
    }
    if (currentNode!=nullptr){
    Patient * currentPatient = currentNode-> getItem();
    
    // Check if the X_Therapy is the last treatment that the patient will have.
    if (currentPatient->getRemainingTreatment()!=1 || currentPatient->getCancelled() == true){
        return nullptr;
    }
    // set this patient as cancelled patient .
    currentPatient->setCancelled();


    // Remove the node
    if (previousNode == nullptr) {
    // removing head
        frontPtr = currentNode->getNext();
    }
     else 
     {
    previousNode->setNext(currentNode->getNext());
     }

    currentNode->setNext(nullptr);
    itemCount--;
    // return the pointer to the patient to the scheduler to be moved to the finish list 
    return currentNode-> getItem();

    }

    }
    return nullptr;
}