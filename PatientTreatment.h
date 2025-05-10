// Structure to track patient treatments
#ifndef PATIENTTREATMENT_H
#define PATIENTTREATMENT_H

enum TreatmentType { E_THERAPY, U_THERAPY, X_THERAPY };  // Therapy types

struct PatientTreatment {
    TreatmentType type;      // Type of therapy
    int duration;            // Treatment duration
    bool completed;          // Completion status
    
    PatientTreatment() : type(E_THERAPY), duration(0), completed(false) {}
    PatientTreatment(TreatmentType t, int d) : type(t), duration(d), completed(false) {}
};
#endif
