#ifndef LIBRARYASSIGNMENT_NODE_H
#define LIBRARYASSIGNMENT_NODE_H

template<typename T>
class Node {
public:
    Node *next;

    Node() {
        next = nullptr;
    }

    explicit Node(T element);

    T getElement() const;

    void setElement(T e);

private:
    T element;
};

template<typename T>
void Node<T>::setElement(T e) {
    element = e;
}

template<typename T>
T Node<T>::getElement() const {
    return element;
}

template<typename T>
Node<T>::Node(T element) {
    this->element = element;
    next = nullptr;
}


#endif //LIBRARYASSIGNMENT_NODE_H
