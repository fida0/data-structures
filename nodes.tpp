//
// Created by fida on 3/19/2026.
//
#pragma once
#include "nodes.h"

// ----------- Forward Node ------------------------
template<typename T>
forwardNode<T>::forwardNode() : value(T{}), next(nullptr) {}

template<typename T>
forwardNode<T>::forwardNode(const T& val) : value(val), next(nullptr) {}


// ------------------- Double Node -------------------------
template<typename T>
doubleNode<T>::doubleNode() : value(T{}), prev(nullptr), next(nullptr) {}

template<typename T>
doubleNode<T>::doubleNode(const T& val) : value(val), prev(nullptr) ,next(nullptr){}

template<typename T>
doubleNode<T>::doubleNode(const T& val,doubleNode *prev,doubleNode *next) : value(val), prev(prev),
next(next) {}
