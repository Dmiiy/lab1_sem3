#ifndef LINKEDLIST_INCLUDED
#define LINKEDLIST_INCLUDED

#include <iostream>
#include "SeqExc.h"
#include "../smrt_ptr/SharedPtr.h"

template<class T>
class LinkedList {
    struct Node {
        T value;
        SharedPtr<Node> next;

        Node(T value, SharedPtr<Node> next = nullptr) : value(value), next(next) {}
    };

    SharedPtr<Node> first = nullptr;
    SharedPtr<Node> last = nullptr;
    int size = 0;

public:
    LinkedList(T *items, int count) {
        for (int i = 0; i < count; i++) {
            append(items[i]);
        }
    }

    LinkedList() = default;

    LinkedList(const LinkedList<T> &list) : size(list.size) {
        SharedPtr<Node> current = list.first;
        while (current.get()) {
            append(current->value);
            current = current->next;
        }
    }

    ~LinkedList() = default;

    T getFirst() const {
        if (!first.get()) throw IndexOutOfRange("List is empty");
        return first->value;
    }

    T getLast() const {
        if (!last.get()) throw IndexOutOfRange("List is empty");
        return last->value;
    }

    void clear() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    T &get(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange("Index out of range");
        }

        SharedPtr<Node> current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    T operator[](int i) const {
        return get(i);
    }

    T &operator[](int i) {
        return get(i);
    }

    LinkedList<T> *getSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= size)
            throw IndexOutOfRange("Invalid index range");

        SharedPtr<Node> current = first;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        }

        auto *subList = new LinkedList<T>();
        for (int i = startIndex; i <= endIndex; i++) {
            subList->append(current->value);
            current = current->next;
        }
        return subList;
    }

    int getLength() const {
        return size;
    }

    void append(const T &value) {
        auto newNode = SharedPtr<Node>(new Node(value, nullptr));

        if (!first.get()) {
            first = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }

        size++;
    }


    void prepend(T item) {
        auto newNode = SharedPtr<Node>(new Node(item, first));
        if (!first.get()) {
            last = newNode;
        }
        first = newNode;
        size++;
    }

    void insertAt(T item, int index) {
        if (index < 0 || index > size)
            throw IndexOutOfRange("Index out of range");

        if (index == 0) {
            prepend(item);
            return;
        }

        SharedPtr<Node> current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        auto newNode = SharedPtr<Node>(new Node(item, current->next));
        current->next = newNode;

        if (index == size) {
            last = newNode;
        }

        size++;
    }

    LinkedList<T> *concat(LinkedList<T> *list) const {
        auto *result = new LinkedList<T>(*this);
        SharedPtr<Node> current = list->first;

        while (current.get()) {
            result->append(current->value);  // Метод append должен увеличивать size
            current = current->next;
        }

        return result;
    }


    void removeAt(int index) {
        if (index < 0 || index >= size)
            throw IndexOutOfRange("Index out of range");

        // Если удаляем первый элемент
        if (index == 0) {
            SharedPtr<Node> node_to_replace = first->next;
            first = node_to_replace;
            if (!first.get()) {
                last = nullptr;
            }
            size--;
            return;
        }


        SharedPtr<Node> current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }


        SharedPtr<Node> nodeToRemove = current->next;
        current->next = nodeToRemove->next;


        if (index == size - 1) {
            last = current;
        }

        size--;
    }


};

#endif