#ifndef TREATMENTRESOURCE_H
#define TREATMENTRESOURCE_H
// Base class for treatment resource


class TreatmentResource {
protected:
    int id;          // Resource identifier
    bool available;  // Availability status
    
public:
    TreatmentResource(int i) ;
    virtual ~TreatmentResource() ;
    
    int getID() const;
    virtual bool isAvailable() const;
    virtual void setAvailable(bool avail) ;
};


#endif