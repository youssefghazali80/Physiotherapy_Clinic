#ifndef NODE_H
#define NODE_H


// Node class for Linked Queue implementation
template <typename T>
class Node {
private:
    T item;         // Data stored in node
    Node<T>* next;  // Pointer to next node
    
public:
    // Constructors
    Node() : next(nullptr) {}
    Node(const T& r_Item) : item(r_Item), next(nullptr) {}
    Node(const T& r_Item, Node<T>* nextNodePtr) : item(r_Item), next(nextNodePtr) {}
    
    // Access methods
    void setItem(const T& r_Item) { item = r_Item; }
    void setNext(Node<T>* nextNodePtr) { next = nextNodePtr; }
    T getItem() const { return item; }
    Node<T>* getNext() const { return next; }
};

#endif