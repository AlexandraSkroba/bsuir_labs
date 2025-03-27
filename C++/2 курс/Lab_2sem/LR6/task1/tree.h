#ifndef TREE_H //предотвращает попытку многократного включения заголовочных файлов
#define TREE_H

#pragma once //препроцессорная директива, исходный файл при компиляции подключался строго один раз
#include <iostream>
#include <queue> //для обхода в ширину
#include <vector>
#include <QString>
#include "mainwindow.h"

template <typename T>
class AVLTree {
public:
    class Node {
    public:
        int key;
        T data;
        Node* left;
        Node* right;
        int height;

        Node() = default;
        ~Node() {

        }
    };


    int k = 0; //счетчик для симметричного обхода
    QString G; //показ дерева
    QVector<std::pair<int,QString>> V; //обход предв.

    Node* newNode(int key, T data = T())
    {
        Node* node = new Node();
        node->key = key;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // новый узел изначально добавлен в лист

        return(node);
    }

    Node* root = nullptr;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }// определение класса

     /* Правый поворот */
    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left),
            height(y->right)) + 1;
        x->height = max(height(x->left),
            height(x->right)) + 1;

        return x;
    }

    /* Левый поворот */
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left),
            height(x->right)) + 1;
        y->height = max(height(y->left),
            height(y->right)) + 1;

        return y;
    }

    /* Сбалансирование */
    int getBalance(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        int heightL = height(node->left);
        int heightR = height(node->right);
        return heightL - heightR;
    }

    /* Вставка */
    Node* insert(Node* node, int key, T data = T()) \
    {
        // 1. Обычная вставка BST
        if (node == nullptr) {
            return (newNode(key, data));
        }

        if (key < node->key)
            node->left = insert(node->left, key, data);
        else if (key > node->key)
            node->right = insert(node->right, key, data);
        else // Равные ключи не допускаются в BST
            return node;

        // 2. Обновление высоты родительского узла
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Получение коэффициента баланса этого узла-предка, чтобы проверить, стал ли этот узел несбалансированным
        int balance = getBalance(node);

        // Если этот узел стал несбалансированым, то есть 4 случая

        // Добавление в правое поддерево правого поддерева сына опорного узла
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Добавление в левое поддерево левого сына опорного узла
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Добавление в правое поддерево левого сына опорного узла
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Добавление в левое поддерево правого сына опорного узла
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // вернуть неизменный указатель узла
        return node;
    }

    /* Удаление */
    Node* deleteNode(Node* root, int key)    // Рекурсивная функция для удаления узла с заданным ключом из поддерева с
    {                                        // заданым коренем. Возвращает корень модифицированного поддерева.

        if (!root) return root;

        if (key > root->key)
            root->right = deleteNode(root->right, key);
        else if (key < root->key)
            root->left = deleteNode(root->left, key);
        else
        {
            if (!root->left && !root->right)
            {
                delete root;
                root = nullptr;
            }
            else if (!root->left)
            {
                Node* temp = root;
                root = root->right;
                delete temp;
                temp = nullptr;
            }
            else if (!root->right)
            {
                Node* temp = root;
                root = root->left;
                delete temp;
                temp = nullptr;
            }
            else
            {
                Node* temp = root->right;
                while (temp->left)
                {
                    temp = temp->left;
                }
                root->key = temp->key;
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->key);
            }
        }


        // Если в дереве один узел, возвращаем его
        if (root == nullptr)
            return root;

        // 2. Обновление высоты текущего узла
        root->height = 1 + max(height(root->left), height(root->right));

        // 3. Проверяем, стал ли этот узел несбалансированным (получаем фактор баланса)
        int balance = getBalance(root);

        // Если этот узел стал несбалансированым, то есть 4 случая

        // L Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // LR Case
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // R Case
        if (balance < -1 &&getBalance(root->right) <= 0)
            return leftRotate(root);

        // RL Case
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    /* Вспомогательная ф-я пок. обхода дерева в предвар. поряд */
    void preOrder(Node* root)
    {
        if (root != nullptr)
        {
            std::pair<int,QString> tmp(root->key,root->data);
            V.push_back(tmp);
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    /* Симметричный обход */
    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        if((!node->right && node->left) || (!node->left && node->right))
        {
            k++;
        }
        else if(!node->right && !node->left)
        {
            k+=2;
        }
        std::pair<int,QString> tmp(node->key,node->data);
        V.push_back(tmp);
        inOrder(node->right);
    }

    /* Oбход в обратном порядке */
    void postOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        inOrder(node->right);
        std::pair<int,QString> tmp(node->key,node->data);
        V.push_back(tmp);
    }

    /* Обход в ширину */
    void wideOrder(Node* root) {
        std::queue<Node*> children;
        children.push(root);

        while (!children.empty()) {
            Node* node = children.front();
            children.pop();

            std::pair<int,QString> tmp(node->key,node->data);
            V.push_back(tmp);

            if (node->left)
                children.push(node->left);
            if (node->right)
                children.push(node->right);

        }
    }

    /* нахождение по ключу */
    Node* findElement(Node* root, int key) {

        if (root == nullptr) {
            return nullptr;
        }

        if (root->key > key)
        {
            root->left = findElement(root->left, key);
        }
        else if (root->key < key)
        {
            root->right = findElement(root->right, key);
        }
        else
        {
            return root;
        }
    }

    /* Показ таблицы */
    void recursive_show(Node* cur, unsigned level = 1) {

        if (cur) {

            recursive_show(cur->right, level + 1);

            for (int i = 0; i < level; ++i)
                std::cout << '\t';

            std::cout << cur->key << '\n' << '\n';

            recursive_show(cur->left, level + 1);
        }
    }

    /* Показ дерева */
    void printTree(Node* root, int space = 0) {
        if (root == nullptr){
            return;
        }
        const int COUNT = 3;
        space += COUNT;
        printTree(root->right, space);
        for (int i = COUNT; i < space; i++) {
            G += "  ";
        }
        QString tmp;
        G+=tmp.setNum(root->key);
        G+="\n";
        printTree(root->left, space);
    }

public:
    AVLTree() = default;
    ~AVLTree() {

    }

    void push(int key, T data = T()) {
        root = insert(root, key, data);
    }

    void pop(int key) {
        root = deleteNode(root, key);
    }

    void print() {
        printTree(root);
    }

    void output() {
        preOrder(root);
        std::cout << "\n\n";
        inOrder(root);
        std::cout << "\n\n";
        postOrder(root);
        std::cout << "\n\n";
        wideOrder(root);
        std::cout << "\n\n";
    }

    void find(int key) {
        Node* element = findElement(root, key);
        if (element != nullptr)
        {
            std::cout << element->key << "\n";
        }
        else
        {
            std::cout << "nullptr\n";
        }
    }
};

#endif // TREE_H
// определение класса
