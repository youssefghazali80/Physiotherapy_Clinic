// Scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H


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



// Forward declarations

enum class ResourceType{ ELECTRO, ULTRASOUND, GYM }; 

// Scheduler class manages patients, resources, and scheduling logic
class Scheduler {
public:
    // Constructor initializes resource pools and sets the patient data file path
    Scheduler(const std::string& patientDataFile,ProgramMode mode);

    // Loads all the data from the 
    void loadData(const std::string& patientDataFile);

    // Processes newly arrived patients at the current time
    void processNewArrivals();

    // Processes early-arriving patients
    void processEarlyPatients();

    // Processes on-time patients
    void processWaitingPatients();

    // Processes In tretament Patients.
    void ProcessInTreatmentPatients();

    // Processes late-arriving patients
    void processLatePatients();

    // Checks for completed treatments and frees up resources
    void checkTreatmentCompletion();

    // Checks if all patients have completed their treatments
    bool allPatientsFinished() const;

    // Prints scheduling and patient statistics
    void printStatistics() const;

    // Main simulation function
    void simulate();

    // function to generate the output file.
    void generateOutputFile();


private:
    int currentTime;
    std::string patientDataFile;
    int pCancel;   // Percentage to cancel the appointment.
    int presc;     // Percentage to resschedule the appointment.
    UI interface;   //

    

    // List of all patients.
    AllQueue allPatients;

    // Queue of ghe finished patients. 
    ArrayStack <Patient *> finishedPatients;

    // Queue of the in treatment patients.
    LinkedQueue <Patient *> inTreatmentPatients;


    // Buffers for early and late patients.
    EarlyQueue <Patient *> earlyPatients;
    priQueue   <Patient *> latePatients;

    // Resource pools for each treatment type.
    LinkedQueue <ElectroResource *> electroResources;
    LinkedQueue <UltrasoundResource *> ultrasoundResources;
    LinkedQueue <GymResource *> gymResources;

    // Queues for patients waiting for treatment.
    EU_WaitList  ElectroWaitingQueue;
    EU_WaitList  ultrasoundWaitingQueue;
    X_WaitList   gymWaitingQueue;

    // Move the patient to the finshed list.
    void moveToFinish(Patient * patient);

    // Move the  patient to the appropriate waiting list. 
    void moveToWait(Patient * patient);

    // Move the patient to the late list
    void moveToLate(Patient * patient);

    // Move the patient to the early list.
    void moveToEarly(Patient * patient);

    // Assigns an available resource to a patient
    void assignResource(Patient* patient);

    // Create the electroResources
    void createElectroResources(int num);

    // Create the ultrasound Resources
    void createUltraSoundResources(int num);

    // Create the Gym Room
    void createGymRooms(int capacity);

    // Checks if a resource of a given type is available
    bool isResourceAvailable(ResourceType type) const;

    // function to make the patient release the resource;
    bool releaseResource(Patient *patient);

    // Retrieves an available resource of a specific type
    TreatmentResource* getAvailableResource(ResourceType type);

    // Logs assignment and scheduling decisions
    void logAssignment(Patient * patient);

    //void print info
    void printinfo();



};

#endif // SCHEDULER_H
