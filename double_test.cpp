//
// Created by Fida on 4/4/2026.
//
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "list.h"

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

static bool listMatches(list<int>& l, const std::vector<int>& expected) {
    std::size_t index = 0;
    for (auto it = l.begin(); it != l.end(); ++it, ++index) {
        if (index >= expected.size() || *it != expected[index]) {
            return false;
        }
    }
    return index == expected.size();
}

int main() {
    TestRunner tr;

    // constructor + empty + size
    {
        list<int> l;
        tr.check(l.empty(), "constructor creates empty list");
        tr.check(l.size() == 0, "size is 0 on new list");
    }

    // append + front/back + iteration order
    {
        list<int> l;
        l.append(10);
        l.append(20);
        l.append(30);

        tr.check(!l.empty(), "list not empty after append");
        tr.check(l.size() == 3, "size after append");
        tr.check(l.front() == 10, "front after append");
        tr.check(l.back() == 30, "back after append");
        tr.check(listMatches(l, {10, 20, 30}), "iterator order after append");
    }

    // prepend + mixed prepend/append
    {
        list<int> l;
        l.prepend(2);
        l.prepend(1);
        l.append(3);
        l.append(4);

        tr.check(l.size() == 4, "size after prepend + append");
        tr.check(l.front() == 1 && l.back() == 4, "front/back after mixed insertions");
        tr.check(listMatches(l, {1, 2, 3, 4}), "order after mixed insertions");
    }

    // iterator operator-> smoke (checks bidirectional link shape indirectly)
    {
        list<int> l;
        l.append(5);
        l.append(6);
        l.append(7);

        auto it = l.begin();
        bool ok = true;
        ok = ok && (it->prev == nullptr);
        ++it;
        ok = ok && (it->prev != nullptr && it->prev->value == 5);
        ++it;
        ok = ok && (it->prev != nullptr && it->prev->value == 6);
        tr.check(ok, "iterator-> exposes expected prev links");
    }

    // pop_front / pop_back on empty
    {
        list<int> l;
        tr.check(!l.pop_front().has_value(), "pop_front on empty returns nullopt");
        tr.check(!l.pop_back().has_value(), "pop_back on empty returns nullopt");
    }

    // pop_front / pop_back normal + single-element transitions
    {
        list<int> l;
        l.append(1);
        l.append(2);
        l.append(3);

        auto a = l.pop_front();
        auto b = l.pop_back();
        tr.check(a.has_value() && a.value() == 1, "pop_front returns first value");
        tr.check(b.has_value() && b.value() == 3, "pop_back returns last value");
        tr.check(l.size() == 1 && l.front() == 2 && l.back() == 2, "state after front+back pops");

        auto c = l.pop_back();
        tr.check(c.has_value() && c.value() == 2, "pop_back on single element returns value");
        tr.check(l.empty() && l.size() == 0, "single-element pop resets to empty");
    }

    // clear + reuse
    {
        list<int> l;
        l.append(9);
        l.append(8);
        l.clear();

        tr.check(l.empty() && l.size() == 0, "clear empties list");

        l.append(42);
        l.prepend(21);
        tr.check(listMatches(l, {21, 42}), "list usable after clear");
    }

    // initializer_list constructor
    {
        list<int> l{3, 4, 5};
        tr.check(l.size() == 3, "initializer_list size");
        tr.check(l.front() == 3 && l.back() == 5, "initializer_list front/back");
        tr.check(listMatches(l, {3, 4, 5}), "initializer_list preserves order");
    }

    std::cout << "\nPassed: " << tr.passed
              << "\nFailed: " << tr.failed
              << "\nTotal : " << (tr.passed + tr.failed) << '\n';

    return tr.failed == 0 ? 0 : 1;
}
