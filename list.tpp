//
// Created by Fida on 4/3/2026.
//
#pragma once
#include <list>


//------------------ Iterator ---------------------------------------
template<typename T>
list<T>::iterator::iterator(doubleNode<T> *c) : current(c) {}

template<typename T>
doubleNode<T>* list<T>::iterator::operator->() { //FIXME
    return this->current;
}

template<typename T>
list<T>::iterator& list<T>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}

template<typename T>
list<T>::iterator list<T>::iterator::operator++(int) {
    auto temp = *this;
    this->current = this->current->next;
    return temp;
}

template<typename T>
bool list<T>::iterator::operator!=(const iterator& other) {
    return this->current != other.current ? true : false;
}

template<typename T>
bool list<T>::iterator::operator==(const iterator& other) {
    return this->current == other.current ? true : false;
}

template<typename T>
T& list<T>::iterator::operator*() {
    return this->current->value;
}

//--------------- Const Iterator ------------------------------------
template<typename T>
list<T>::const_iterator::const_iterator(const doubleNode<T> *c) : current(c) {}

template<typename T>
const doubleNode<T>* list<T>::const_iterator::operator->() const { //FIXME
    return this->current;
}

template<typename T>
list<T>::const_iterator& list<T>::const_iterator::operator++() {
    this->current = this->current->next;
    return *this;
}

template<typename T>
list<T>::const_iterator list<T>::const_iterator::operator++(int) {
    auto temp = *this;
    this->current = this->current->next;
    return temp;
}

template<typename T>
bool list<T>::const_iterator::operator!=(const const_iterator& other) const {
    return this->current != other.current ? true : false;
}

template<typename T>
bool list<T>::const_iterator::operator==(const const_iterator& other) const {
    return this->current == other.current ? true : false;
}

template<typename T>
const T& list<T>::const_iterator::operator*() const {
    return this->current->value;
}

//-------------- Reverse Iterator -----------------------------------
template<typename T>
list<T>::reverse_iterator::reverse_iterator(doubleNode<T> *c) : current(c) {}

template<typename T>
doubleNode<T>* list<T>::reverse_iterator::operator->() { //FIXME
    return current;
}

template<typename T>
list<T>::reverse_iterator& list<T>::reverse_iterator::operator++() {
    current = current->prev;
    return *this;
}

template<typename T>
list<T>::reverse_iterator list<T>::reverse_iterator::operator++(int) {
    auto temp = *this;
    current = current->prev;
    return temp;
}

template<typename T>
list<T>::reverse_iterator& list<T>::reverse_iterator::operator--() {
    current = current->next;
    return *this;
}

template<typename T>
list<T>::reverse_iterator list<T>::reverse_iterator::operator--(int) {
    auto temp = *this;
    current = current->next;
    return temp;
}

template<typename T>
bool list<T>::reverse_iterator::operator!=(const reverse_iterator& other) const {
    return current != other.current;
}

template<typename T>
bool list<T>::reverse_iterator::operator==(const reverse_iterator& other) const {
    return current == other.current;
}

template<typename T>
T& list<T>::reverse_iterator::operator*() const {
    return current->value;
}

// ------------------- list -----------------------------------------
template<typename T>
list<T>::list() : head(nullptr), tail(nullptr) {}

template<typename T>
list<T>::list(const std::initializer_list<T>& il) {
    for (const T& value: il) {
        if (tail == nullptr) {
            auto *newNode = new doubleNode<T>(value);
            head = tail = newNode;
            ++lSize;
        } else {
            auto *newNode = new doubleNode<T>(value, tail, nullptr);
            tail->next = newNode;
            tail = newNode;
            ++lSize;
        }
    }
}

template<typename T>
list<T>::~list() {
    auto current = head;
    while (current != nullptr) {
        auto *temp = current;
        current = current->next;
        delete temp;
    }
}

template<typename T>
list<T>::iterator list<T>::begin() {
    return iterator(head);
}

template<typename T>
list<T>::iterator list<T>::end() {
    return iterator(nullptr);
}

template<typename T>
list<T>::const_iterator list<T>::cbegin() const {
    return const_iterator(head);
}

template<typename T>
list<T>::const_iterator list<T>::cend() const {
    return const_iterator(nullptr);
}

template<typename T>
list<T>::reverse_iterator list<T>::rbegin() {
    return reverse_iterator(tail);
}

