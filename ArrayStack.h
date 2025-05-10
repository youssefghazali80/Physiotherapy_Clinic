#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "StackADT.h"

// Array-based Stack implementation
template<typename T>
class ArrayStack : public StackADT<T> {
protected:
    enum { MAX_SIZE = 1000 };  // Maximum stack size
    T items[MAX_SIZE];        // Array to store items
    int top;                  // Index of top item
    
public:

    ArrayStack() : top(-1) {}

    bool isEmpty() const override {
        return top == -1;
    }

    // Add item to top of stack
    bool push(const T& newEntry) override {
        if (top == MAX_SIZE - 1) return false;  // Stack full
        items[++top] = newEntry;
        return true;
    }

    // Remove item from top of stack
    bool pop(T& TopEntry) override {
        if (isEmpty()) return false;
        TopEntry = items[top--];
        return true;
    }

    // View top item without removing
    bool peek(T& TopEntry) const override {
        if (isEmpty()) return false;
        TopEntry = items[top];
        return true;
    }

    int size() const override {
        return top + 1;
    }


    template<typename U>
    friend std::ostream& operator<<(std::ostream& os,  const ArrayStack<U>& stack);
};
template<typename U>
std::ostream& operator<<(std::ostream& os,  const ArrayStack<U>& stack){


        for (int i = stack.size()-1;i>=0;i--){
            os << *(stack.items[i]);
        }
        os << endl;
        return os; 

}


#endif