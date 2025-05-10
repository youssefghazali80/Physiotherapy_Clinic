// Scheduler.cpp

#include "Scheduler.h"
#include "Patient.h"
#include "TreatmentResource.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <random>
#include <climits>
#include <fstream>
#include "UI.h"



using namespace std;

Scheduler::Scheduler(const std::string& patientDataFile,ProgramMode mode)
    : currentTime(0), patientDataFile(patientDataFile),interface(mode) {
        // Load the Data from the input file.
        loadData(patientDataFile);


}

void Scheduler::loadData(const string& input_file) {

    
    std::ifstream inFile(input_file);
    std::string line ;
    int E_num,U_num,X_num;   // Number of Electro, Ultrasound, Gym Resources.
    // The first line has the number of resources that the hospital has.
    if(std::getline (inFile,line))
    {
        std::istringstream line1(line);
        line1 >> E_num >> U_num  >> X_num;
        // Create the Electro and the UltraSound resources
        createElectroResources(E_num);
        createUltraSoundResources(U_num);

    }
    // The second line contains the capacity of the gym rooms
    if (std::getline(inFile,line))
    {
        std::istringstream line2(line);
        int capacity;
        for (int i =1; i<= X_num;i++){
            line2 >> capacity;
            createGymRooms(capacity);

        }

    }
    // The third line has the percentage of the cancelling and rescheduling
    if (std::getline(inFile,line)){
        std::istringstream line3(line);
        line3 >> pCancel >> presc;
    }
    // The fourth line has the number of patients
    int patientsNum;  // Number of all the patients.
    if (std::getline(inFile,line)){
        std::istringstream line4(line);
        line4 >> patientsNum ;
    }
    for (int i=1; i <= patientsNum ;i++){
        if (std::getline(inFile,line)){
        std::istringstream patient_line(line);
        char type ; 
        int PT ,VT,Treatment_num;
        PatientType t ;
        // Assign the type of the patient, Appointment type, And Arrival Time.
        patient_line >> type >> PT >> VT >> Treatment_num;
        // Check the type of the patient and assign it.
        if (type == 'N'){
            t = NORMAL;
        }
        else{
            t = RECOVERING;
        }
        /* Create two arrays on the heap to save the type of treatments needed and pass it to 
           to the Patient Constructor.
        */

        TreatmentType* treatment  = new TreatmentType[Treatment_num];
        int * durations = new int [Treatment_num];
        for (int j =1; j <=Treatment_num ; j++){

            char treatment_type;
            patient_line >> treatment_type ; 
            // Assign the treatment type according to the input character.
            switch (treatment_type){
                case 'E':
                    treatment[j-1]= E_THERAPY;
                    break;
                case 'U':
                    treatment[j-1]= U_THERAPY;
                    break;
                case 'X':
                    treatment[j-1]= X_THERAPY;
                    break;
                default:
                    break;       
            }
            // Assign the duartion of the treatment to pass it to the constructor of the patient.
            patient_line >> durations[j-1]; 
            

        }
        // Construct The Patient from the extracted input data.
        allPatients.enqueue(new Patient(i,t,PT,VT,treatment,durations,Treatment_num));

         
    }
        
    }



 
}

void Scheduler::processNewArrivals() 
{
    /* As the input file formatted by ascending order regarding arrival_time 
    So once i found that the first patirnt has not arrived yet so there is no need to check
    the remaning queue*/
    // Create a pointer to Patient 
    Patient * current_patient;
    // Flag to indicate that the patient we study has arrived and it is assumed to be true
    bool Arrived = true;
    while ((!allPatients.isEmpty()) && Arrived== true ){
        allPatients.peek(current_patient);
        //check if the patient has arrived or not
        if (current_patient->getVT() == currentTime)
        {
            // If the patient has arrived then decide if he/she has arrived early or late or on time.

            //  IF PT > VT (late patient)

            if (current_patient->getPT()  < currentTime)
            {
                // Move this patient to the Late list.
                moveToLate(current_patient);

            }
            else if(current_patient->getPT() > current_patient->getVT())
            {
                // Move this patient to the Early list.
                moveToEarly(current_patient);
            }
            else
            {
                // This patient has arrived on time so he/she will be moved to the waiting list.
                moveToWait(current_patient);
            }
            // Remove the patient from the All Patients list.
            allPatients.dequeue(current_patient);
    
            


        }

        else
        {
            // Assign the flag to false as there is need to check the remaning list.
            Arrived=false;
        }


    } 



}