template<typename T>
list<T>::reverse_iterator list<T>::rend() {
    return reverse_iterator(nullptr);
}

template<typename T>
T& list<T>::front() { return head->value; }

template<typename T>
T& list<T>::back() { return tail->value; }

template<typename T>
int list<T>::size() const { return lSize; }

template<typename T>
bool list<T>::empty() const { return lSize == 0; }

template<typename T>
void list<T>::clear() {
    if (!lSize) { return; }
    auto current = head;
    while (current != nullptr) {
        auto *temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    lSize = 0;
}

template<typename T>
list<T>::iterator list<T>::insert(const_iterator pos, const T& value) {
    auto prevNode = pos.current->prev;
    auto *newNode = new doubleNode<T>(value, prevNode, pos.current);
    pos.current->prev = newNode;
    if (prevNode) {
        prevNode->next = newNode;
    } else {
        head = newNode;
    }
    return iterator(newNode);
}

template<typename T>
void list<T>::append(const T& value) { //todo range
    if (lSize == 0) {
        head = tail = new doubleNode<T>(value);
    } else {
        tail->next = new doubleNode<T>(value, tail, nullptr);
        tail = tail->next;
    }
    ++lSize;
}

template<typename T>
void list<T>::prepend(const T& value) { //todo range
    if (lSize == 0) {
        head = tail = new doubleNode<T>(value);
    } else {
        head->prev = new doubleNode<T>(value, nullptr, head);
        head = head->prev;
    }
    ++lSize;
}

template<typename T>
list<T>::iterator list<T>::erase(iterator pos) {
    auto prevNode = pos.current->prev;
    auto nextNode = pos.current->next;
    if (prevNode) {
        prevNode->next = nextNode;
    } else {
        head = nextNode;
    }
    if (nextNode) {
        nextNode->prev = prevNode;
    } else {
        tail = prevNode;
    }
    delete pos.current;
    --lSize;
    return iterator(nextNode);
}

template<typename T>
void list<T>::push_back(const T& value) {
    if (lSize == 0) {
        head = tail = new doubleNode<T>(value);
    } else {
        tail->next = new doubleNode<T>(value, tail, nullptr);
        tail = tail->next;
    }
    ++lSize;
}

template<typename T>
std::optional<T> list<T>::pop_back() {
    if (tail == nullptr) { return std::nullopt; }
    auto *temp = tail;
    T value = temp->value;
    tail = tail->prev;
    if (tail != nullptr) { tail->next = nullptr; } else { tail = head = nullptr; }
    delete temp;
    --lSize;
    return value;
}

template<typename T>
void list<T>::push_front(const T& value) {
    if (lSize == 0) {
        head = tail = new doubleNode<T>(value);
    } else {
        head->prev = new doubleNode<T>(value, head, nullptr);
        head = head->prev;
    }
    ++lSize;
}

template<typename T>
std::optional<T> list<T>::pop_front() {
    if (head == nullptr) { return std::nullopt; }
    //if there is one element in the list then we must not run the -> operator on nullptr
    auto *temp = head;
    T value = temp->value;
    head = temp->next;
    if (head != nullptr) { head->prev = nullptr; } else { head = tail = nullptr; }
    delete temp;
    --lSize;
    return value;
}

template<typename T>
void list<T>::resize(int n) {
    if (n < 0 || lSize == n) { return; }
    while (lSize > n) {
        auto temp = tail;
        tail = tail->prev;
        if (tail != nullptr) { tail->next = nullptr; } else { head = nullptr; }
        delete temp;
        --lSize;
    }
    while (lSize < n) {
        auto newNode = new doubleNode<T>(T(), tail, nullptr);
        if (tail != nullptr) { tail->next = newNode; } else { head = newNode; }
        tail = newNode;
        ++lSize;
    }
}

template<typename T>
void list<T>::resize(int n, T value) {
    if (n < 0 || lSize == n) { return; }
    while (lSize > n) {
        auto temp = tail;
        tail = tail->prev;
        if (tail != nullptr) { tail->next = nullptr; } else { head = nullptr; }
        delete temp;
        --lSize;
    }
    while (lSize < n) {
        auto newNode = new doubleNode<T>(value, tail, nullptr);
        if (tail != nullptr) { tail->next = newNode; } else { head = newNode; }
        tail = newNode;
        ++lSize;
    }
}
