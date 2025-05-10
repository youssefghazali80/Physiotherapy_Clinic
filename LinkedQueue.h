#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "QueueADT.h"
#include "Node.h"
#include <iostream>



// Linked Queue implementation of Queue
template <typename T>
class LinkedQueue : public QueueADT<T> {
protected:
    Node<T>* backPtr;   // Pointer to back of queue
    Node<T>* frontPtr;  // Pointer to front of queue
    int itemCount;      // Track number of items
    
public:
    
    LinkedQueue() : backPtr(nullptr), frontPtr(nullptr), itemCount(0) {}
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,  const LinkedQueue<U>& queue);
    
    bool isEmpty() const override {
        return (frontPtr == nullptr);
    }

    // Add item to back of queue
    bool enqueue(const T& newEntry) override {
        Node<T>* newNodePtr = new Node<T>(newEntry);
        
        if (isEmpty()) {
            frontPtr = newNodePtr;
        } else {
            backPtr->setNext(newNodePtr);
        }
        
        backPtr = newNodePtr;
        itemCount++;
        return true;
    }

    // Remove item from front of queue
    bool dequeue(T& frntEntry) override {
        if (isEmpty()) return false;

        Node<T>* nodeToDeletePtr = frontPtr;
        frntEntry = frontPtr->getItem();
        frontPtr = frontPtr->getNext();

        if (nodeToDeletePtr == backPtr) {
            backPtr = nullptr;
        }

        delete nodeToDeletePtr;
        itemCount--;
        return true;
    }

    // View front item without removing
    bool peek(T& frntEntry) const override {
        if (isEmpty()) return false;
        frntEntry = frontPtr->getItem();
        return true;
    }

    int size() const override { return itemCount; }

    // Destructor - deletes all nodes
    ~LinkedQueue() {
        while (!isEmpty()) {
            T temp;
            dequeue(temp);
        }
    }
};


template <typename U>
std::ostream& operator<<(std::ostream& os,  const LinkedQueue<U>& queue){
        Node <U>* currentNode= queue.frontPtr; 

        while (currentNode != nullptr ) {
        os << *(currentNode->getItem());
        
        currentNode = currentNode->getNext();
        }
        os << std::endl;
        return os; 

}






#endif