void Scheduler::processEarlyPatients()
{
    /*
    check if the appointment time for the patients who are coming Early has come.
    As this is a priority queue sorted according to appointment time so we will be checking 
    as long as we did not find an appointmnet that hadnot come yet.

    */

    Patient * current_patient;
    // Flag to indicate that the appointment of the patient we study has come.
    bool Arrived = true;
    while ((!earlyPatients.isEmpty()) && Arrived == true ){
        int pt;
        earlyPatients.peek(current_patient,pt);
        // check if the appointment has come.
        if (pt == currentTime)
        {
            // Move the patient to the waiting patient list.
            moveToWait(current_patient);
            // remove the patient from the Early list.
            earlyPatients.dequeue(current_patient,pt);

        }
        else
        {
            Arrived=false;

        }

    }
}


void Scheduler::processLatePatients()
{
    /*
    Check if the appointment time for the patients who are coming late has come.
    As this is a priority queue sorted according to appointment time so we will be checking 
    as long as we did not find an appointmnet that had not come yet.

    Note: The new appointmnet is PT + late penalty which is equal half of the
    time that he is late. 

    */

    Patient * current_patient;
    // Flag to indicate that the appointment of the patient we study has come.
    bool Arrived = true;
    while ((!latePatients.isEmpty()) && Arrived == true ){
        int pt;
        latePatients.peek(current_patient,pt);
        // check if the appointment has come.
        if (current_patient->getVT()+current_patient->getLatePenalty() == currentTime){
            // Move the patient to the waiting patient list.
            moveToWait(current_patient);
            // Remove the patient from the Early list.
            int pt;
            latePatients.dequeue(current_patient,pt);

        }
        else{
            Arrived=false;

        }

    }
}

void Scheduler :: ProcessInTreatmentPatients()
{
    // Loop on the In treatment patients 


    // Create a pointer to the current patient
    Patient * current_patient;
    int count = inTreatmentPatients.size();
    for (int i =1; i<= count;i++)
    {
        // Remove the current patient fromt the queue.
        inTreatmentPatients.dequeue(current_patient);

        // Decrement the raming time to finsih the treatment
        current_patient->decrementRemainingTime();

        current_patient->incrementTreatmentTime();
        
        // Check if the patients has finsished the current treatment.
        if (current_patient->getRemainingTime() == 0){

            // get the finsished treatment type
            // Release the resource taken by the patient
            TreatmentType type =current_patient->getCurrentTreatmentType();
            if (type == E_THERAPY)
            {
                electroResources.enqueue( (ElectroResource*) current_patient->releaseResource() );

            }
            else if (type == U_THERAPY)
            {
                ultrasoundResources.enqueue( (UltrasoundResource *) (current_patient->releaseResource()) );
            }
            else
            {
                GymResource * gymResource = ( (GymResource *) (current_patient->releaseResource()));
                // Check if the capacity of the room was 0 so it was unavailable;
                if(gymResource->getCurrentOccupancy() == gymResource->getCapacity()){
                    // Enqueue it to the avaialabe gym resources.
                    gymResources.enqueue(gymResource);

                }
                gymResource->patientLeaved();
            }
            // Complete this Treatment.
            current_patient->completeCurrentTreatment();

            // Checks if the patient has finished all the tretaments.
            if (current_patient -> allTreatmentsDone())
            {
                // Then move this patient to finished list.
                moveToFinish(current_patient);
            }
            else
            {
                // Move this patient to the suitable waiting list.
                moveToWait(current_patient);
            }

        }
        else
        {
            inTreatmentPatients.enqueue(current_patient);
        }


    }


}

bool Scheduler::allPatientsFinished() const
{
    //check if all the lists are empty except the waiting list
    if (Patient::getPatientCount() == finishedPatients.size())
    {
        return true;
    }
    else
    {
        return false;
    }
        

}

void Scheduler::printStatistics() const {

}


