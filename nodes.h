//
// Created by fida on 3/19/2026.
//

#ifndef DATA_STRUCTURES_NODES_H
#define DATA_STRUCTURES_NODES_H


template <typename T> struct SinglyLinkedNode {
    T value;
    SinglyLinkedNode* next;
    SinglyLinkedNode();
    explicit SinglyLinkedNode(const T& val);

};


#include "nodes.tpp"
#endif //DATA_STRUCTURES_NODES_H