#ifndef LIBRARYASSIGNMENT_LINKEDLIST_H
#define LIBRARYASSIGNMENT_LINKEDLIST_H

#include "Node.h"

template<typename T>
class LinkedList {
public:
    LinkedList();

    ~LinkedList();

    void AddFirst(T e);

    int GetSize() const;

    void Clear();

    T Get(int index) const;


    T GetFirst() const;

    T RemoveFirst();

    void Add(int index, T value);

    bool Contains(T element) const; // returns true if it contains the eleement
    void AddLast(T element); // adds the element to the tail
    T GetLast() const; // returns the last element in the list
    T RemoveLast(); // removes the last element and returns it's value
    bool IsEmpty() const;

    T Set(int index, T element); // sets the elemenet at specified index and returns the value being replace
private:
    Node<T> *GetNode(int index) const;

private:
    Node<T> *_head;
    Node<T> *_tail;
    int _size;
};
template<typename T>
LinkedList<T>::LinkedList() {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template<typename T>
void LinkedList<T>::AddFirst(T e) {
    Node<T> *temp = new Node<T>(e);
    temp->next = _head;
    _head = temp;
    _size++;

    if (_tail == nullptr)
        _tail = _head;
}


template<typename T>
int LinkedList<T>::GetSize() const {
    return _size;
}

template<typename T>
void LinkedList<T>::Clear() {
    while (_head != nullptr) {
        Node<T> *temp = _head;
        _head = _head->next;
        delete temp;
    }

    _tail = nullptr;
    _size = 0;
}


template<typename T>
T LinkedList<T>::Get(int index) const {
    return GetNode(index)->getElement();
}

template<typename T>
T LinkedList<T>::GetFirst() const {
    if (_size == 0)
        throw "Index out of range";
    else
        return _head->getElement();
}

template<typename T>
T LinkedList<T>::RemoveFirst() {
    if (_size == 0)
        throw "No elements in the list";
    else {
        Node<T> *temp = _head;
        _head = _head->next;

        if (_head == nullptr)
            _tail = nullptr;
        _size--;
        T element = temp->getElement();
        delete temp;
        return element;
    }
}

template<typename T>
void LinkedList<T>::Add(int index, const T value) {
    if (index == 0)
        AddFirst(value);
    else if (index >= _size)
        AddLast(value);
    else {
        Node<T> *current = _head;
        for (int i = 1; i < index; i++)
            current = current->next;
        Node<T> *temp = current->next;
        current->next = new Node<T>(value);
        (current->next)->next = temp;
        _size++;
    }
}


template<typename T>
bool LinkedList<T>::Contains(T element) const {
    Node<T>* current = _head;
    while(current != nullptr) {
        if(current->getElement() == element) return true;
        current = current->next;
    }
    return false;
}

template<typename T>
void LinkedList<T>::AddLast(T element) {
    Node<T> *temp = new Node<T>(element);
    temp->next = nullptr;
    if (_size == 0) {
        _head = temp;
    } else {
        _tail->next = temp;
    }

    _size++;
    _tail = temp;
}

template<typename T>
T LinkedList<T>::GetLast() const {
    if (_size == 0) throw "Empty List";
    return _tail->getElement();
}

template<typename T>
T LinkedList<T>::RemoveLast() {
    if (_size == 0) throw "Empty List";
    T element = _tail->getElement();
    if(_size == 1) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    } else {
        Node<T>* secondToLast = GetNode(_size - 1 - 1);
        secondToLast->next = nullptr;
        delete _tail;
        _tail = secondToLast;
    }

    _size--;
    return element;
}

template<typename T>
bool LinkedList<T>::IsEmpty() const {
    return _size == 0;
}

template<typename T>
T LinkedList<T>::Set(int index, T element) {
    Node<T>* current;
    current = GetNode(index);
    T temp = current->getElement();
    current->setElement(element);
    return temp;
}

template<typename T>
Node<T> *LinkedList<T>::GetNode(int index) const {
    if (index < 0 || index > _size - 1)
        throw "Out of range";

    Node<T> *current = _head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}

#endif //LIBRARYASSIGNMENT_LINKEDLIST_H
