#include <iostream>
#include "singly_linked_list.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SinglyLinkedList<int> n1;
    n1.append(5);
    n1.append(2);
    n1.append(4);
    n1.append(7);
    n1.print();
    /*const auto nodeAtFive = n1.findByValue(5);
    n1.remove(nodeAtFive);
    n1.remove(n1.findByIndex(9));*/
    n1.print();

    SinglyLinkedList<int> n2;
    n2.append(1);
    n2.append(1);
    n2.append(1);
    n2.append(1);
    n2.append(1);
    n2.append(1);
    n2.append(1);

    std::cout << "n2 before combination: ";
    n2.print();
    n1.combine(n2);
    std::cout << "This is n1's print: ";
    n1.print();
    std::cout << "This is n2's print: ";
    n2.print();

    n1.clear();
    std::cout << "n1 post clear: "<< std::endl;
    n1.print();
    return 0;
}
