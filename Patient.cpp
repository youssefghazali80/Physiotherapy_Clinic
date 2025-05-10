#include "Patient.h"


// Static variable definition and initialization
int Patient::patientNum = 0;  // Initialize static variable to 0

// Default constructor
Patient::Patient() : PID(0), type(NORMAL), PT(0), VT(0), status(IDLE),
                     treatmentCount(0), currentTreatment(E_THERAPY), finishTime(0), latePenalty(0) {}

// Initialize patient with treatments
Patient::Patient(int id, PatientType t, int pt, int vt, TreatmentType* ttypes,int * durations, int count) :
    PID(id), type(t), PT(pt), VT(vt), status(IDLE),cancelledPatient(false),rescheduledPatient(false),
    treatmentCount(count), currentTreatment(ttypes[0]), finishTime(0), latePenalty(0),remainingtreatments(count),
    totalTreatmentTime(0)
     {

    for (int i = 0; i < count; i++) {
        treatments.enqueue(PatientTreatment(ttypes[i], durations[i]));
    }
    patientNum++;   // increment the number of patients created.
}

// Access methods.
int Patient::getPID() const { return PID; }
PatientType Patient::getType() const { return type; }
int Patient::getPT() const { return PT; }
int Patient::getVT() const { return VT; }
PatientStatus Patient::getStatus() const { return status; }
int Patient::getTreatmentCount() const { return treatmentCount; }
TreatmentType Patient::getCurrentTreatmentType() const { return currentTreatment; }
int Patient::getFinishTime() const { return finishTime; }
int Patient::getLatePenalty() const { return latePenalty; }
bool Patient ::getRescheduled() const{return rescheduledPatient;}
bool Patient :: getCancelled() const{return cancelledPatient;}
int Patient :: getRemainingTreatment() const{return remainingtreatments;}
int Patient :: getRemainingTime()const{return remainigtime;}
TreatmentResource * Patient:: getTretamentResource() const { return treatmentResource;}
int Patient :: getTreatmentTime()const{return totalTreatmentTime;}


// Set methods.
void Patient::setStatus(PatientStatus s) { status = s; }
void Patient::setFinishTime(int time) { finishTime = time; }
void Patient::setLatePenalty(int penalty) { latePenalty = penalty; }
void Patient::setPT(int pt)    { PT = pt; }
void Patient ::setReschedule() {rescheduledPatient =true;}
void Patient::setCancelled()   {cancelledPatient =true;}
void Patient ::SetcurrentTreatment(TreatmentType treatment){currentTreatment=treatment;}


// set the remainig time to the duration of the current treatment
void Patient :: setRemainigtime(){
    PatientTreatment t ;
    for (int i =1;i<=treatmentCount;i++){
        treatments.dequeue(t);
        if (t.type == currentTreatment){
            remainigtime = t.duration;
        }
        treatments.enqueue(t);
    }

}



// Get next treatment duration
int Patient::getNextTreatment() {
    PatientTreatment t;
    if (treatments.peek(t) && !t.completed) {
        currentTreatment = t.type;
        return t.duration;
    }
    return -1;  // No more treatments
}

// Mark current treatment as completed
void Patient::completeCurrentTreatment() {
    PatientTreatment t;
    for (int i=0;i<treatmentCount;i++){
        treatments.dequeue(t);
        if (t.type==currentTreatment){
            t.completed=true;

        }
        treatments.enqueue(t);
    }
    remainingtreatments--;
    if(!allTreatmentsDone())
    {
        bool found = false;    // Find the next required treatment.
        while(!found){
            treatments.peek(t);
            if (t.completed==false){
                currentTreatment =t.type;
                found=true;
            }
            else{
                treatments.dequeue(t);
                treatments.enqueue(t);
            }
        }  



    }

}

// Check if all treatments are done
bool Patient::allTreatmentsDone() const {
    if (remainingtreatments ==0){
        return true;
    }
    else{
        return false;
    }
}

// Print patient information
void Patient::printInfo() const {
    cout << "PID: " << PID << ", Type: " << (type == NORMAL ? "N" : "R")
         << ", PT: " << PT << ", VT: " << VT << ", Status: ";
    switch(status) {
        case IDLE: cout << "IDLE"; break;
        case ERLY: cout << "ERLY"; break;
        case LATE: cout << "LATE"; break;
        case WAIT: cout << "WAIT"; break;
        case SERV: cout << "SERV"; break;
        case FNSH: cout << "FNSH"; break;
    }
    cout << ", Treatments: [";

    // Print treatment queue
    LinkedQueue<PatientTreatment> temp = treatments;
    PatientTreatment t;
    bool first = true;
    while (temp.dequeue(t)) {
        if (!first) cout << ", ";
        cout << (t.type == E_THERAPY ? "E" : (t.type == U_THERAPY ? "U" : "X")) 
             << ":" << t.duration;
        if (t.completed) cout << "(done)";
        first = false;
    }
    cout << "]";
    if (status == SERV) cout << ", Finishes at: " << finishTime;
    if (status == LATE) cout << ", Penalty: " << latePenalty;
    cout << endl;
}

int Patient::getPatientCount() {
    return patientNum;
}
void Patient ::decrementRemainingTime(){
    remainigtime --;
}
// function that gets array of boolean as parameter and sets the the corresponding remaing 
// treatment to true.
void Patient:: getremainingtreatmentsTypes(bool *x){
    PatientTreatment t  ;
    for (int i=1;i<=treatments.size();i++){
        treatments.dequeue(t);
        if (!t.completed){
            x[t.type] =true;

        }
        treatments.enqueue(t);

    }
    
}

// Assign the Resource to the patient.
void Patient :: assignResource(TreatmentResource *resource){
    treatmentResource = resource;
    remainigtime = getNextTreatment();


}

// Release the resource once the patient has completed tretament.
TreatmentResource * Patient:: releaseResource(){
    TreatmentResource * temp = treatmentResource;
    treatmentResource =nullptr;
    return temp;
}
void Patient ::incrementTreatmentTime(){
    totalTreatmentTime ++;
    }
// gets the waiting time.    
int Patient :: getWT(){
    return getFinishTime()-getVT()- getTreatmentTime();
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
    switch (p.getStatus()){
        case IDLE:
            os << "P" << p.getPID() << "_" << p.getVT()<<", ";
            break;
        case WAIT:
            os << p.getPID()<<", " ;
            break;
        case ERLY :
            os << p.getPID()<<", " ;
            break;
        case SERV:
            os << "P" << p.getPID() << "_" ;
            switch(p.getCurrentTreatmentType())
            {
                case E_THERAPY:
                    os<< "E"<<p.getTretamentResource()->getID()<< " ,";
                    break;
                case U_THERAPY :
                    os <<"U"<<p.getTretamentResource()->getID()<< " ,";
                    break;
                case X_THERAPY:
                    os <<"X" <<p.getTretamentResource()->getID()<<" ,";
                    break; 
                default:
                    break;       

            }
            break;
        case FNSH:
            os << p.getPID()<<", " ;
            break;
        case LATE:
            os << p.getPID()<<", " ;
            break;

        default:
            break;    
    }
    return os;
}