void Scheduler::logAssignment(Patient * patient) {
    /*
    std::cout << "Assigned patient " << patient->getPID()
              << " to " << TreatmentResource::typeToString(patient->getResourceType())
              << " at time " << currentTime << "\n";
              */
}

void Scheduler :: processWaitingPatients(){
    // process the electro waiting queue
    Patient * patient = nullptr;
    ElectroResource * resource = nullptr;
    //  assign pateints to the available electro resources Till it is full.
    while (!electroResources.isEmpty() && !ElectroWaitingQueue.isEmpty())
    {
        // dequeu the resource from the electro resources beacuse it will be un avaialable
        electroResources.dequeue(resource);
        // dequeue the patient from the electro waiting list.
        ElectroWaitingQueue.dequeue(patient);

        // Assign this resource ot the patient.
        patient->assignResource(resource);
       
        // Change the Status of the patient to be serv
        patient->setStatus(SERV);
        // Change the current tretament type of the patient.
        patient->SetcurrentTreatment(E_THERAPY);

        patient->setRemainigtime();


        

        // move the patient to the intreatmentlist.
        inTreatmentPatients.enqueue(patient);
    }
    UltrasoundResource * ultraresource = nullptr;
    //  assign pateints to the available electro resources Till it is full.
    while (!ultrasoundResources.isEmpty() && !ultrasoundWaitingQueue.isEmpty())
    {
        //dequeu the resource from the ultrasound resources beacuse it will be un avaialable
        ultrasoundResources.dequeue(ultraresource);
        // dequeue the patient from the ultrasound waiting list.
        ultrasoundWaitingQueue.dequeue(patient);

        // Assign this resource ot the patient.
        patient->assignResource(ultraresource);

        // Change the current tretament type of the patient.
        patient->SetcurrentTreatment(U_THERAPY);
        //move the patient to the intreatmentlist.

        // Change the Status of the patient to be serv
        patient->setStatus(SERV);
        inTreatmentPatients.enqueue(patient);
        patient->setRemainigtime();
    }

    while (!gymResources.isEmpty() && !gymWaitingQueue.isEmpty())
    {
        GymResource * gymresource = nullptr;
        // Get the current gym room.
        gymResources.peek(gymresource);
        // Decrement the capacity of the gym.
        gymresource->patientEntered();
        // remove the room if it is full capacity.
        if (gymresource->getCurrentOccupancy()==gymresource->getCapacity())
        {
            gymResources.dequeue(gymresource);
        }

        // dequeue the patient from the electro waiting list.
        gymWaitingQueue.dequeue(patient);

        // Assign this resource ot the patient.
        patient->assignResource(gymresource);

        // Change the current tretament type of the patient.
        patient->SetcurrentTreatment(X_THERAPY);

        // Change the Status of the patient to be serv
        patient->setStatus(SERV);
        
        //move the patient to the intreatmentlist.
        inTreatmentPatients.enqueue(patient);

        patient->setRemainigtime();
    }

}

void Scheduler :: moveToWait(Patient * patient){
    // Change the stat of teh patient to wait
    patient->setStatus(WAIT);

    // Get The required Treatment.
    TreatmentType requiredTreatment = patient->getCurrentTreatmentType();

    // Check the type of the Patient.
    if (patient->getType() == NORMAL)
    {

        // check the type of the required treatment.
        if (requiredTreatment==E_THERAPY){
            ElectroWaitingQueue.enqueue(patient);
        }
        else if (requiredTreatment == X_THERAPY){
            gymWaitingQueue.enqueue(patient);
        }
        else {
            ultrasoundWaitingQueue.enqueue(patient);
        }
  

    }
    else 
    {
        //create an array assuing the remainf treatment types is false
        bool x[3] ={false,false,false};

        //apply the function that will convert the types remainig to true
        patient->getremainingtreatmentsTypes(x);
        //create a variable to store value to compare them
        int Electrolatency=INT_MAX;
        int Ultrasoundlatency=INT_MAX;
        int Gymlatency =INT_MAX;
        if (x[0]==true){
                Electrolatency=ElectroWaitingQueue.calcTreatmentLatency();
          
        }
        if (x[1]==true){
                Ultrasoundlatency=ultrasoundWaitingQueue.calcTreatmentLatency();
            
        }
        if (x[2]==true){
            Gymlatency = gymWaitingQueue.calcTreatmentLatency();
        }
        if (Electrolatency<Ultrasoundlatency){
            if(Electrolatency < Gymlatency){
                // electro waiting  queue has the least latency
                ElectroWaitingQueue.enqueue(patient);
            }
            else{
                // gym waiting queue has the least latency
                gymWaitingQueue.enqueue(patient);

            }
        }
        else {
            if (Ultrasoundlatency < Gymlatency){
            ultrasoundWaitingQueue.enqueue(patient);
            }
            else{
                gymWaitingQueue.enqueue(patient);

            }   
        }
        

    }
}


