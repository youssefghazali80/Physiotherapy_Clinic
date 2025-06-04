#include "UI.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "ElectroResource.h"
#include "UltrasoundResource.h"
#include "ArrayStack.h"
#include "GymResource.h"
//#include <conio.h>    // This is for windows
#include <unistd.h>
#include "termio.h"
// CONSTRUCTOR.
UI :: UI (ProgramMode programMode) : Mode(programMode){}

ProgramMode UI :: getMode(){return Mode;}

// print the details of #include <unistd.h>the first 10 patients
void UI :: printAllpatientList(AllQueue * allPatients)
{   

    std::cout << "===============   ALL List   =================" << std::endl;
    std::cout << *(allPatients);


}
void UI :: printElectroWaitingList(EU_WaitList * waiting_list){
    std::cout << "===============   Waiting List   =================" << std::endl;
    std::cout << waiting_list->size() << " E-therapy patients" << *(waiting_list) <<endl ;



}
    
    // Then print the U_Therapy waiitng list
void UI::printUltraSoundWaitingList(EU_WaitList * waiting_list){
    std::cout << waiting_list->size() << " U-therapy patients" << *(waiting_list) <<endl ;

}

    // Then print the X_Therapy waiting list.
void UI :: printXTherapyWaitingList(X_WaitList * waiting_list){
     std::cout << waiting_list->size() << " X-therapy patients" << *(waiting_list) <<endl ;

}


// Then print the Early list.
void UI::printEarlyList(EarlyQueue<Patient*> * earlyPatients){
    std::cout << "===============   Early List   =================" << std::endl;
    std::cout << earlyPatients->size() << " patients: " << *(earlyPatients) <<endl; 


}

// Then print the late list
void UI ::printLateList(priQueue<Patient *> * latePatients) {
    std::cout << "===============   Late List   =================" << std::endl;
    std::cout << latePatients->size() << " patients: " << *(latePatients) <<endl; 

}

// Then print the Avaialbe E_devices;
void UI :: printAvailableERersources(LinkedQueue<ElectroResource * > *resources){
    std::cout << "===============   Avail E-Devices   =================" << std::endl;
    std::cout << resources->size() << " Electro devices: " << *(resources) <<endl; 


}


    // Then print the Availabe U-devices;
void UI:: printAvailableUResources(LinkedQueue<UltrasoundResource *> *resources){
    std::cout << "===============   Avail U-Devices   =================" << std::endl;
    std::cout << resources->size() << " Ultra devices: " << *(resources) <<endl; 
}

    // Then print the avaialble x-rooms();
void UI::printAvailableXResources(LinkedQueue<GymResource *>* resources){
    std::cout << "===============   Avail X-Rooms  =================" << std::endl;
    std::cout << resources->size() << " rooms: "   << *(resources) <<endl;  
}

    // Then print the available In Treatment Patients.
void UI:: printInTreatmentList(LinkedQueue<Patient *> *patients){
    std::cout << "===============   In Tretament lists  =================" << std::endl;
    std::cout << patients->size() << " ==> " << *(patients) << endl;
}

    // Then print the finished list
void UI:: printFinishedList(ArrayStack <Patient *> *finishedPatients){
    std::cout << "===============   Finished patients  =================" << std::endl;
    std::cout << finishedPatients->size() << " finished patients: " << *(finishedPatients) << endl;

}

void UI:: waitForAnyKey()
{
   // Waits for a single key press without needing Enter

    std::cout << "Press any key to continue..." << std::flush;

    termios oldt, newt;
    char ch;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Wait for a key press
    read(STDIN_FILENO, &ch, 1);

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    std::cout << std::endl;
    //_getch()         this line for windows.
}

    
