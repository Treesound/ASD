#include <iostream>
#include <string>

// Структура узла бинарного дерева поиска
struct Node {
    int data;       // Значение узла
    Node* left;     // Указатель на левого потомка
    Node* right;    // Указатель на правого потомка

    // Конструктор для узла с заданным значением
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева поиска
class BinarySearchTree {
public:
    // Конструктор по умолчанию, инициализирует корень как nullptr
    BinarySearchTree() : root(nullptr) {}

    // Вставка значения в дерево
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Удаление значения из дерева
    void remove(int value) {
        root = removeRecursive(root, value);
    }

    // Поиск значения в дереве
    bool search(int value) {
        return searchRecursive(root, value);
    }

    // Получение линейной скобочной нотации для дерева
    std::string getLinearBracketNotation() {
        return generateLinearBracketNotation(root);
    }

    // Вывод линейной скобочной нотации для дерева
    void printLinearBracketNotation() {
        std::cout << "Binary Search Tree (Linear Bracket Notation): " << getLinearBracketNotation() << std::endl;
    }
private:
    Node* root;  // Указатель на корень дерева

    // Рекурсивная вставка значения в дерево
    Node* insertRecursive(Node* node, int value) {
        // Если узел равен nullptr, то создаем новый узел с заданным значением
        if (node == nullptr) {
            return new Node(value);
        }

        // Если значение меньше текущего узла, рекурсивно вставляем его в левое поддерево
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        }
        // Если значение больше текущего узла, рекурсивно вставляем его в правое поддерево
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        // Возвращаем текущий узел после вставки
        return node;
    }

    // Поиск узла с минимальным значением в дереве
    Node* findMin(Node* node) {
        // Пока есть левый потомок, спускаемся влево
        while (node->left != nullptr) {
            node = node->left;
        }
        // Возвращаем узел с минимальным значением
        return node;
    }

    // Рекурсивное удаление узла с заданным значением из дерева
    Node* removeRecursive(Node* node, int value) {
        // Если узел равен nullptr, возвращаем его (удалять нечего)
        if (node == nullptr) {
            return node;
        }

        // Если значение для удаления меньше значения узла, рекурсивно удаляем в левом поддереве
        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        }
        // Если значение для удаления больше значения узла, рекурсивно удаляем в правом поддереве
        else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        }
        else {
            // Узел со значением для удаления найден

            // Если у узла только один потомок или отсутствуют, удаляем узел и возвращаем его потомка (или nullptr)
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // У узла есть оба потомка
            // Находим минимальное значение в правом поддереве (потомке для замены)
            Node* temp = findMin(node->right);
            // Заменяем значение текущего узла минимальным значением
            node->data = temp->data;
            // Рекурсивно удаляем узел с минимальным значением в правом поддереве
            node->right = removeRecursive(node->right, temp->data);
        }

        // Возвращаем обновленный узел
        return node;
    }




    // Рекурсивный поиск значения в дереве
    bool searchRecursive(Node* node, int value) {
        // Если узел равен nullptr, значит значение не найдено
        if (node == nullptr) {
            return false;
        }

        // Если значение узла равно искомому значению, возвращаем true
        if (value == node->data) {
            return true;
        }
        // Если искомое значение меньше значения узла, ищем в левом поддереве
        else if (value < node->data) {
            return searchRecursive(node->left, value);
        }
        // Иначе ищем в правом поддереве
        else {
            return searchRecursive(node->right, value);
        }
    }

    // Генерация линейной скобочной нотации для дерева
    std::string generateLinearBracketNotation(Node* node) {
        // Если узел равен nullptr, возвращаем пустую строку
        if (node == nullptr) {
            return "";
        }

        // Преобразуем значение узла в строку
        std::string result = std::to_string(node->data);

        // Если у узла есть хотя бы один потомок (левый или правый), добавляем скобки и рекурсивно обрабатываем поддеревья
        if (node->left != nullptr || node->right != nullptr) {
            result += "(" + generateLinearBracketNotation(node->left) + ")";
            // Если есть правый потомок, добавляем его обработку
            if (node->right != nullptr) {
                result += "(" + generateLinearBracketNotation(node->right) + ")";
            }
        }

        // Возвращаем полученную линейную скобочную нотацию
        return result;
    }
};

int main() {
    BinarySearchTree bst;

    std::string input;
    std::cout << "Enter Binary Search Tree in linear bracket notation: ";
    std::getline(std::cin, input);

    // Парсинг линейно-скобочной записи и вставка узлов в дерево
    for (char c : input) {
        if (isdigit(c)) {
            int value = c - '0';
            bst.insert(value);
        }
    }

    while (true) {
        std::cout << "\nMenu:\n1. Add Node\n2. Remove Node\n3. Search Node\n4. Print Linear Bracket Notation\n5. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Enter value to add: ";
            int value;
            std::cin >> value;
            bst.insert(value);
            break;
        }
        case 2: {
            std::cout << "Enter value to remove: ";
            int value;
            std::cin >> value;
            bst.remove(value);
            break;
        }
        case 3: {
            std::cout << "Enter value to search: ";
            int value;
            std::cin >> value;
            std::cout << (bst.search(value) ? "Node found" : "Node not found") << std::endl;
            break;
        }
        case 4:
            bst.printLinearBracketNotation();
            break;
        case 5:
            std::cout << "Binary Search Tree (Linear Bracket Notation): " << bst.getLinearBracketNotation() << std::endl;
            std::cout << "Exiting program." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
// (5(3(1)(4))(7(6)(8)))
