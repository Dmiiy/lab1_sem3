#include "..\include\sequence\Sequence.h"
#include "..\include\sequence\LinkedListSequence.h"
#include "..\include\sequence\LinkedList.h"

#include "lib/googletest/include/gtest/gtest.h"

TEST(LinkedList, BasicOperations) {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.prepend(0);

    ASSERT_EQ(list.getFirst(), 0);
    ASSERT_EQ(list.getLast(), 2);
    ASSERT_EQ(list.getLength(), 3);

}

TEST(LinkedList, InsertAt) {
    LinkedList<int> list;
    list.append(1);
    list.append(3);
    list.insertAt(2, 1);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);


}

TEST(LinkedList, RemoveAt) {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.removeAt(1);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.getLength(), 2);
}

TEST(LinkedList, GetSubList) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(items, 5);
    LinkedList<int> *subList = list.getSubList(1, 3);

    ASSERT_EQ(subList->getLength(), 3);
    ASSERT_EQ(subList->get(0), 2);
    ASSERT_EQ(subList->get(2), 4);

    delete subList; // не забываем очистить память
}

TEST(LinkedList, Concat) {
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5};
    LinkedList<int> list1(items1, 3);
    LinkedList<int> list2(items2, 2);

    LinkedList<int> *result = list1.concat(&list2);

    ASSERT_EQ(result->getLength(), 8);
    ASSERT_EQ(result->get(0), 1);
    ASSERT_EQ(result->get(4), 5);

    delete result;
}

//LinkedListSequence

TEST(LinkedListSequence, RemoveAt) {
    LinkedListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    seq.append(3);
    seq.removeAt(1);

    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 3);
    ASSERT_EQ(seq.getLength(), 2);
}

TEST(LinkedListSequence, GetSubsequence) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);
    Sequence<int> *subSeq = seq.getSubsequence(1, 3);

    ASSERT_EQ(subSeq->getLength(), 3);
    ASSERT_EQ(subSeq->get(0), 2);
    ASSERT_EQ(subSeq->get(2), 4);

    delete subSeq;
}

TEST(LinkedListSequence, Concat) {
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5};
    LinkedListSequence<int> seq1(items1, 3);
    LinkedListSequence<int> seq2(items2, 2);

    Sequence<int> *result = seq1.concat(&seq2);

    ASSERT_EQ(result->getLength(), 8);
    ASSERT_EQ(result->get(0), 1);
    ASSERT_EQ(result->get(4), 5);

    delete result;
}

TEST(LinkedListSequence, Map) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);

    Sequence<int> *mapped = seq.map([](int x) { return x * 2; });

    ASSERT_EQ(mapped->get(0), 2);
    ASSERT_EQ(mapped->get(4), 10);

    delete mapped;
}

TEST(LinkedListSequence, Where) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);

    Sequence<int> *filtered = seq.where([](int x) { return x % 2 == 0; });

    ASSERT_EQ(filtered->getLength(), 2);
    ASSERT_EQ(filtered->get(0), 2);
    ASSERT_EQ(filtered->get(1), 4);

    delete filtered;
}

TEST(LinkedListSequence, Reduce) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);

    int result = seq.reduce([](int a, int b) { return a + b; });

    ASSERT_EQ(result, 15);
}

TEST(LinkedListSequence, findSubsequence) {
    int data[] = {11, 22, 33, 44, 55};
    Sequence<int> *main = new LinkedListSequence<int>(data, _countof(data));
    ASSERT_EQ(5, main->getLength());
    ASSERT_EQ(11, main->get(0));
    ASSERT_EQ(22, main->get(1));
    ASSERT_EQ(33, main->get(2));
    ASSERT_EQ(44, main->get(3));
    ASSERT_EQ(55, main->get(4));


    {
        int d[] = {22, 33};
        Sequence<int> *sub = new LinkedListSequence<int>(d, _countof(d));
        ASSERT_EQ(2, sub->getLength());
        ASSERT_EQ(22, sub->get(0));
        ASSERT_EQ(33, sub->get(1));
        ASSERT_EQ(1, main->findSubsequence(*sub));
        delete sub;
    }


    delete main;
}

TEST(LinkedListSequence, operations) {
    auto *list = new LinkedListSequence<int>();  // Список целых чисел
    // Пока что список пуст
    ASSERT_EQ(0, list->getLength());
    // Пытаемся получить первый элемент на пустом списке
    try {
        list->getFirst();
        FAIL();
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }
    // Пытаемся получить последний элемент на пустом списке
    try {
        list->getLast();
        FAIL();
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }
    // Добавляем первый элемент
    list->append(11);
    ASSERT_EQ(1, list->getLength());
    ASSERT_EQ(11, list->getFirst());
    ASSERT_EQ(11, list->getLast());
    // Добавляем второй элемент в начало списка
    list->append(22);
    ASSERT_EQ(2, list->getLength());
    ASSERT_EQ(11, list->getFirst());
    ASSERT_EQ(22, list->getLast());
    list->append(33);
    list->append(44);
    // Подсписок извлекаем
    Sequence<int> *sub = list->getSubsequence(1, 2);
    ASSERT_EQ(2, sub->getLength());
    ASSERT_EQ(22, sub->get(0));
    ASSERT_EQ(33, sub->get(1));
    // Добавляем ещё в начало элемент
    sub->prepend(-100);
    ASSERT_EQ(3, sub->getLength());
    ASSERT_EQ(-100, sub->getFirst());
    delete sub;
    delete list;
}

TEST(LinkedListSequence, create_list_from_array) {
    wstring items[3] = {L"first", L"second", L"third"};
    LinkedListSequence<wstring> list(items, 3);
    ASSERT_EQ(3, list.getLength());
    ASSERT_EQ(wstring(L"first"), list.get(0));
    ASSERT_EQ(wstring(L"second"), list.get(1));
    ASSERT_EQ(wstring(L"third"), list.get(2));
    ASSERT_EQ(wstring(L"first"), list[0]);
    ASSERT_EQ(wstring(L"second"), list[1]);
    ASSERT_EQ(wstring(L"third"), list[2]);

    LinkedListSequence<wstring> copy(list);
    ASSERT_EQ(6, copy.getLength());
    ASSERT_EQ(wstring(L"first"), copy.getFirst());
    ASSERT_EQ(wstring(L"first"), copy.get(0));
    ASSERT_EQ(wstring(L"second"), copy.get(1));
    ASSERT_EQ(wstring(L"third"), copy.get(2));
    ASSERT_EQ(wstring(L"third"), copy.getLast());
}

TEST(LinkedListSequence, insertAt) {
    wstring items[3] = {L"first", L"second", L"third"};
    Sequence<wstring> *list = new LinkedListSequence<wstring>(items, 3);
    ASSERT_EQ(3, list->getLength());
    ASSERT_EQ(wstring(L"first"), list->get(0));
    ASSERT_EQ(wstring(L"second"), list->get(1));
    ASSERT_EQ(wstring(L"third"), list->get(2));
    // Вставляем элемент после "first"
    list->insertAt(L"test", 1);
    ASSERT_EQ(4, list->getLength());
    ASSERT_EQ(wstring(L"first"), list->get(0));
    ASSERT_EQ(wstring(L"test"), list->get(1));
    ASSERT_EQ(wstring(L"second"), list->get(2));
    ASSERT_EQ(wstring(L"third"), list->get(3));
    delete list;
}




