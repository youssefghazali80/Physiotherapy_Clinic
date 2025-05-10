#ifndef PRIQUEUE_H
#define PRIQUEUE_H

#include "PriNode.h"
#include <iostream>

// Priority Queue implementation
template <typename T>
class priQueue {
protected:
    priNode<T>* head;      // Head of priority queue
    int itemCount;         // Number of items
    
public:
    priQueue() : head(nullptr), itemCount(0) {}

    // Add item with priority - higher priority comes first
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        itemCount++;

        // Insert at head if highest priority
        if (head == nullptr || priority < head->getPri()) {
            newNode->setNext(head);
            head = newNode;
            return;
        }

        // Find correct position in queue
        priNode<T>* current = head;
        while (current->getNext() && priority >= current->getNext()->getPri()) {
            current = current->getNext();
        }
        
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    // Remove highest priority item
    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty()) return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        itemCount--;
        return true;
    }

    // View highest priority item without removing
    bool peek(T& topEntry, int& pri) const {
        if (isEmpty()) return false;
        pri = head->getPri();
        topEntry = head->getItem();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const { return itemCount; }

    // Destructor - deletes all nodes
    ~priQueue() {
        T temp;
        int p;
        while (dequeue(temp, p));
    }
    // Add friend function declaration
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const priQueue<U>& queue);
};
template<typename U>
std::ostream& operator<<(std::ostream& os, const priQueue<U>& queue){
        priNode <U> * currentNode= queue.head; 
        for(int i =1; i<queue.size();i++){
            os << *(currentNode->getItem());    
            currentNode = currentNode->getNext();
        
        }
        return os; 

}



#endif