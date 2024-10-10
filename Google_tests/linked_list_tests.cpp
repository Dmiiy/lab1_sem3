#include "..\include\sequence\Sequence.h"
#include "..\include\sequence\LinkedListSequence.h"

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
    auto subList = list.getSubList(1, 3);

    ASSERT_EQ(subList->getLength(), 3);
    ASSERT_EQ(subList->get(0), 2);
    ASSERT_EQ(subList->get(2), 4);

}

TEST(LinkedList, Concat) {
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5};
    LinkedList<int> list1(items1, 3);
    LinkedList<int> list2(items2, 2);
    auto result = list1.concat(&list2);

    ASSERT_EQ(result->getLength(), 8);
    ASSERT_EQ(result->get(0), 1);
    ASSERT_EQ(result->get(4), 5);

}


//LinkedListSequence

TEST(LinkedListSequence, ConstructorWithArray) {
    int arr[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(arr, 5);

    EXPECT_EQ(seq.getLength(), 5);        // Проверяем, что длина последовательности равна 5
    EXPECT_EQ(seq.getFirst(), 1);         // Проверяем первый элемент
    EXPECT_EQ(seq.getLast(), 5);          // Проверяем последний элемент
}

TEST(LinkedListSequence, Append) {
    LinkedListSequence<int> seq;
    seq.append(10);
    seq.append(20);

    EXPECT_EQ(seq.getLength(), 2);        // Проверяем длину после добавления
    EXPECT_EQ(seq[0], 10);                 // Проверяем первый элемент
    EXPECT_EQ(seq[1], 20);                 // Проверяем второй элемент
}

TEST(LinkedListSequence, Prepend) {
    LinkedListSequence<int> seq;
    seq.prepend(30);
    seq.prepend(20);

    EXPECT_EQ(seq.getLength(), 2);        // Проверяем длину после добавления
    EXPECT_EQ(seq.getFirst(), 20);        // Проверяем, что первым элементом является 20
}

TEST(LinkedListSequence, InsertAt) {
    LinkedListSequence<int> seq;
    seq.append(10);
    seq.append(30);
    seq.insertAt(20, 1); // Вставляем 20 на позицию 1

    EXPECT_EQ(seq.getLength(), 3);        // Проверяем длину после вставки
    EXPECT_EQ(seq[1], 20);                 // Проверяем, что элемент на позиции 1 - 20
}

TEST(LinkedListSequence, RemoveAt) {
    LinkedListSequence<int> seq;
    seq.append(10);
    seq.append(20);
    seq.append(30);

    seq.removeAt(1); // Удаляем элемент на позиции 1 (20)

    EXPECT_EQ(seq.getLength(), 2);        // Проверяем длину после удаления
    EXPECT_EQ(seq[1], 30);                 // Проверяем, что на позиции 1 теперь 30
}
TEST(LinkedListSequence, Concat) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    LinkedListSequence<int> seq1(arr1, 3); // Первая последовательность
    LinkedListSequence<int> seq2(arr2, 3); // Вторая последовательность

    auto concatenatedSeq = seq1.concat(&seq2); // Конкатенация двух последовательностей

    EXPECT_EQ(concatenatedSeq->getLength(), 9); // Проверяем длину результирующей последовательности
    EXPECT_EQ((*concatenatedSeq)[0], 1);         // Проверяем первый элемент
    EXPECT_EQ((*concatenatedSeq)[1], 2);         // Проверяем второй элемент
    EXPECT_EQ((*concatenatedSeq)[2], 3);         // Проверяем третий элемент
    EXPECT_EQ((*concatenatedSeq)[3], 4);         // Проверяем четвертый элемент
    EXPECT_EQ((*concatenatedSeq)[4], 5);         // Проверяем пятый элемент
    EXPECT_EQ((*concatenatedSeq)[5], 6);         // Проверяем шестой элемент
}
TEST(LinkedListSequence, GetSubsequence) {
    int arr[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(arr, 5);

    auto subseq = seq.getSubsequence(1, 3); // Получаем подпоследовательность с 1 по 3
    EXPECT_EQ(subseq->getLength(), 3);       // Проверяем длину подпоследовательности
    EXPECT_EQ((*subseq)[0], 2);               // Проверяем первый элемент подпоследовательности
    EXPECT_EQ((*subseq)[1], 3);               // Проверяем второй элемент подпоследовательности
    EXPECT_EQ((*subseq)[2], 4);               // Проверяем третий элемент подпоследовательности
}

TEST(LinkedListSequence, MapFunction) {
    int arr[] = {1, 2, 3};
    LinkedListSequence<int> seq(arr, 3);

    auto mappedSeq = seq.map([](int x) { return x * 2; }); // Умножаем каждый элемент на 2
    EXPECT_EQ(mappedSeq->getLength(), 3);
    EXPECT_EQ((*mappedSeq)[0], 2);
    EXPECT_EQ((*mappedSeq)[1], 4);
    EXPECT_EQ((*mappedSeq)[2], 6);
}

TEST(LinkedListSequence, WhereFunction) {
    int arr[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(arr, 5);

    auto filteredSeq = seq.where([](int x) { return x % 2 == 0; }); // Оставляем только четные числа
    EXPECT_EQ(filteredSeq->getLength(), 2);
    EXPECT_EQ((*filteredSeq)[0], 2);
    EXPECT_EQ((*filteredSeq)[1], 4);
}

TEST(LinkedListSequence, ReduceFunction) {
    int arr[] = {1, 2, 3, 4};
    LinkedListSequence<int> seq(arr, 4);

    int sum = seq.reduce([](int a, int b) { return a + b; }); // Суммируем все элементы
    EXPECT_EQ(sum, 10);
}