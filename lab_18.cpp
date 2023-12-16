#include <iostream>

using namespace std;

// Структура узла бинарного дерева
struct Node
{
    int key;
    struct Node* left, * right;
};

// Функция для создания нового узла с заданным ключом
struct Node* newNode(int item)
{
    // Выделяем память под новый узел
    struct Node* temp = new Node;

    // Инициализируем поля узла
    temp->key = item;
    temp->left = temp->right = NULL;

    // Возвращаем указатель на новый узел
    return temp;
}
void storeSorted(Node* root, int arr[], int& i)
{
    // Рекурсивная функция для сохранения узлов в отсортированном порядке

    if (root != NULL)
    {
        // Рекурсивно обходим левое поддерево
        storeSorted(root->left, arr, i);

        // Сохраняем ключ текущего узла в массиве и увеличиваем счетчик i
        arr[i++] = root->key;

        // Рекурсивно обходим правое поддерево
        storeSorted(root->right, arr, i);
    }
}
Node* insert(Node* node, int key)
{
    // Функция вставки нового узла с ключом key в бинарное дерево поиска

    // Если дерево пусто, возвращаем новый узел
    if (node == NULL)
        return newNode(key);

    // В противном случае, рекурсивно спускаемся по дереву
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    // Возвращает неизменный указатель на узел
    return node;
}
void treeSort(int arr[], int n)
{
    // Функция для сортировки массива arr с использованием сортировки деревом

    // Создание корня дерева
    struct Node* root = NULL;

    // Построение бинарного дерева поиска (БДП)
    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++)
        root = insert(root, arr[i]);

    // Обход дерева в порядке возрастания и сохранение значений в массиве arr
    int i = 0;
    storeSorted(root, arr, i);
}

int main()
{
    int arr[] = { 5, 4, 7, 2, 11 };
    int n = sizeof(arr) / sizeof(arr[0]);

    treeSort(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
