#ifndef EARLYQUEUE_H
#define EARLYQUEUE_H
#include "priQueue.h"
#include "Patient.h"
#include <random>

// Linked Queue implementation of Queue
template <typename T>

class EarlyQueue : public priQueue <T>  {
public:
     // Constructor 
      EarlyQueue();
     // Reschedule function
      bool reschedule ();
      template <typename U>
      friend std::ostream& operator<<(std::ostream& os,  const EarlyQueue<U>& queue);

};
template <typename U>
std::ostream& operator<<(std::ostream& os, const EarlyQueue<U>& queue){
        priNode <U>* currentNode= queue.head; 

        while (currentNode != nullptr ) {
        os << *(currentNode->getItem());
        
        currentNode = currentNode->getNext();
        }
        os << endl;
        return os; 


}

// make the constructor the same as 
template <typename T>
EarlyQueue<T> :: EarlyQueue() : priQueue<T>(){}



template <typename T>
bool EarlyQueue <T> :: reschedule(){
    if (this->itemCount == 0 ){
        //return false if the early patients list has no patient (empty list)
        return false; 
    }
    else
    {
    random_device rd;                                 // Get a random seed.
    mt19937 gen(rd());                                // Mersenne Twister generator.
    uniform_int_distribution <> dist1(1,this->itemCount);    //Range[1,itemCount]

    int randomPatient = dist1(gen);      // Generate the number.
    priNode<Patient *> * currentNode = this->head; 
    priNode<Patient *> * previousNode = nullptr;
    // Loop Till We stop on the current patient.

    for (int i = 1; i < randomPatient; ++i){
        previousNode = currentNode;
        currentNode = currentNode->getNext();
    }

        Patient * currentPatient = currentNode-> getItem();
        // Check if the patient has cancelled before.
        if (currentPatient->getRescheduled()){
        return false;
        }
        if (previousNode ==nullptr){
            this->head =currentNode->getNext();
            this->itemCount--;
        }
        else{
            previousNode->setNext(currentNode->getNext());
            this->itemCount--;
        }


    // Generate a new appointment Time (PT)
    int oldPT = currentPatient->getPT();
    uniform_int_distribution <> dist2(oldPT ,oldPT+30);    // Range [oldPT,oldPt+30]
    int newPT = dist2(gen);                                // New appointment time
    currentPatient->setPT(newPT);                          // Set the new appointment time
    currentPatient->setReschedule();                        // Sets the falg as Cancelled

    // Place the patient in the in the Early Queue according to its new PT.
    this->enqueue(currentPatient,currentPatient->getPT());
    return true;


    }
    
}





#endif