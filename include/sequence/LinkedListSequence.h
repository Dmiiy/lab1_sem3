#ifndef LINKEDLISTSEQUENCE_INCLUDED
#define LINKEDLISTSEQUENCE_INCLUDED

#include "LinkedList.h"
#include "Sequence.h"
#include "../smrt_ptr/SharedPtr.h"


template<class T>
class LinkedListSequence : public Sequence<T> {
    LinkedList<T> data;  // Односвязный список

    void checkIndex(int index) const {
        if (index < 0 || index >= getLength())
            throw std::runtime_error("Index out of bounds");
    }

public:
    LinkedListSequence(T *items, int count) : data(items, count) {}

    LinkedListSequence() = default;

    explicit LinkedListSequence(const LinkedList<T> &list) : data(list) {}

    // Возвращает первый элемент последовательности
    T getFirst() const override {
        return data.getFirst();
    }

    // Возвращает последний элемент последовательности
    T getLast() const override {
        return data.getLast();
    }

    // Получает элемент по индексу
    T get(int index) const override {
        return data.get(index);
    }

    // Оператор индексации для доступа к элементам
    T operator[](int i) const {
        return data[i];
    }

    // Оператор индексации для изменения элементов
    T &operator[](int i) {
        return data[i];
    }

    // Получение подпоследовательности
    SharedPtr<Sequence<T>> getSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        auto res = SharedPtr<Sequence<T>>(static_cast<Sequence<T>*>(new LinkedListSequence<T>()));

        for (int index = startIndex; index <= endIndex; index++) {
            res->append(data.get(index));
        }
        return res; // Возвращаем умный указатель
    }

    // Возвращает длину последовательности
    int getLength() const override {
        return data.getLength();
    }

    // Добавление элемента в конец
    void append(T item) override {
        data.append(item);
    }

    // Добавление элемента в начало
    void prepend(T item) override {
        data.prepend(item);
    }

    // Вставка элемента по индексу
    void insertAt(T item, int index) override {
        data.insertAt(item, index);
    }

    // Конкатенация двух последовательностей
    SharedPtr<Sequence<T>> concat(Sequence<T> *list) override {
        auto res = SharedPtr<Sequence<T>>(static_cast<Sequence<T>*>(new LinkedListSequence<T>(*this)));

        for (int i = 0; i < list->getLength(); i++) {
            res->append(list->get(i));
        }
        return res; // Возвращаем умный указатель
    }

    // Удаление элемента по индексу
    void removeAt(int index) override {
        data.removeAt(index);
    }

    // Деструктор
    ~LinkedListSequence() override = default;

    // Применение функции к элементам последовательности
    SharedPtr<Sequence<T>> map(T (*f)(T)) const override {
        auto res = SharedPtr<Sequence<T>>(static_cast<Sequence<T>*>(new LinkedListSequence<T>));

        for (int i = 0; i < getLength(); i++) {
            res->append(f(data.get(i)));
        }
        return res; // Возвращаем умный указатель
    }

    // Фильтрация элементов последовательности
    SharedPtr<Sequence<T>> where(bool (*h)(T)) const override {
        auto res = SharedPtr<Sequence<T>>(static_cast<Sequence<T>*>(new LinkedListSequence<T>));

        for (int i = 0; i < getLength(); i++) {
            if (h(data.get(i))) {
                res->append(data.get(i));
            }
        }
        return res; // Возвращаем умный указатель
    }

    // Сведение элементов последовательности
    T reduce(T (*f)(T, T)) const override {
        T result = data.getFirst();

        for (int i = 1; i < getLength(); i++) {
            result = f(result, data.get(i));
        }
        return result;
    }
};

#endif // LINKEDLISTSEQUENCE_INCLUDED
