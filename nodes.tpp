//
// Created by fida on 3/19/2026.
//
#pragma once
#include "nodes.h"

template<typename T>
SinglyLinkedNode<T>::SinglyLinkedNode():value(T{}),next(nullptr) {}

template<typename T>
SinglyLinkedNode<T>::SinglyLinkedNode(const T& val):value(val), next(nullptr) {}
