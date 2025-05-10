#ifndef QUEUEADT_H
#define QUEUEADT_H


// Abstract Queue interface
template<class T>
class QueueADT {
public:
    virtual bool isEmpty() const = 0;          // Check if queue is empty
    virtual bool enqueue(const T& newEntry) = 0;  // Add item to back
    virtual bool dequeue(T& FrontEntry) = 0;   // Remove item from front
    virtual bool peek(T& FrontEntry) const = 0;  // View front item
    virtual int size() const = 0;             // Get number of items
    virtual ~QueueADT() {}                    // Virtual destructor
};

#endif