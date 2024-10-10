//#include <QApplication>
//#include <QWidget>
//#include <QVBoxLayout>
//#include <QHBoxLayout>
//#include <QLabel>
//#include <QLineEdit>
//#include <QPushButton>
//#include <QTextEdit>
//#include <QMessageBox>
//#include <QInputDialog>
//
//#include "sequence/LinkedList.h"  // Подключите ваш класс LinkedList
//
//class LinkedListApp : public QWidget {
//    //Q_OBJECT
//
//public:
//    LinkedListApp(QWidget *parent = nullptr) : QWidget(parent) {
//        setWindowTitle("Работа с односвязным списком");
//        setFixedSize(1400, 800);
//        setStyleSheet("background-color: #f0f0f0;");
//
//        QVBoxLayout *mainLayout = new QVBoxLayout(this);
//
//        // Поле ввода для элемента списка
//        QHBoxLayout *inputLayout = new QHBoxLayout();
//        QLabel *elementLabel = new QLabel("Элемент:");
//        inputLayout->addWidget(elementLabel);
//
//        elementInput = new QLineEdit();
//        elementInput->setFixedWidth(500);
//        inputLayout->addWidget(elementInput);
//
//        QPushButton *addElementButton = new QPushButton("Добавить элемент");
//        connect(addElementButton, &QPushButton::clicked, this, &LinkedListApp::addElement);
//        inputLayout->addWidget(addElementButton);
//
//        mainLayout->addLayout(inputLayout);
//
//        // Кнопки для операций
//        QHBoxLayout *buttonLayout = new QHBoxLayout();
//
//        QPushButton *addToEndButton = new QPushButton("Добавить в конец");
//        connect(addToEndButton, &QPushButton::clicked, this, &LinkedListApp::addToEnd);
//        buttonLayout->addWidget(addToEndButton);
//
//        QPushButton *addToStartButton = new QPushButton("Добавить в начало");
//        connect(addToStartButton, &QPushButton::clicked, this, &LinkedListApp::addToStart);
//        buttonLayout->addWidget(addToStartButton);
//
//        QPushButton *insertAtButton = new QPushButton("Вставить по индексу");
//        connect(insertAtButton, &QPushButton::clicked, this, &LinkedListApp::insertAt);
//        buttonLayout->addWidget(insertAtButton);
//
//        QPushButton *removeAtButton = new QPushButton("Удалить по индексу");
//        connect(removeAtButton, &QPushButton::clicked, this, &LinkedListApp::removeAt);
//        buttonLayout->addWidget(removeAtButton);
//
//        QPushButton *getFirstButton = new QPushButton("Получить первый элемент");
//        connect(getFirstButton, &QPushButton::clicked, this, &LinkedListApp::getFirst);
//        buttonLayout->addWidget(getFirstButton);
//
//        QPushButton *getLastButton = new QPushButton("Получить последний элемент");
//        connect(getLastButton, &QPushButton::clicked, this, &LinkedListApp::getLast);
//        buttonLayout->addWidget(getLastButton);
//
//        QPushButton *getAtIndexButton = new QPushButton("Получить элемент по индексу");
//        connect(getAtIndexButton, &QPushButton::clicked, this, &LinkedListApp::getAtIndex);
//        buttonLayout->addWidget(getAtIndexButton);
//
//        QPushButton *clearListButton = new QPushButton("Очистить список");
//        connect(clearListButton, &QPushButton::clicked, this, &LinkedListApp::clearList);
//        buttonLayout->addWidget(clearListButton);
//
//        QPushButton *getLengthButton = new QPushButton("Получить длину");
//        connect(getLengthButton, &QPushButton::clicked, this, &LinkedListApp::getLength);
//        buttonLayout->addWidget(getLengthButton);
//
//        QPushButton *getSublistButton = new QPushButton("Получить подсписок");
//        connect(getSublistButton, &QPushButton::clicked, this, &LinkedListApp::getSublist);
//        buttonLayout->addWidget(getSublistButton);
//
//        mainLayout->addLayout(buttonLayout);
//
//        // Поле для отображения элементов списка
//        QLabel *listLabel = new QLabel("Элементы списка:");
//        mainLayout->addWidget(listLabel);
//
//        listDisplay = new QTextEdit();
//        listDisplay->setReadOnly(true);
//        mainLayout->addWidget(listDisplay);
//
//        // Инициализация списка
//        linkedList = new LinkedList<QString>();
//    }
//
//private slots:
//    void addElement() {
//        QString element = elementInput->text();
//        if (!element.isEmpty()) {
//            linkedList->append(element);
//            elementInput->clear();
//            updateListDisplay();
//        } else {
//            QMessageBox::warning(this, "Ошибка", "Введите элемент для добавления.");
//        }
//    }
//
//    void addToEnd() {
//        // Добавить в конец
//        QString element = elementInput->text();
//        if (!element.isEmpty()) {
//            linkedList->append(element);
//            elementInput->clear();
//            updateListDisplay();
//        } else {
//            QMessageBox::warning(this, "Ошибка", "Введите элемент для добавления.");
//        }
//    }
//
//    void addToStart() {
//        // Добавить в начало
//        QString element = elementInput->text();
//        if (!element.isEmpty()) {
//            linkedList->prepend(element);
//            elementInput->clear();
//            updateListDisplay();
//        } else {
//            QMessageBox::warning(this, "Ошибка", "Введите элемент для добавления.");
//        }
//    }
//
//    void insertAt() {
//        bool ok;
//        int index = QInputDialog::getInt(this, "Вставить по индексу", "Индекс:", 0, 0, linkedList->getLength(), 1, &ok);
//        if (ok) {
//            QString element = elementInput->text();
//            if (!element.isEmpty()) {
//                linkedList->insertAt(element, index);
//                elementInput->clear();
//                updateListDisplay();
//            } else {
//                QMessageBox::warning(this, "Ошибка", "Введите элемент для добавления.");
//            }
//        }
//    }
//
//    void removeAt() {
//        bool ok;
//        int index = QInputDialog::getInt(this, "Удалить по индексу", "Индекс:", 0, 0, linkedList->getLength() - 1, 1, &ok);
//        if (ok) {
//            try {
//                linkedList->removeAt(index);
//                updateListDisplay();
//            } catch (const IndexOutOfRange &e) {
//                QMessageBox::warning(this, "Ошибка", e.what());
//            }
//        }
//    }
//
//    void getFirst() {
//        try {
//            QString firstElement = linkedList->getFirst();
//            QMessageBox::information(this, "Первый элемент", "Первый элемент: " + firstElement);
//        } catch (const IndexOutOfRange &e) {
//            QMessageBox::warning(this, "Ошибка", e.what());
//        }
//    }
//
//    void getLast() {
//        try {
//            QString lastElement = linkedList->getLast();
//            QMessageBox::information(this, "Последний элемент", "Последний элемент: " + lastElement);
//        } catch (const IndexOutOfRange &e) {
//            QMessageBox::warning(this, "Ошибка", e.what());
//        }
//    }
//
//    void getAtIndex() {
//        bool ok;
//        int index = QInputDialog::getInt(this, "Получить элемент по индексу", "Индекс:", 0, 0, linkedList->getLength() - 1, 1, &ok);
//        if (ok) {
//            try {
//                QString element = linkedList->get(index);
//                QMessageBox::information(this, "Элемент по индексу", "Элемент: " + element);
//            } catch (const IndexOutOfRange &e) {
//                QMessageBox::warning(this, "Ошибка", e.what());
//            }
//        }
//    }
//
//    void clearList() {
//        linkedList->clear();
//        updateListDisplay();
//    }
//
//    void getLength() {
//        int length = linkedList->getLength();
//        QMessageBox::information(this, "Длина списка", "Длина списка: " + QString::number(length));
//    }
//
//    void getSublist() {
//        bool ok1, ok2;
//        int startIndex = QInputDialog::getInt(this, "Получить подсписок", "Начальный индекс:", 0, 0, linkedList->getLength() - 1, 1, &ok1);
//        int endIndex = QInputDialog::getInt(this, "Получить подсписок", "Конечный индекс:", startIndex, startIndex, linkedList->getLength() - 1, 1, &ok2);
//        if (ok1 && ok2) {
//            try {
//                auto sublist = linkedList->getSubList(startIndex, endIndex);
//                QString result;
//                for (int i = 0; i < sublist->getLength(); ++i) {
//                    result += sublist->get(i) + "\n";
//                }
//                QMessageBox::information(this, "Подсписок", result);
//            } catch (const IndexOutOfRange &e) {
//                QMessageBox::warning(this, "Ошибка", e.what());
//            }
//        }
//    }
//
//private:
//    void updateListDisplay() {
//        listDisplay->clear();
//        for (int i = 0; i < linkedList->getLength(); ++i) {
//            listDisplay->append(linkedList->get(i));
//        }
//    }
//
//    QLineEdit *elementInput;
//    QTextEdit *listDisplay;
//    LinkedList<QString> *linkedList;
//};
//
//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//    LinkedListApp window;
//    window.show();
//    return app.exec();
//}
