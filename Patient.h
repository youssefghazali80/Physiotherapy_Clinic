#ifndef PATIENT_H
#define PATIENT_H

#include "LinkedQueue.h"
#include "PatientTreatment.h"
#include "TreatmentResource.h"


#include <iostream>
using namespace std;

// Patient class representing hospital patients
enum PatientType { NORMAL, RECOVERING };  // Normal or recovering patient
enum PatientStatus { IDLE, ERLY, LATE, WAIT, SERV, FNSH };  // Current patient state



class Patient {
private:

    int PID;                                    // Patient ID
    PatientType type;                           // Normal or recovering
    int PT;                                     // Appointment Time.
    int VT;                                     // Visit time.
    PatientStatus status;                       // Current status
    LinkedQueue <PatientTreatment> treatments;   // Queue of required treatments
    int treatmentCount;                         // Number of treatments
    TreatmentType currentTreatment;             // Current treatment type
    int finishTime;                             // When current treatment finishes
    int latePenalty;                            // Penalty for late arrival
    int remainigtime;                           /* Remaining time for the patient to 
                                                    finish current treatment*/
    int totalTreatmentTime;

    TreatmentResource *treatmentResource;       // Current assigned treatment resource                                                 
    int remainingtreatments;                    // Number of remainig treatments 
    bool cancelledPatient;                      // flag to indicate if the patient has cancelled
    bool rescheduledPatient;                    // Flag to indicate if the patient has rescheduled
    static int patientNum;                      // Static variable to track the number of patients.
    

public:
    Patient();  // Default constructor

    // Initialize patient with treatments
    Patient(int id, PatientType t, int pt, int vt,TreatmentType* ttypes,int * durations, int count);

    // Access methods
    int getPID() const;
    PatientType getType() const;
    int getPT() const;
    int getVT() const;
    PatientStatus getStatus() const;
    int getTreatmentCount() const;
    TreatmentType getCurrentTreatmentType() const;
    LinkedQueue<PatientTreatment> * getTreatments() const;
    int getFinishTime()   const;
    int getLatePenalty()  const;
    bool getRescheduled() const;
    bool getCancelled()   const;
    int getRemainingTreatment() const;
    int getRemainingTime()const;
    TreatmentResource * getTretamentResource() const ;
    int getTreatmentTime()const;



    // Set methods
    void setStatus(PatientStatus s);
    void setFinishTime(int time);
    void setLatePenalty(int penalty);
    void setPT(int pt);
    void setReschedule();
    void setCancelled();
    void SetTreatmentResource(TreatmentResource * treatmentResource);
    void SetcurrentTreatment(TreatmentType treatment );
    void setRemainigtime();
    // Get the Patient count
    static int getPatientCount();

    // Get next treatment duration
    int getNextTreatment();

    // Mark current treatment as completed
    void completeCurrentTreatment();

    // Check if all treatments are done
    bool allTreatmentsDone() const;

    // Print patient information
    void printInfo() const;
    
    // Decrement the remaining time for treatment.
    void decrementRemainingTime();

    // Get the remaing treatment types
    void getremainingtreatmentsTypes(bool *x);
    
    // Assign the resource to the patient.
    void assignResource(TreatmentResource *resource);

    // Release the resource once the patient has completed tretament.
    TreatmentResource *releaseResource();

    void incrementTreatmentTime();




    int getWT();
    
    // using friendships relation to overload the <<
    friend std::ostream& operator<<(std::ostream& os, const Patient& p);




};

#endif
