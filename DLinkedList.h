
#ifndef DLL_H
#define DLL_H
/* Doubly Linked List Implementation
//by Dr. Saleh M. Alnaeli
2021*/
#include <iostream>
using namespace std;
//------------
template <class E> class DLinkedList; /* CS244 Students: Attention: this is to
declare the DLinkedList so that compiler has no problem using it in Node class as a
friend
// it is like a prototype */
template <class E>
class DNode {     /* singly linked list node
 // provide DLinkedList access*/
public:
    E& getElem() { return elem; }; // Node does not return const, fixed issues
    DNode<E>* getNext() const { return next; };
    DNode<E>* getPrev() const { return prev; };
    E elem;     /* linked list element value*/
private:
    
    DNode<E>* next;   /* next item in the list*/
    DNode<E>* prev;   /* previous node in list*/
    friend class DLinkedList<E>;
};
//
template <class E>
class DLinkedList {    // a singly linked list
public:
    DLinkedList();    // empty list constructor
    DLinkedList(const DLinkedList<E>&); // copy costructor
    ~DLinkedList();    // destructor
    DLinkedList<E>& operator=(DLinkedList<E>&); // assignment operator
    bool empty() const;    // is list empty?
    const E& front() const;   // return front element
    const E& back() const;   // return front element
    void addFront(const E& e);   // add to front of list
    void addBack(const E& e);
    void removeFront();    // remove front item list
    void removeBack();    // remove front item list
    DNode<E>* getHead() const { return head; };   // return head address
    DNode<E>* getTail() const { return tail; };
    template <class E> friend  ostream& operator<<(ostream& os, const
        DLinkedList<E>&);
private:
    DNode<E>* head;    // head of the list
    DNode<E>* tail;    // tail of the list
protected:
    // local utilities
    void add(DNode<E>* v, const E& e); // insert new node before v
    void remove(DNode<E>* v); // remove node v
};
template <class E>
DLinkedList<E>::DLinkedList()    // constructor
{
    head = new DNode<E>;  // create sentinels
    tail = new DNode<E>;
    head->next = tail;  // have them point to each other
    tail->prev = head;
}
template <class E>
DLinkedList<E>::~DLinkedList()   // destructor
{
    while (!empty()) removeFront();
    delete head;
    delete tail;
}
template <class E>
bool DLinkedList<E>::empty()const   // is list empty?
{
    return (head->next == tail);
}
template <class E>
const E& DLinkedList<E>::front() const  // return front element
{
    return head->next->elem;
}
template <class E>
const E& DLinkedList<E>::back() const  // return front element
{
    return tail->prev->elem;
}
/*Inserting a new node into a doubly linked list. The protected utility function
add inserts a node u before an arbitrary node v. The public member functions
addFront
and addBack both invoke this utility function.*/
template <class E>
void DLinkedList<E>::add(DNode<E>* v, const E& e) {
    DNode<E>* u = new DNode<E>;
    u->elem = e; // create a new node for e
    u->next = v; // link u in between v
    u->prev = v->prev; // .. .and v->prev
    v->prev->next = u;
    v->prev = u;
}
template <class E>
void DLinkedList<E>::addFront(const E& e) {  // add to front of list
    add(head->next, e);
    //DNode<E>* v = new DNode<E>;    // create new node
    //v->elem = e;     // store data
    //v->next = head;     // head now follows v
    //head = v;
    //if (tail == NULL)
    // tail = v;// v is now the head
}
template <class E>
void DLinkedList<E>::addBack(const E& e) {  // add to back of list
    add(tail, e);
}
/* Removing a node from a doubly linked list. The local utility function remove
removes the node v.
The public member functions removeFront and removeBack invoke this utility
function.*/
template <class E>
void DLinkedList<E>::remove(DNode<E>* v) { // remove node v
    DNode<E>* u = v->prev; // predecessor
    DNode<E>* w = v->next; // successor
    u->next = w; // unlink v from list
    w->prev = u;
    delete v;
}
template <class E>
void DLinkedList<E>::removeFront() {   // remove from front item
    remove(head->next); // removes from front
}
template <class E>
void DLinkedList<E>::removeBack() {   // remove back item
    remove(tail->prev); // removes from back
}
template <class E>
DLinkedList<E>::DLinkedList(const DLinkedList<E>& obj)
{
    head = new DNode<E>;  // create sentinels
    tail = new DNode<E>;
    head->next = tail;  // have them point to each other
    tail->prev = head;
    if (obj.head != obj.tail) {
        for (DNode<E>* curr = obj.head->next;
            curr != obj.tail; curr = curr->getNext())
        {
            addBack(curr->getElem());
        }//end for
    }//end if
} // end copy constructor3
////----------------------
//overloading assignment operator
//dll1=dll2;
template <class E>
DLinkedList<E>& DLinkedList<E>::operator=(DLinkedList<E>& rhs) // assignment 
{
    if (this != &rhs) {
        //while (head != tail) // first, empty list
        // removeFront();
        while (!empty()) removeFront();
        for (DNode<E>* curr = rhs.head->getNext();
            curr != rhs.getTail(); curr = curr->getNext())
        {
            addBack(curr->getElem());
        }//end for
    }
    return *this;
} // overloading assignment
template <class E>
ostream& operator<<(ostream& os, const DLinkedList<E>& DLL) {
    os << "[";
    if (!DLL.empty()) {
        os << (DLL.head->getNext()->getElem());
        for (DNode<E>* curr = DLL.head->getNext()->getNext();
            curr != DLL.getTail(); curr = curr->getNext())
        {
            os << ", " << (curr->getElem());
        }//end for
    }
    os << "]";
    return os;
}
//-----------
#endif // !DLL_H
