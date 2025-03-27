#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "../../utils/queue.h"  //только для обхода в ширину
#include <vector>
#include "../../utils/stack.h" //для итераторов
#include "../../utils/pair.h"
#include <QString>

template <typename KeyType, typename ValueType>
class map {
public:
    struct Node {
        pair<KeyType, ValueType> pair;
        Node* left;
        Node* right;
        Node* parent;
        int height;

        Node() = default;
        ~Node() = default;
    };

    Node* root = nullptr;
    size_t m_size = 0;
    QString SF,SS;

private:

    Node* newNode(Node* parent, pair<KeyType,ValueType> pair)
    {
        Node* node = new Node();
        node->pair = pair;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
        node->height = 1;

        return(node);
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        x->parent = y->parent;
        y->parent = x;

        if (T2)
            T2->parent = y;

        y->height = max(height(y->left),
            height(y->right)) + 1;
        x->height = max(height(x->left),
            height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        y->parent = x->parent;
        x->parent = y;

        if (T2)
            T2->parent = x;

        x->height = max(height(x->left),
            height(x->right)) + 1;
        y->height = max(height(y->left),
            height(y->right)) + 1;

        return y;
    }

    int getBalance(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        int heightL = height(node->left);
        int heightR = height(node->right);
        return heightL - heightR;
    }

    Node* insert(Node* parentNode, Node* node, pair<KeyType,ValueType> pair)
    {
        if (node == nullptr) {
            m_size++;
            return (newNode(parentNode, pair));
        }

        if (pair.first < node->pair.first)
            node->left = insert(node, node->left, pair);
        else if (pair.first > node->pair.first)
            node->right = insert(node, node->right, pair);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);


        if (balance > 1 && pair.first < node->left->pair.first)
            return rightRotate(node);

        if (balance < -1 && pair.first > node->right->pair.first)
            return leftRotate(node);

        if (balance > 1 && pair.first > node->left->pair.first)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }


        if (balance < -1 && pair.first < node->right->pair.first)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* deleteNode(Node* root, KeyType key)
    {

        if (!root) return root;

        if (key > root->pair.first)
            root->right = deleteNode(root->right, key);
        else if (key < root->pair.first)
            root->left = deleteNode(root->left, key);
        else
        {
            if (!root->left && !root->right)
            {
                delete root;
                root = nullptr;
                m_size--;
            }
            else if (!root->left)
            {
                Node* temp = root;
                root = root->right;
                delete temp;
                temp = nullptr;
                m_size--;
            }
            else if (!root->right)
            {
                Node* temp = root;
                root = root->left;
                delete temp;
                temp = nullptr;
                m_size--;
            }
            else
            {
                Node* temp = root->right;
                while (temp->left)
                {
                    temp = temp->left;
                }
                root->pair = temp->pair;
                root->right = deleteNode(root->right, temp->pair.first);
            }
        }


        if (root == NULL)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);


        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void preOrder(Node* root)
    {
        if (root != nullptr)
        {
            std::cout << root->pair.first << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }


    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->pair.first << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->pair.first << " ";
    }

    void wideOrder(Node* root) {
        queue<Node*> children;
        children.push(root);

        while (!children.empty()) {
            Node* node = *children.front();
            children.pop();

            std::cout << node->pair.first << " ";

            if (node->left)
                children.push(node->left);
            if (node->right)
                children.push(node->right);

        }
    }


    void recursive_show(Node* cur, unsigned level = 1) {

        if (cur) {

            recursive_show(cur->right, level + 1);

            for (int i = 0; i < level; ++i)
                std::cout << '\t';

            std::cout << cur->pair.first << '\n' << '\n';

            recursive_show(cur->left, level + 1);
        }
    }

    void printTreeFirst(Node* root, int space = 0) {
        if (!root)
            return;
        const int COUNT = 3;
        space += COUNT;
        printTreeFirst(root->right, space);
        for (int i = COUNT; i < space; i++) {
            SF.push_back("  ");
        }
        SF.push_back(QString::fromStdString(root->pair.first) + '\n');
        printTreeFirst(root->left, space);
    }

    void printTreeSecond(Node* root, int space = 0) {
        if (!root)
            return;
        const int COUNT = 3;
        space += COUNT;
        printTreeSecond(root->right, space);
        for (int i = COUNT; i < space; i++) {
            SS.push_back("  ");
        }
        QString s;
        SS.push_back(s.setNum(root->pair.second) + '\n');
        printTreeSecond(root->left, space);
    }

