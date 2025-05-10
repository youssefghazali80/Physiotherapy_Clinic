#ifndef UI_H
#define UI_H


#include "priQueue.h"
#include <memory>
#include <string>
#include <fstream>
#include "LinkedQueue.h"
#include "TreatmentResource.h"
#include "GymResource.h"
#include "ElectroResource.h"
#include "UltrasoundResource.h"
#include "Patient.h"
#include "EarlyQueue.h"
#include "ArrayStack.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "UI.h"
#include "AllQueue.h"


enum ProgramMode {INTERACTIVE,SILENT};

class UI {
    private:

    ProgramMode Mode;     // Mode of the program.


    public:
    UI(ProgramMode programMode);
    ProgramMode getMode();
    void printAllpatientList(AllQueue  * allPatients);
    void printElectroWaitingList(EU_WaitList * waiting_list);
    
    // Then print the U_Therapy waiitng list
    void printUltraSoundWaitingList(EU_WaitList * waiting_list);

    // Then print the X_Therapy waiting list.
    void printXTherapyWaitingList(X_WaitList * waiting_list);


    // Then print the Early list.
    void printEarlyList(EarlyQueue<Patient*> * earlyPatients);

    // Then print the late list
    void printLateList(priQueue<Patient *> * latePatients) ;

    // Then print the Avaialbe E_devices;
    void printAvailableERersources(LinkedQueue<ElectroResource * > *resources);

    // Then print the Availabe U-devices;
    void printAvailableUResources(LinkedQueue<UltrasoundResource *> *resources);

    // Then print the avaialble x-rooms();
    void printAvailableXResources(LinkedQueue<GymResource *>* resources);

    // Then print the available In Treatment Patients.
    void printInTreatmentList(LinkedQueue<Patient *> *patients); 

    // Then print the finished list
    void printFinishedList(ArrayStack <Patient *> *finishedPatients);

    //wait for any key pressed
    void waitForAnyKey();
    

    };
    












#endif