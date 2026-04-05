#include <iostream>
#include <string>
#include <vector>
#include "forwardList.h"

struct TestRunner {
    int passed = 0;
    int failed = 0;

    void check(bool condition, const std::string& name) {
        if (condition) {
            ++passed;
            std::cout << "[PASS] " << name << '\n';
        } else {
            ++failed;
            std::cout << "[FAIL] " << name << '\n';
        }
    }
};

static bool listMatches(forwardList<int>& list, const std::vector<int>& expected) {
    for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
        auto *node = list.findByIndex(i);
        if (node == nullptr || node->value != expected[i]) {
            return false;
        }
    }
    return list.findByIndex(static_cast<int>(expected.size())) == nullptr;
}

int main() {
    TestRunner tr;

    // constructor + empty + clear
    {
        forwardList<int> list;
        tr.check(list.empty(), "constructor creates empty list");
        list.clear();
        tr.check(list.empty(), "clear on empty list");
        list.clear();
        tr.check(list.empty(), "clear is idempotent");
    }

    // append + print smoke test
    {
        forwardList<int> list;
        tr.check(list.append(10), "append first element");
        tr.check(list.append(20), "append second element");
        tr.check(!list.empty(), "list not empty after append");
        tr.check(listMatches(list, {10, 20}), "append preserves order");
        list.print(); // smoke test: should not crash
        tr.check(true, "print smoke test");
    }

    // findByValue + findByIndex + pop
    {
        forwardList<int> list;
        list.append(4);
        list.append(7);
        list.append(9);

        auto *node7 = list.findByValue(7);
        tr.check(node7 != nullptr && node7->value == 7, "findByValue found");
        tr.check(list.findByValue(99) == nullptr, "findByValue not found");

        auto *idx0 = list.findByIndex(0);
        auto *idx2 = list.findByIndex(2);
        tr.check(idx0 != nullptr && idx0->value == 4, "findByIndex first");
        tr.check(idx2 != nullptr && idx2->value == 9, "findByIndex last valid");
        tr.check(list.findByIndex(3) == nullptr, "findByIndex out of range");
        tr.check(list.findByIndex(-1) == nullptr, "findByIndex negative");

        tr.check(list.pop(node7) == node7, "pop found pointer");
        forwardNode<int> outsideNode(123);
        tr.check(list.pop(&outsideNode) == nullptr, "pop node not in list");
        tr.check(list.pop(nullptr) == nullptr, "pop nullptr");
    }

    // remove (head, middle, tail, null, not found)
    {
        forwardList<int> list;
        list.append(1);
        list.append(2);
        list.append(3);
        list.append(4);

        tr.check(!list.remove(nullptr), "remove nullptr returns false");

        auto *headNode = list.findByIndex(0);
        tr.check(list.remove(headNode), "remove head");
        tr.check(listMatches(list, {2, 3, 4}), "state after removing head");

        auto *middleNode = list.findByValue(3);
        tr.check(list.remove(middleNode), "remove middle");
        tr.check(listMatches(list, {2, 4}), "state after removing middle");

        auto *tailNode = list.findByValue(4);
        tr.check(list.remove(tailNode), "remove tail");
        tr.check(listMatches(list, {2}), "state after removing tail");

        forwardNode<int> outsideNode(777);
        tr.check(!list.remove(&outsideNode), "remove node not in list");
    }

    // removeByValue (zero, one, many, all)
    {
        forwardList<int> list;
        tr.check(list.removeByValue(5) == 0, "removeByValue on empty list");

        list.append(1);
        list.append(2);
        list.append(2);
        list.append(3);
        list.append(2);

        tr.check(list.removeByValue(9) == 0, "removeByValue no matches");
        tr.check(listMatches(list, {1, 2, 2, 3, 2}), "state unchanged when no matches");

        tr.check(list.removeByValue(3) == 1, "removeByValue one match");
        tr.check(listMatches(list, {1, 2, 2, 2}), "state after removing one match");

        tr.check(list.removeByValue(2) == 3, "removeByValue many matches");
        tr.check(listMatches(list, {1}), "state after removing many matches");

        tr.check(list.removeByValue(1) == 1, "removeByValue removes all remaining");
        tr.check(list.empty(), "list empty after removing all");
    }

    // insertAfter (valid, tail, null, not found)
    {
        forwardList<int> list;
        list.append(1);
        list.append(3);

        auto *one = list.findByValue(1);
        tr.check(list.insertAfter(one, 2), "insertAfter valid middle position");
        tr.check(listMatches(list, {1, 2, 3}), "state after insertAfter middle");

        auto *tail = list.findByValue(3);
        tr.check(list.insertAfter(tail, 4), "insertAfter tail");
        tr.check(listMatches(list, {1, 2, 3, 4}), "state after insertAfter tail");

        tr.check(!list.insertAfter(nullptr, 99), "insertAfter nullptr position");

        forwardNode<int> outsideNode(500);
        tr.check(!list.insertAfter(&outsideNode, 99), "insertAfter node not in list");
    }

    // insertBefore (valid, head, null, not found, empty list)
    {
        forwardList<int> list;
        list.append(1);
        list.append(2);
        list.append(3);

        tr.check(!list.insertBefore(nullptr, 99), "insertBefore nullptr position");

        auto *two = list.findByValue(2);
        tr.check(list.insertBefore(two, 99), "insertBefore valid middle position");
        tr.check(listMatches(list, {1, 99, 2, 3}), "state after insertBefore middle");

        auto *head = list.findByIndex(0);
        tr.check(list.insertBefore(head, 0), "insertBefore head");
        tr.check(listMatches(list, {0, 1, 99, 2, 3}), "state after insertBefore head");

        forwardNode<int> outsideNode(800);
        tr.check(!list.insertBefore(&outsideNode, 77), "insertBefore node not in list");

        forwardList<int> emptyList;
        tr.check(!emptyList.insertBefore(&outsideNode, 10), "insertBefore on empty list");
    }

    // combine (all combinations)
    {
        forwardList<int> a;
        forwardList<int> b;
        b.append(7);
        b.append(8);

        a.combine(b);
        tr.check(listMatches(a, {7, 8}), "combine empty + non-empty moves nodes");
        tr.check(b.empty(), "combine releases other list when moved");

        forwardList<int> c;
        c.append(1);
        c.append(2);
        forwardList<int> d;

        c.combine(d);
        tr.check(listMatches(c, {1, 2}), "combine non-empty + empty keeps original");
        tr.check(d.empty(), "combine with empty other keeps other empty");

        forwardList<int> e;
        forwardList<int> f;
        e.combine(f);
        tr.check(e.empty() && f.empty(), "combine empty + empty");

        forwardList<int> g;
        g.append(1);
        forwardList<int> h;
        h.append(2);
        h.append(3);
        g.combine(h);
        tr.check(listMatches(g, {1, 2, 3}), "combine non-empty + non-empty appends correctly");
        tr.check(h.empty(), "combine non-empty + non-empty empties other");
    }

    // destructor scope test (no explicit assert, but ensures code path is exercised)
    {
        forwardList<int> scoped;
        scoped.append(11);
        scoped.append(22);
    }
    tr.check(true, "destructor scope exit smoke test");

    std::cout << "\nPassed: " << tr.passed
            << "\nFailed: " << tr.failed
            << "\nTotal : " << (tr.passed + tr.failed) << '\n';

    return tr.failed == 0 ? 0 : 1;
}
