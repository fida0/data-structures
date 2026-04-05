//
// Created by fida on 3/19/2026.
//

#ifndef DATA_STRUCTURES_NODES_H
#define DATA_STRUCTURES_NODES_H


template <typename T> struct forwardNode {
    T value;
    forwardNode* next;
    forwardNode();
    explicit forwardNode(const T& val);

};

template <typename T> struct doubleNode {
    T value;
    doubleNode* prev;
    doubleNode* next;

    doubleNode();
    explicit doubleNode(const T& val);
    explicit doubleNode(const T& val,doubleNode* prev,doubleNode* next );
};

#include "nodes.tpp"
#endif //DATA_STRUCTURES_NODES_H