#ifndef STACKADT_H
#define STACKADT_H


// Abstract Stack interface
template<typename T>
class StackADT {
public:
    virtual bool isEmpty() const = 0;      // Check if stack is empty
    virtual bool push(const T& newEntry) = 0;  // Add item to top
    virtual bool pop(T& TopEntry) = 0;     // Remove item from top
    virtual bool peek(T& TopEntry) const = 0;  // View top item
    virtual int size() const = 0;         // Get number of items
    virtual ~StackADT() {}                // Virtual destructor
};

#endif