    void changeValueType(Node* node, const KeyType& key, const ValueType& value) {
        if (node == nullptr) {
            return;
        }

        if (key < node->pair.first)
            changeValueType(node->left, key, value);
        else if (key > node->pair.first)
            changeValueType(node->right, key, value);
        else {
            node->pair.second = value;
            return;
        }
    }

    bool findElement(Node* node, const KeyType& key) {
        if (node == nullptr) {
            return false;
        }

        if (key < node->pair.first)
            findElement(node->left, key);
        else if (key > node->pair.first)
            findElement(node->right, key);
        else {
            return true;
        }
    }

    Node* firstNode(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node* lastNode(Node* node) {
        while (node->right)
            node = node->right;
        return node;
    }

public:

    map() {
        this->m_size = 0;
    }

    ~map(){
        clear();
    }

    void insert(pair<KeyType,ValueType> pair) {
        root = insert(nullptr, root, pair);
    }

    void insert_or_assign(pair<KeyType, ValueType> pair) {
        if (contains(pair.first)) {
            changeValueType(this->root, pair.first, pair.second);
        }
        else {
            insert(pair);
        }
    }

    void erase(const KeyType& key) {
        root = deleteNode(root, key);
    }

    void clear() {
        while (m_size)
            this->root = deleteNode(this->root, this->root->pair.first);
    }

    void printFirst() {
        SF = "";
        printTreeFirst(root);
    }

    void printSecond() {
        SS = "";
        printTreeSecond(root);
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

    bool empty() {
        return !m_size;
    }

    size_t size() {
        return m_size;
    }

    class ForwardBSTIterator {
    private:
        stack<Node*> stack;
    public:

        ForwardBSTIterator(Node* root) {
            pushLeft(root);
        }

        ~ForwardBSTIterator() {

        }

        int next() {
            Node* node = stack.get();
            stack.pop();
            if (node->right != nullptr) {
                pushLeft(node->right);
            }

            return node->pair.first;
        }

        bool hasNext() {
            return stack.size() > 0;
        }

    private:
        void pushLeft(Node* root) {
            while (root != nullptr) {
                stack.push(root);
                root = root->left;
            }
        }
    };

    class BSTIterator {
    private:
        Node* node;

    public:
        BSTIterator(Node* node) {
            this->node = node;
        }

        ~BSTIterator() {

        }

        Node* operator++(int) {
            if (!node) {
                return nullptr;
            }
            if (node->right) {
                node = node->right;
                while (node->left)
                    node = node->left;
            }
            else {
                if (node->parent && node->pair.first < node->parent->pair.first)
                    node = node->parent;
                else {
                    while (node->parent && node->pair.first > node->parent->pair.first) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            }
            return node;
        }

        Node* operator--(int) {
            if (node->left) {
                node = node->left;
                while (node->right)
                    node = node->right;
            }
            else {
                if (node->parent && node->pair.first > node->parent->pair.first)
                    node = node->parent;
                else {
                    while (node->pair.first < node->parent->pair.first) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            }
            return node;
        }

        pair<KeyType,ValueType>& operator*() {
            if (node)
                return node->pair;
        }

        bool operator!=(const BSTIterator& other) { return node != other.node; }
        bool operator==(const BSTIterator& other) { return node == other.node; }
    };

    BSTIterator find(const KeyType& key) {
        if (contains(key)) {
            auto it = map<KeyType, ValueType>::BSTIterator(this->begin());
            for (it; it != this->end(); it++) {
                if ((*it).first == key)
                    return it;
            }
        }
        else {
            return end();
        }
    }

    bool contains(const KeyType& key) {
        return findElement(this->root, key);
    }

    BSTIterator lower_bound(const KeyType& key) {
        for (auto it = map<KeyType,ValueType>::BSTIterator(this->begin()); it != this->end(); it++) {
            if ((*it).first >= key)
                return it;
        }
        return nullptr;
    }

    BSTIterator upper_bound(const KeyType& key) {
        for (auto it = map<KeyType, ValueType>::BSTIterator(this->begin()); it != this->end(); it++) {
            if ((*it).first > key)
                return it;
        }
        return nullptr;
    }

    Node* begin() {
        return firstNode(this->root);
    }

    Node* back() {
        return lastNode(this->root);
    }

    Node* end() {
        return lastNode(this->root)->right;
    }
};

#endif // MAP_H
