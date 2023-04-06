#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  List() : first(nullptr), last(nullptr), numSize(0){}

  ~List(){
    clear();
  }

  List(const List<T>&other) : first(nullptr), last(nullptr), numSize(0){
    copy_all(other);
  }

  List<T> & operator=(const List<T> &rhs){
    if(this == &rhs){
      return *this;
    }
    clear();
    copy_all(rhs);
    return *this;
  }


  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return numSize;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *n = new Node;
    n->datum = datum;
    n->prev = nullptr;
    if(empty()){
      first = last = n;
      n->next = nullptr;
    }
    else{
      n->next = first;
      first->prev = n;
      first = n;
    }
    numSize++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *n = new Node;
    n->datum = datum;
    n->next = nullptr;
    if(empty()){
      first = last = n;
      n->prev = nullptr;
    }
    else{
      n->prev = last;
      last->next = n;
      last = n;
    }
    numSize++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    Node *ptr1 = first;
    if(first==last){
      first = last = nullptr;
    }
    else{
      first = first->next;
      first->prev = nullptr;
    }
    delete ptr1;
    numSize--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    if(first==last){
      delete first;
      first = last = nullptr;
    }
    else{
      Node *ptr1 = last;
      last = ptr1->prev;
      last -> next = nullptr;
      delete ptr1;
    }
    numSize--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    while(!empty()){
      pop_front();
    }
    numSize = 0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(Node *n = other.first; n; n = n->next){
      push_back(n->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int numSize;

public:
  ////////////////////////////////////////
  class Iterator {
    friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator():node_ptr(nullptr){};
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*()const{
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator & operator++(){ 
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const{
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const{
      return !(node_ptr == rhs.node_ptr);
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here



    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p):node_ptr(p){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    if(first == last){
      first = last = nullptr;
    }
    else if(i.node_ptr == first){
      first = i.node_ptr->next;
      first->prev = nullptr;
    }
    else if(i.node_ptr == last){
      last = i.node_ptr->prev;
      last->next = nullptr;
    }
    else{
      (i.node_ptr->prev)->next = i.node_ptr->next;
      (i.node_ptr->next)->prev = i.node_ptr->prev;
    }
    delete i.node_ptr;
    numSize--;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    if(i == first){
      push_front(datum);
    }
    else if(i == end()){
      push_back(datum);
    }
    else{
      Node *n = new Node;
      (i.node_ptr->prev)->next = n;
      n->prev = i.node_ptr->prev;
      i.node_ptr->prev = n;
      n->next = i.node_ptr;
      n->datum = datum;
      numSize++;
    }
  }

};//List


/////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
