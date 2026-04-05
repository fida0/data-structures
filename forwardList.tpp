//
// Created by fida on 3/19/2026.
//
#pragma once
#include "forwardList.h"
#include <iostream>

// template<typename T>
// using ForwardList = forwardList<forwardNode<T>>;

// Iterator implementations
template<typename T>
using Iterator = forwardList<T>::Iterator;

template<typename T>
forwardList<T>::Iterator::Iterator(forwardNode<T> *current) : current(current) {}

template<typename T>
forwardList<T>::Iterator &forwardList<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template<typename T>
forwardList<T>::Iterator forwardList<T>::Iterator::operator++(int) {
    Iterator old = *this;
    ++(*this);
    return old;
}

template<typename T>
T &forwardList<T>::Iterator::operator*() const {
    return current->value;
}

template<typename T>
forwardNode<T> *forwardList<T>::Iterator::operator->() const {
    return current;
}

template<typename T>
bool forwardList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template<typename T>
bool forwardList<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

// List implementations
template<typename T>
forwardList<T>::Iterator forwardList<T>::begin() { return Iterator(head); }

template<typename T>
forwardList<T>::Iterator forwardList<T>::end() { return Iterator(nullptr); }

template<typename T>
forwardList<T>::Iterator forwardList<T>::begin() const { return Iterator(head); }

template<typename T>
forwardList<T>::Iterator forwardList<T>::end() const { return Iterator(nullptr); }


template<typename T>
forwardList<T>::forwardList() : head(nullptr), tail(nullptr) {}

template<typename T>
forwardList<T>::forwardList(forwardList&& other) noexcept : head(other.head), tail(other.tail) {
    other.releaseLinks();
}

template<typename T>
forwardList<T> &forwardList<T>::operator=(forwardList&& other) noexcept {
    if (this == &other) { return *this; }
    clear();
    head = other.head;
    tail = other.tail;
    other.releaseLinks();
    return *this;
}

template<typename T>
forwardList<T>::~forwardList() {
    clear();
}

template<typename T>
bool forwardList<T>::empty() const { return head == nullptr; }

template<typename T>
bool forwardList<T>::append(const T& value) {
    auto *newNode = new forwardNode<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    return true;
}

template<typename T>
void forwardList<T>::print() const {
    std::cout << '\n';
    const forwardNode<T> *current = head;
    while (current != nullptr) {
        std::cout << "Address: " << current << ", Value: " << current->value << std::endl;
        current = current->next;
    }
}


template<typename T>
bool forwardList<T>::remove(const forwardNode<T> *node) {
    if (node == nullptr || head == nullptr) { return false; }
    forwardNode<T> *current = head;
    forwardNode<T> *prevNode = nullptr;
    while (current != nullptr) {
        if (current == node) {
            if (current == head) {
                destroyHead();
            } else {
                if (current == tail) { tail = prevNode; }
                destroyNode(prevNode, current);
            }
            return true;
        }
        prevNode = current;
        current = current->next;
    }
    return false;
}

template<typename T>
int forwardList<T>::removeByValue(const T& value) {
    if (head == nullptr) { return 0; }
    if (head->value == value && head == tail) {
        destroyHead();
        return 1;
    }
    forwardNode<T> *current = head;
    forwardNode<T> *prev{};
    int removed{};
    while (current != nullptr) {
        if (current->value == value) {
            forwardNode<T> *nodeToDelete = current;
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
forwardNode<T> *forwardList<T>::findByValue(const T& value) {
    forwardNode<T> *current = head;
    while (current != nullptr) {
        if (current->value == value) { return current; }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
const forwardNode<T> *forwardList<T>::findByValue(const T& value) const {
    const forwardNode<T> *current = head;
    while (current != nullptr) {
        if (current->value == value) { return current; }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
forwardNode<T> *forwardList<T>::findByIndex(int index) {
    if (index < 0) { return nullptr; }
    int it{};
    forwardNode<T> *current = head;
    while (current != nullptr) {
        if (index == it) { return current; }
        current = current->next;
        it++;
    }
    return nullptr;
}

template<typename T>
const forwardNode<T> *forwardList<T>::findByIndex(int index) const {
    if (index < 0) { return nullptr; }
    int it{};
    const forwardNode<T> *current = head;
    while (current != nullptr) {
        if (index == it) { return current; }
        current = current->next;
        it++;
    }
    return nullptr;
}

template<typename T>
forwardNode<T> *forwardList<T>::pop(const forwardNode<T> *node) {
    // Non-mutating lookup by pointer identity.
    forwardNode<T> *current = head;
    while (current != nullptr) {
        if (current == node) { return current; }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
bool forwardList<T>::insertAfter(const forwardNode<T> *pos, const T& value) {
    if (pos == nullptr) { return false; }
    forwardNode<T> *current = head;
    while (current != nullptr) {
        if (current == pos) {
            auto newNode = new forwardNode<T>(value);
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
bool forwardList<T>::insertBefore(const forwardNode<T> *pos, const T& value) {
    if (pos == nullptr) { return false; }
    if (head == pos) {
        auto *newNode = new forwardNode<T>(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) { tail = newNode; }
        return true;
    }
    forwardNode<T> *current = head;
    while (current != nullptr) {
        if (current->next == pos) {
            auto newNode = new forwardNode<T>(value);
            newNode->next = current->next;
            current->next = newNode;
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void forwardList<T>::combine(forwardList& other) {
    if (&other == this) { return; }
    if (other.head == nullptr) { return; }
    if (head == nullptr) {
        head = other.head;
        tail = other.tail;
        other.releaseLinks();
        return;
    }
    tail->next = other.head;
    tail = other.tail;
    other.releaseLinks();
}

template<typename T>
void forwardList<T>::clear() {
    forwardNode<T> *current = head;
    while (current != nullptr) {
        forwardNode<T> *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}
