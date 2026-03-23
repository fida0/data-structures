//
// Created by fida on 3/19/2026.
//
#pragma once
#include "singly_linked_list.h"
#include <iostream>

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList():head(nullptr),tail(nullptr) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        SinglyLinkedNode<T>* next = current->next;
        delete current;
        current = next;
    }
}
template<typename T>
bool SinglyLinkedList<T>::empty(){return head==nullptr;}

template<typename T>
bool SinglyLinkedList<T>::append(const T& value){
    auto* newNode = new SinglyLinkedNode<T>(value);
    if (head == nullptr){head = newNode;return true;}
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (current->next == nullptr) {current->next = newNode; tail = newNode; return true;}
        current = current->next;
    }
    return false;
    // head = new SinglyLinkedNode<T>(value);
}
template<typename T>
void SinglyLinkedList<T>::print() {
    std::cout << '\n';
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        std::cout <<"Address: " << current << ", Value: " << current->value << std::endl;
        current = current->next;
    }
}
// TODO: Solve Case where head is node, tail is node, and not tail nor head is node
template<typename T>
bool SinglyLinkedList<T>::remove(const SinglyLinkedNode<T>* node) {
    SinglyLinkedNode<T>* current = head;
    SinglyLinkedNode<T>* prevNode{};
    while (current != nullptr) {
        if (current->next == node) {prevNode = current;}
        if (current == node) {
            if (current == head) {head = current->next;} else {prevNode->next = current->next;}
            delete[] current;
            return true;
        }
        current = current->next;
    }
    return false;
}
template<typename T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::findByValue(const T& value) {

    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (current->value == value) return current;
            current = current->next;
    }
    return nullptr;
}
template<typename T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::findByIndex(const int& index) {
    int it{};
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (index == it) return current;
        current = current->next;
        it++;
    }
    return nullptr;

}
template<typename T>
SinglyLinkedNode<T>* SinglyLinkedList<T>::pop(const SinglyLinkedNode<T>* node) {
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (current == node) return current;
        current = current->next;
    }
    return nullptr;
}
template<typename T>
bool SinglyLinkedList<T>::insertAfter(const SinglyLinkedNode<T>* pos, const T& value) {
    if (pos == nullptr) {return false;}
    auto newNode = new SinglyLinkedNode<T>(value);
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (current == pos) {
            newNode.next = current->next;
            current->next = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}
template<typename T>
bool SinglyLinkedList<T>::insertBefore(const SinglyLinkedNode<T>* pos, const T& value) {
    if (pos == nullptr) {return false;}
    auto newNode = new SinglyLinkedNode<T>(value);
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (current->next == pos) {
            newNode->next = pos;
            current->next = newNode;
            return true;
        }
    }
    return false;
}
template<typename T>
void SinglyLinkedList<T>::combine(SinglyLinkedList<T>& other) {
    if (other.head == nullptr) {return;}
    tail->next = other.head;
    tail = other.tail;
    other.RELEASE();
}
template<typename T>
void SinglyLinkedList<T>::clear() {
    SinglyLinkedNode<T>* current = head;
    while (current != nullptr) {
        SinglyLinkedNode<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr; tail = nullptr;
}
