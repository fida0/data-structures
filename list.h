//
// Created by Fida on 4/3/2026.
//@noFormat

#ifndef DATA_STRUCTURES_LIST_H
#define DATA_STRUCTURES_LIST_H
#include "nodes.h"
#include <initializer_list>
#include <optional>

template<class T>
class list {
private:
    doubleNode<T> *head{};
    doubleNode<T> *tail{};
    int lSize{};

    // ---------------- Iterator Class -------------------------
public:
    class iterator {
    public:
        explicit iterator(doubleNode<T> *c);

        doubleNode<T>* operator->(); //FIXME

        iterator& operator++();


        iterator operator++(int);

        //TODO add -- pre and post
        bool operator!=(const iterator& other);

        bool operator==(const iterator& other);

        T& operator*();

    private:
        doubleNode<T> *current{};
    };

    //--------------- Const Iterator ------------------------------------
public:
    class const_iterator {
    public:
        explicit const_iterator(const doubleNode<T> *c);

        const doubleNode<T>* operator->() const; //FIXME
        const_iterator& operator++();

        const_iterator operator++(int);

        //TODO add -- pre and post
        bool operator!=(const const_iterator& other) const;

        bool operator==(const const_iterator& other) const;

        const T& operator*() const;

    private:
        const doubleNode<T> *current{};
    };

    //-------------- Reverse Iterator -----------------------------------
public:
    class reverse_iterator {
    public:
        explicit reverse_iterator(doubleNode<T> *c);

        doubleNode<T>* operator->(); //FIXME

        reverse_iterator& operator++();

        reverse_iterator operator++(int);

        reverse_iterator& operator--();

        reverse_iterator operator--(int);

        bool operator!=(const reverse_iterator& other) const;

        bool operator==(const reverse_iterator& other) const;

        T& operator*() const;

    private:
        doubleNode<T> *current{};
    };

    // ------------- Public Implementation ---------------------
public:
    list();

    list(const std::initializer_list<T>& il);

    ~list();

    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    reverse_iterator rbegin();

    reverse_iterator rend();

    T& front();

    T& back();

    [[nodiscard]] int size() const;

    [[nodiscard]] bool empty() const;

    void clear();

    void append(const T& value); //todo range

    void prepend(const T& value); //todo range

    iterator erase(iterator pos);

    iterator insert(const_iterator pos, const T& value);

    void push_back(const T& value);

    std::optional<T> pop_back();

    void push_front(const T& value);

    std::optional<T> pop_front();

    void resize(int n);

    void resize(int n, T value);
};


#include "list.tpp"
#endif //DATA_STRUCTURES_LIST_H
