#ifndef PRINODE_H
#define PRINODE_H

template <typename T>   

// Priority Node for priority queue 
class priNode {
private:
    T item;         // Data item
    int pri;        // Priority value
    priNode<T>* next;  // Next node pointer
    
public:
    priNode(const T& r_Item, int PRI) : item(r_Item), pri(PRI), next(nullptr) {}
    
    void setItem(const T& r_Item, int PRI) { item = r_Item; pri = PRI; }
    void setNext(priNode<T>* nextNodePtr) { next = nextNodePtr; }
    T getItem(int& PRI) const { PRI = pri; return item; }
    T getItem() const { return item; }
    priNode<T>* getNext() const { return next; }
    int getPri() const { return pri; }
};






#endif