void Scheduler :: moveToLate(Patient * patient){
    // Change the status of the patient to be late patient.
    patient->setStatus(LATE);

    //  Set the late penalty of the patient.
    patient->setLatePenalty((currentTime-patient->getPT())/2);

    //  Insert the late patients with the new appointment assigned to it which is current time + the penalty applied to the patient.
    latePatients.enqueue(patient,patient->getLatePenalty()+currentTime);

}

void Scheduler :: moveToFinish(Patient *patient){
    // Set this patient as finished patiend

    patient->setFinishTime(currentTime);
    patient->setStatus(FNSH);

    // Push the patient to the finsihed patient stack.
    finishedPatients.push(patient);

}

void Scheduler :: moveToEarly(Patient * patient)
{

    // Set the status of the pateint to Early.
    patient->setStatus(ERLY);

    // Move the patient to the early list 
    earlyPatients.enqueue(patient,patient->getPT());

}
// The main simulation function
    // Generate the output file.
void Scheduler :: generateOutputFile(){

    std::ofstream outFile("outputfile.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << "outputfile.txt" << " for writing.\n";
        return;
    }

    int totalPatients = finishedPatients.size();
    int normalCount = 0, reschedulableCount = 0;
    int totalWT = 0, totalTT = 0;
    int wtN = 0, wtR = 0, ttN = 0, ttR = 0;
    int cancelCount = 0, reschedCount = 0;
    int earlyCount = 0, lateCount = 0;
    int latePenaltySum = 0;

    outFile << "PID   PType  PT    VT   FT   WT  TT    Cancel   Resc\n";
    Patient *patient;
    while(!finishedPatients.isEmpty()) {
        finishedPatients.pop(patient);
        std::string type = (patient->getType() == NORMAL) ? "N" : "R";
        std::string cancel = (patient->getCancelled()) ? "T" : "F";
        std::string resched = (patient->getRescheduled() )? "T" : "F";

        outFile << "P" << patient->getPID() << "      "
                << type << "         "
                << patient->getPT() << "    "
                << patient->getVT() << "    "
                << patient->getFinishTime() << "   "
                << patient->getWT() << "   "
                << patient->getTreatmentTime() << "     "
                << cancel << "            "
                << resched << "\n";

        totalWT += patient->getWT();
        totalTT += patient->getTreatmentTime();

        if (patient->getType() == NORMAL) {
            normalCount++;
            wtN += patient->getWT();
            ttN += patient->getTreatmentTime();
        } else {
            reschedulableCount++;
            wtR += patient->getWT();
            ttR += patient->getTreatmentTime();
        }

        if (patient->getCancelled()) cancelCount++;
        if (patient->getRescheduled()) reschedCount++;
        if (patient->getPT() > patient->getVT()) earlyCount++;
        if (patient->getPT() < patient->getVT()) {
            lateCount++;
            latePenaltySum += patient->getLatePenalty(); // assumes this exists
        }
    }

    outFile << "\nTotal number of timesteps = " << currentTime << "\n";
    outFile << "Total number of all, N, and R patients = " <<  totalPatients<< ", "
            << normalCount << ", " << reschedulableCount << "\n";

    outFile << "Average total waiting time for all, N, and R patients = "
            << (double)totalWT / totalPatients << ", "
            << (normalCount ? (double)wtN / normalCount : 0) << ", "
            << (reschedulableCount ? (double)wtR / reschedulableCount : 0) << "\n";

    outFile << "Average total treatment time for all, N, and R patients = "
            << (double)totalTT / totalPatients << ", "
            << (normalCount ? (double)ttN / normalCount : 0) << ", "
            << (reschedulableCount ? (double)ttR / reschedulableCount : 0) << "\n";

    outFile << "Percentage of patients of an accepted cancellation (%) = "
            << (100.0 * cancelCount / totalPatients) << " %\n";

    outFile << "Percentage of patients of an accepted rescheduling (%) = "
            << (100.0 * reschedCount / totalPatients) << " %\n";

    outFile << "Percentage of early patients (%) = "
            << (100.0 * earlyCount / totalPatients) << " %\n";

    outFile << "Percentage of late patients (%) = "
            << (100.0 * lateCount / totalPatients) << " %\n";

    outFile << "Average late penalty = "
            << (lateCount ? (double)latePenaltySum / lateCount : 0) << " timestep(s)\n";

    outFile.close();




}

