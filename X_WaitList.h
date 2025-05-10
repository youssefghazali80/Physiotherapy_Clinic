#ifndef X_WAITLIST_H
#define X_WAITLIST_H

#include "EU_WaitList.h"


class X_WaitList : public EU_WaitList{

    public :
    //add cancel function

    Patient * cancel();
};







#endif