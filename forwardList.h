//
// Created by fida on 3/19/2026.
//

#ifndef UNTITLED1_SINGlY_LINKED_LIST_H
#define UNTITLED1_SINGlY_LINKED_LIST_H
#include "nodes.h"

template<typename T>
class forwardList {
private:
    forwardNode<T> *head{};
    forwardNode<T> *tail{};

    void releaseLinks() { head = tail = nullptr; }

    void destroyHead() {
        if (head == nullptr) { return; }
        auto temp = head;
        if (tail == head) { tail = nullptr; }
        head = head->next;
        delete temp;
    }

    void destroyNode(forwardNode<T> *prevNode, forwardNode<T> *nodeToRemove) {
        prevNode->next = nodeToRemove->next;
        delete nodeToRemove;
    }

public:
    class Iterator {
    public:
        Iterator(forwardNode<T> *current);

        Iterator &operator++();

        Iterator operator++(int);

        T &operator*() const;

        forwardNode<T> *operator->() const;

        bool operator!=(const Iterator& other) const;

        bool operator==(const Iterator& other) const;

    private:
        forwardNode<T> *current{};
    };

public:
    forwardList();

    forwardList(const forwardList&) = delete;

    forwardList &operator=(const forwardList&) = delete;

    forwardList(forwardList&& other) noexcept;

    forwardList &operator=(forwardList&& other) noexcept;

    ~forwardList();

    bool empty() const;

    bool append(const T& value);

    void print() const;

    Iterator begin();

    Iterator end();

    Iterator begin() const;

    Iterator end() const;

    bool remove(const forwardNode<T> *node);

    int removeByValue(const T& value);

    forwardNode<T> *findByValue(const T& value);

    const forwardNode<T> *findByValue(const T& value) const;

    forwardNode<T> *findByIndex(int index);

    const forwardNode<T> *findByIndex(int index) const;

    forwardNode<T> *pop(const forwardNode<T> *node);

    bool insertAfter(const forwardNode<T> *pos, const T& value);

    bool insertBefore(const forwardNode<T> *pos, const T& value);

    void combine(forwardList& other);

    void clear();
};


#include "forwardList.tpp"
#endif //UNTITLED1_SINGlY_LINKED_LIST_H
