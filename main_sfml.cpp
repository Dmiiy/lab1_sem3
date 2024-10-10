#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>
// Включаем вашу реализацию LinkedList
#include "sequence/LinkedList.h"

class GUI {
public:
    GUI() {
        // Создание окна
        window.create(sf::VideoMode(800, 620), "Linked List");
        window.setFramerateLimit(60);

        // Загрузка шрифта
        if (!font.loadFromFile("../include/fonts/arial.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }

        // Настройка текста информации
        infoText.setFont(font);
        infoText.setCharacterSize(18);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(20, 550);

        // Поле для ввода данных
        inputBox.setSize(sf::Vector2f(200, 30));
        inputBox.setPosition(20, 510);
        inputBox.setFillColor(sf::Color::White);
        inputText.setFont(font);
        inputText.setCharacterSize(18);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(25, 515);

        // Кнопки
        setupButton(addStartButton, addStartText, "Add to Start", 20, 50);
        setupButton(addEndButton, addEndText, "Add to End", 20, 100);
        setupButton(insertButton, insertText, "Insert at Index", 20, 150);
        setupButton(deleteButton, deleteText, "Delete at Index", 20, 200);
        setupButton(getElementButton, getElementText, "Get Element by Index", 20, 250);
        setupButton(sublistButton, sublistText, "Get Sublist", 20, 300);
        setupButton(concatButton, concatText, "Concat Lists", 20, 350);
        setupButton(clearButton, clearText, "Clear List", 20, 400);
        setupButton(exitButton, exitText, "Exit", 20, 450);
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text infoText;
    sf::RectangleShape inputBox;
    sf::Text inputText;
    std::string userInput;

    // Кнопки и текст кнопок
    sf::RectangleShape addStartButton, addEndButton, insertButton, deleteButton, getElementButton, sublistButton, concatButton, clearButton, exitButton;
    sf::Text addStartText, addEndText, insertText, deleteText, getElementText, sublistText, concatText, clearText, exitText;

    LinkedList<int> list;  // Экземпляр вашего списка

    // Структура для хранения состояния кнопок
    struct ButtonState {
        bool isClicked = false;
        sf::Color originalColor;
        sf::Color clickedColor;
    };

    std::map<sf::RectangleShape *, ButtonState> buttonStates;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!userInput.empty())
                        userInput.pop_back();
                } else if (event.text.unicode < 128) {
                    userInput += static_cast<char>(event.text.unicode);
                }
                inputText.setString(userInput);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (isButtonClicked(addStartButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleAddToStart();
                    changeButtonColor(addStartButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(addEndButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleAddToEnd();
                    changeButtonColor(addEndButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(insertButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleInsertAtIndex();
                    changeButtonColor(insertButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(deleteButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleDeleteAtIndex();
                    changeButtonColor(deleteButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(getElementButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleGetElementAtIndex();
                    changeButtonColor(getElementButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(sublistButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleGetSublist();
                    changeButtonColor(sublistButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(concatButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleConcatLists();
                    changeButtonColor(concatButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(clearButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleClearList();
                    changeButtonColor(clearButton, sf::Color(66, 170, 255));
                } else if (isButtonClicked(exitButton, event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                }
            }
        }
    }

    void setupButton(sf::RectangleShape &button, sf::Text &buttonText, const std::string &text, float x, float y) {
        button.setSize(sf::Vector2f(170, 30));
        button.setPosition(x, y);
        button.setFillColor(sf::Color(11, 11, 100));

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(16);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(x + 10, y + 5);

        // Запоминаем состояние кнопки
        buttonStates[&button] = {false, sf::Color(11, 11, 100), sf::Color(66, 170, 255)};
    }

    bool isButtonClicked(const sf::RectangleShape &button, float x, float y) {
        return button.getGlobalBounds().contains(x, y);
    }

    void changeButtonColor(sf::RectangleShape &button, const sf::Color &color) {
        button.setFillColor(color);

        // Запускаем поток для возврата цвета через 300 мс
        std::thread([this, &button]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            button.setFillColor(buttonStates[&button].originalColor);
        }).detach();
    }

    // --- Обработчики событий ---
    void handleAddToStart() {
        try {
            int value = std::stoi(userInput);
            list.prepend(value);
            infoText.setString("Element added to start");
            userInput.clear();
            inputText.setString(userInput);
        } catch (std::exception &e) {
            infoText.setString("Invalid input for Add to Start");
        }
    }

    void handleAddToEnd() {
        try {
            int value = std::stoi(userInput);
            list.append(value);
            infoText.setString("Element added to end");
            userInput.clear();
            inputText.setString(userInput);
        } catch (std::exception &e) {
            infoText.setString("Invalid input for Add to End");
        }
    }

    void handleInsertAtIndex() {
        try {
            std::istringstream iss(userInput);
            int value, index;
            if (iss >> value >> index) {
                list.insertAt(value, index);
                infoText.setString("Element inserted at index " + std::to_string(index));
                userInput.clear();
                inputText.setString(userInput);
            } else {
                throw std::invalid_argument("Invalid input");
            }
        } catch (std::exception &e) {
            infoText.setString("Invalid input for Insert at Index");
        }
    }

    void handleDeleteAtIndex() {
        try {
            int index = std::stoi(userInput);
            list.removeAt(index);
            infoText.setString("Element at index " + std::to_string(index) + " deleted");
            userInput.clear();
            inputText.setString(userInput);
        } catch (std::exception &e) {
            infoText.setString("Invalid index for Delete");
        }
    }

    void handleGetElementAtIndex() {
        try {
            int index = std::stoi(userInput);
            int value = list.get(index);
            infoText.setString("Element at index " + std::to_string(index) + ": " + std::to_string(value));
            userInput.clear();
            inputText.setString(userInput);
        } catch (std::exception &e) {
            infoText.setString("Invalid index for Get Element");
        }
    }

    void handleGetSublist() {
        try {
            std::istringstream iss(userInput);
            int startIndex, endIndex;
            if (iss >> startIndex >> endIndex) {
                auto sublist = list.getSubList(startIndex, endIndex);
                std::stringstream ss;
                ss << "Sublist: [";
                for (int i = 0; i < sublist->getLength(); i++) {
                    ss << sublist->get(i);
                    if (i < sublist->getLength() - 1)
                        ss << ", ";
                }
                ss << "]";
                infoText.setString(ss.str());
                userInput.clear();
                inputText.setString(userInput);
            } else {
                throw std::invalid_argument("Invalid input");
            }
        } catch (std::exception &e) {
            infoText.setString("Invalid input for Get Sublist");
        }
    }

    void handleConcatLists() {
        try {
            LinkedList<int> secondList;
            std::string sanitizedInput = userInput;

            // Удаление пробелов в начале и конце строки
            sanitizedInput.erase(sanitizedInput.find_last_not_of(" \n\r\t") + 1);
            sanitizedInput.erase(0, sanitizedInput.find_first_not_of(" \n\r\t"));

            // Проверка на пустой ввод
            if (sanitizedInput.empty()) {
                infoText.setString("Input is empty. Please enter valid values.");
                return;
            }

            // Заменяем запятые на пробелы для унифицированного парсинга
            std::replace(sanitizedInput.begin(), sanitizedInput.end(), ',', ' ');

            std::istringstream iss(sanitizedInput);
            int value;

            // Чтение всех значений из строки
            while (iss >> value) {
                secondList.append(value);  // Добавляем каждый элемент во второй список
            }

            // Проверка, добавлены ли элементы
            if (secondList.getLength() == 0) {
                infoText.setString("No valid numbers were found. Please check the input.");
                return;
            }

            // Теперь вместо вызова concat мы добавляем все элементы второго списка в основной
            for (int i = 0; i < secondList.getLength(); i++) {
                list.append(secondList.get(i));  // Добавляем элементы второго списка к первому
            }

            // Сообщение об успешном выполнении
            infoText.setString("Lists successfully concatenated");

            // Очищаем поле ввода
            userInput.clear();
            inputText.setString(userInput);

        } catch (std::exception &e) {
            infoText.setString("Error occurred during concat: Invalid input.");
        }
    }


    void handleClearList() {
        list.clear();  // Используем специально созданную функцию clear()
        infoText.setString("List cleared");
    }


    void render() {
        window.clear();

        // Отображаем элементы интерфейса
        window.draw(inputBox);
        window.draw(inputText);

        drawButton(addStartButton, addStartText);
        drawButton(addEndButton, addEndText);
        drawButton(insertButton, insertText);
        drawButton(deleteButton, deleteText);
        drawButton(getElementButton, getElementText);
        drawButton(sublistButton, sublistText);
        drawButton(concatButton, concatText);
        drawButton(clearButton, clearText);
        drawButton(exitButton, exitText);

        // Отображаем информацию о списке
        drawList();
        window.draw(infoText);

        window.display();
    }

    void drawButton(const sf::RectangleShape &button, const sf::Text &buttonText) {
        window.draw(button);
        window.draw(buttonText);
    }

    void drawList() {
        float x = 200;
        float y = 50;

        // Отображаем элементы списка в виде прямоугольников
        for (int i = 0; i < list.getLength(); ++i) {
            sf::RectangleShape node(sf::Vector2f(50, 30));
            node.setFillColor(sf::Color::Cyan);
            node.setPosition(x, y);

            sf::Text nodeText;
            nodeText.setFont(font);
            nodeText.setString(std::to_string(list.get(i)));
            nodeText.setCharacterSize(16);
            nodeText.setFillColor(sf::Color::Black);
            nodeText.setPosition(x + 10, y + 5);

            window.draw(node);
            window.draw(nodeText);

            x += 60;  // Смещаем каждый элемент вправо
        }
    }
};

int main() {
    GUI gui;
    gui.run();
    return 0;
}