void Scheduler :: createGymRooms(int capacity){
    static int count=0;
    count++;
    GymResource * gym =new GymResource(count,capacity);
    gymResources.enqueue(gym);


}

void Scheduler :: createElectroResources(int num){
    for (int i=1;i<=num;i++){
    ElectroResource * electro =new ElectroResource(i);
    electroResources.enqueue(electro);
    }
}
void Scheduler :: createUltraSoundResources(int num){
    for (int i=1;i<=num;i++)
    {
    UltrasoundResource * ultraResource =new UltrasoundResource(i);
    ultrasoundResources.enqueue(ultraResource);
    }
}





void Scheduler :: printinfo(){

    //print the current time
    std::cout << "Current Timestep: " << currentTime << std::endl;
    
    // First print the details of the not arrived patients
    interface.printAllpatientList(&allPatients);

    // Then print the all the waiting lists


    // Then print the E_Therapy waiting list
    interface.printElectroWaitingList(&ElectroWaitingQueue);
    
    // Then print the U_Therapy waiitng list
    interface.printUltraSoundWaitingList(&ultrasoundWaitingQueue);

    // Then print the X_Therapy waiting list.
    interface.printXTherapyWaitingList(&gymWaitingQueue);


    // Then print the Early list.
    interface.printEarlyList(&earlyPatients);

    // Then print the late list
    interface.printLateList(&latePatients);

    // Then print the Avaialbe E_devices;
    interface.printAvailableERersources(&electroResources);

    // Then print the Availabe U-devices;
    interface.printAvailableUResources(&ultrasoundResources);

    // Then print the avaialble x-rooms();
    interface.printAvailableXResources(&gymResources);

    // Then print the available In Treatment Patients.
    interface.printInTreatmentList(&inTreatmentPatients); 

    // Then print the finished list

    interface.printFinishedList(&finishedPatients);

    // Wait for the user to press a key.
    interface.waitForAnyKey();
    
}
void Scheduler :: simulate (){
    
    while (!allPatientsFinished()){
    currentTime++;

   
    // At first we check if any patient has arrived from the new arrival list
    processNewArrivals();

    // then we check if the appointment of any patient from the early arrivals  has come.
    processEarlyPatients();

    // then we check if the appointmnet of any patient from the late Arrivals has come
    processLatePatients();

    // then we check if any patient in treatment has finished his treatment

    ProcessInTreatmentPatients();

    // Generate a random number 
    random_device rd;                                  // Get a random seed.
    mt19937 gen(rd());                                 // Mersenne Twister generator.
    uniform_int_distribution <> dist1(0,100);          // Range [0,100]
    int percentage = dist1(gen);                       // Generate the percentage
    if (percentage < presc)
    {
        // As the random number generated is less than the prescheduling 
        // So reschedule.
        earlyPatients.reschedule();

    }
    // Generate Another random number
    percentage = dist1(gen);
    if (percentage < pCancel){
        // As the random number Generated is less than the pcancelling. 
        // So Cancel.




        Patient * cancelledPatient = gymWaitingQueue.cancel();
        if (cancelledPatient != nullptr){
            // Move the cancelled patient to the finsih list.
            moveToFinish(cancelledPatient);
        }

    }
    // Process the waiting patients.
    processWaitingPatients();
    if (interface.getMode()==INTERACTIVE){
            printinfo();
    } 
     }

    // Generate the output file.
    generateOutputFile();

}


