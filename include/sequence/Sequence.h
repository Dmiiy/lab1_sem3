#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include "../smrt_ptr/SharedPtr.h"

template<class T>
class Sequence {
public:
    // Декомпозиция
    virtual T getFirst() const = 0;

    virtual T getLast() const = 0;

    virtual T get(int index) const = 0;

    // Перегруженные операторы для заданного индекса
    virtual T operator[](int i) const = 0;

    virtual T &operator[](int i) = 0;

    // Возвращает подпоследовательность
    virtual SharedPtr<Sequence<T>> getSubsequence(int startIndex, int endIndex) const = 0;

    virtual int getLength() const = 0;

    // Операции
    virtual void append(T item) = 0;

    virtual void prepend(T item) = 0;

    virtual void insertAt(T item, int index) = 0;

    virtual void removeAt(int index) = 0;

    // Конкатенация двух последовательностей
    virtual SharedPtr<Sequence<T>> concat(Sequence<T> *list) = 0;

    // Поиск подпоследовательности
    virtual int findSubsequence(Sequence<T> &subSequence) {
        int subSeqLen = subSequence.getLength();
        for (int start = 0; start <= getLength() - subSeqLen; start++) {
            bool match = true;
            for (int i = 0; i < subSeqLen; i++) {
                if (get(start + i) != subSequence.get(i)) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return start;
            }
        }
        return -1;
    };

    // Применение функции к элементам последовательности
    virtual SharedPtr<Sequence<T>> map(T (*f)(T)) const = 0;

    // Фильтрация элементов последовательности
    virtual SharedPtr<Sequence<T>> where(bool (*h)(T)) const = 0;

    // Сведение элементов последовательности
    virtual T reduce(T (*f)(T, T)) const = 0;

    // Деструктор
    virtual ~Sequence() = default;
};

#endif // SEQUENCE_INCLUDED
