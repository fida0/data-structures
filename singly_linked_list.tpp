//
// Created by fida on 3/19/2026.
//
#pragma once
#include "singly_linked_list.h"
#include <iostream>

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    if (head == nullptr) { return; }
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        SinglyLinkedNode<T> *next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
bool SinglyLinkedList<T>::empty() { return head == nullptr; }

template<typename T>
bool SinglyLinkedList<T>::append(const T &value) {
    if (head == nullptr) {
        auto *newNode = new SinglyLinkedNode<T>(value);
        tail = head = newNode;
        return true;
    }
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        if (current->next == nullptr) {
            auto *newNode = new SinglyLinkedNode<T>(value);
            current->next = newNode;
            tail = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void SinglyLinkedList<T>::print() {
    std::cout << '\n';
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        std::cout << "Address: " << current << ", Value: " << current->value << std::endl;
        current = current->next;
    }
}

template<typename T>
bool SinglyLinkedList<T>::remove(const SinglyLinkedNode<T> *node) {
    SinglyLinkedNode<T> *current = head;
    SinglyLinkedNode<T> *prevNode{};
    while (current != nullptr) {
        if (current->next == node) { prevNode = current; }
        if (current == node) {
            if (current == head) {destroyHead();} else {
                if (current == tail) { tail = prevNode; }
                destroyNode(prevNode, current);
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
int SinglyLinkedList<T>::removeByValue(const T &value) {
    if (head == nullptr) {return 0;}
    if (head->value == value && head == tail) {
        destroyHead();
        return 1;
    }
    SinglyLinkedNode<T> *current = head;
    SinglyLinkedNode<T> *prev{};
    int removed{};
    while (current != nullptr) {
        if (current->value == value) {
            SinglyLinkedNode<T> *nodeToDelete = current;
            current = current->next;
            if (prev == nullptr) { head = head->next; } else { prev->next = current; }
            if (nodeToDelete == tail) { tail = prev; }
            delete nodeToDelete;
            ++removed;
        } else {
            prev = current;
            current = current->next;
        }
    }
    if (head == nullptr) { tail = nullptr; }
    return removed;
}

template<typename T>
SinglyLinkedNode<T> *SinglyLinkedList<T>::findByValue(const T &value) {
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        if (current->value == value) return current;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
SinglyLinkedNode<T> *SinglyLinkedList<T>::findByIndex(const int &index) {
    int it{};
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        if (index == it) return current;
        current = current->next;
        it++;
    }
    return nullptr;
}

template<typename T>
SinglyLinkedNode<T> *SinglyLinkedList<T>::pop(const SinglyLinkedNode<T> *node) { //TODO: differentiate from findByValue
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        if (current == node) return current;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
bool SinglyLinkedList<T>::insertAfter(const SinglyLinkedNode<T> *pos, const T &value) {
    if (pos == nullptr) { return false; }
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        if (current == pos) {
            auto newNode = new SinglyLinkedNode<T>(value);
            newNode->next = current->next;
            current->next = newNode;
            if (current == tail) { tail = newNode; }
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
bool SinglyLinkedList<T>::insertBefore(const SinglyLinkedNode<T> *pos, const T &value) {
    if (pos == nullptr) { return false; }
    if (head == pos) {
        auto *newNode = new SinglyLinkedNode<T>(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) { tail = newNode; }
        return true;
    }
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        if (current->next == pos) {
            auto newNode = new SinglyLinkedNode<T>(value);
            newNode->next = current->next;
            current->next = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void SinglyLinkedList<T>::combine(SinglyLinkedList &other) {
    if (&other == this) {return;}
    if (other.head == nullptr) { return; }
    if (head == nullptr) {
        head = other.head;
        tail = other.tail;
        other.RELEASE();
        return;
    }
    if (tail != nullptr) { tail->next = other.head; } else { head->next = other.head; }
    if (other.tail != nullptr) {
        tail = other.tail;
    } else {
        tail = other.head;
    }

    other.RELEASE();
}

template<typename T>
void SinglyLinkedList<T>::clear() {
    SinglyLinkedNode<T> *current = head;
    while (current != nullptr) {
        SinglyLinkedNode<T> *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}
