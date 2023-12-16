#include <iostream>
#include <string>
#include <stack>

// Структура для представления узла бинарного дерева
struct Node {
    int data;       // Значение узла
    Node* left;     // Указатель на левого потомка
    Node* right;    // Указатель на правого потомка
};

// Функция создания нового узла с заданным значением
Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Рекурсивная функция для прямого обхода дерева
void preOrderRecursive(Node* node) {
    if (node == nullptr)
        return;

    std::cout << node->data << " ";  // Посещение узла
    preOrderRecursive(node->left);   // Рекурсивный обход левого поддерева
    preOrderRecursive(node->right);  // Рекурсивный обход правого поддерева
}

// Рекурсивная функция для центрального обхода дерева
void inOrderRecursive(Node* node) {
    if (node == nullptr)
        return;

    inOrderRecursive(node->left);     // Рекурсивный обход левого поддерева
    std::cout << node->data << " ";  // Посещение узла
    inOrderRecursive(node->right);    // Рекурсивный обход правого поддерева
}

// Рекурсивная функция для концевого обхода дерева
void postOrderRecursive(Node* node) {
    if (node == nullptr)
        return;

    postOrderRecursive(node->left);   // Рекурсивный обход левого поддерева
    postOrderRecursive(node->right);  // Рекурсивный обход правого поддерева
    std::cout << node->data << " ";  // Посещение узла
}

// Нерекурсивная функция для прямого обхода дерева
void preOrderNonRecursive(Node* node) {
    if (node == nullptr)
        return;

    std::stack<Node*> stack;   // Стек для хранения узлов
    stack.push(node);          // Начинаем с корневого узла

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        std::cout << current->data << " ";  // Посещение узла

        if (current->right)
            stack.push(current->right);     // Добавление правого потомка в стек

        if (current->left)
            stack.push(current->left);      // Добавление левого потомка в стек
    }
}

// Функция findIndex находит индекс закрывающей скобки ')' для заданного открывающего символа '('.
int findIndex(const std::string& str, int si, int ei) {
    if (si > ei)
        return -1;

    std::stack<char> s;  // Используем стек для отслеживания открывающих скобок '('

    // Проходим по символам в диапазоне от si до ei включительно
    for (int i = si; i <= ei; i++) {
        if (str[i] == '(')
            s.push(str[i]);  // Если символ - открывающая скобка, добавляем ее в стек
        else if (str[i] == ')') {
            // Если символ - закрывающая скобка, проверяем соответствие с вершиной стека
            if (s.top() == '(') {
                s.pop();  // Если соответствие, удаляем вершину стека
                if (s.empty())
                    return i;  // Если стек пуст, возвращаем индекс закрывающей скобки
            }
        }
    }

    return -1;  // Если не нашли соответствующую закрывающую скобку, возвращаем -1
}

// Функция treeFromString строит бинарное дерево из строки, представляющей структуру дерева.
Node* treeFromString(const std::string& str, int si, int ei) {
    if (si > ei)
        return nullptr;

    int num = 0;
    // Парсим число из строки, начиная с позиции si и двигаясь до позиции ei
    while (si <= ei && str[si] >= '0' && str[si] <= '9') {
        num *= 10;
        num += (str[si] - '0');
        si++;
    }

    Node* root = newNode(num);  // Создаем узел с числовым значением num
    int index = -1;

    // Если текущий символ - открывающая скобка '(',
    // то ищем соответствующую ей закрывающую скобку ')'
    if (si <= ei && str[si] == '(')
        index = findIndex(str, si, ei);

    if (index != -1) {
        // Рекурсивно строим левое и правое поддерево
        root->left = treeFromString(str, si + 1, index - 1);
        root->right = treeFromString(str, index + 2, ei - 1);
    }

    return root;  // Возвращаем построенный узел дерева
}

int main() {
    std::string str = "8(3(1)(6(4)(7)))(10()(14(13)))";
    Node* root = treeFromString(str, 0, str.length() - 1);

    std::cout << "Рекурсивный обход(прямой): ";
    preOrderRecursive(root);
    std::cout << std::endl;

    std::cout << "Рекурсивный обход(центральный): ";
    inOrderRecursive(root);
    std::cout << std::endl;

    std::cout << "Рекурсивный обход(концевой): ";
    postOrderRecursive(root);
    std::cout << std::endl;

    std::cout << "Не рекурсивный прямой обход: ";
    preOrderNonRecursive(root);
    std::cout << std::endl;

    return 0;
}
