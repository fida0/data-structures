//
// Created by fida on 3/19/2026.
//

#ifndef UNTITLED1_SINGlY_LINKED_LIST_H
#define UNTITLED1_SINGlY_LINKED_LIST_H
#include "nodes.h"

template <typename T> class SinglyLinkedList {
private:
    // std::unique_ptr<T> head;
    // std::unique_ptr<void> tail = nullptr;
    SinglyLinkedNode<T>* head;
    SinglyLinkedNode<T>* tail;

    void RELEASE() {head = {};}
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    bool empty();
    bool append(const T& value);
    void print();
    bool remove(const SinglyLinkedNode<T>* node);
    SinglyLinkedNode<T>* findByValue(const T& value);
    SinglyLinkedNode<T>* findByIndex(const int& index);
    SinglyLinkedNode<T>* pop(const SinglyLinkedNode<T>* node);
    bool insertAfter(const SinglyLinkedNode<T>* pos, const T& value);
    bool insertBefore(const SinglyLinkedNode<T>* pos, const T& value);
    void combine(SinglyLinkedList& other);
    void clear();
};



#include "singly_linked_list.tpp"
#endif //UNTITLED1_SINGlY_LINKED_LIST_H