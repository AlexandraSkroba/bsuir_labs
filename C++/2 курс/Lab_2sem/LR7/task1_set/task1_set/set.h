#ifndef SET_H
#define SET_H

#include <iostream>
#include "../../utils/queue.h"
#include <vector>
#include "../../utils/stack.h"
#include <QString>

template <typename KeyType>
class set {
public:
    struct Node {
        KeyType key;
        Node* left;
        Node* right;
        Node* parent;
        int height;

        Node() = default;
        ~Node() = default;
    };

    Node* root = nullptr;
    size_t m_size = 0;
    QString S;

private:

    Node* newNode(Node* parent, const KeyType& key)
    {
        Node* node = new Node();
        node->key = key;
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

    Node* insert(Node* parentNode, Node* node, const KeyType& key)
    {
        if (node == nullptr) {
            m_size++;
            return (newNode(parentNode, key));
        }

        if (key < node->key)
            node->left = insert(node, node->left, key);
        else if (key > node->key)
            node->right = insert(node, node->right, key	);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);


        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }


        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* deleteNode(Node* root, const KeyType& key)
    {

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
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
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
            std::cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }


    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->key << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->key << " ";
    }

    void wideOrder(Node* root) {
        queue<Node*> children;
        children.push(root);

        while (!children.empty()) {
            Node* node = *children.front();
            children.pop();

            std::cout << node->key << " ";

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

            std::cout << cur->key << '\n' << '\n';

            recursive_show(cur->left, level + 1);
        }
    }

public:

    void printTree(Node* root, int space = 0) {
        if (!root)
            return;
        const int COUNT = 3;
        space += COUNT;
        printTree(root->right, space);
        for (int i = COUNT; i < space; i++) {
            S.push_back("  ");
        }
        QString s;
        S.push_back(s.setNum(root->key) + '\n');
        printTree(root->left, space);
    }

    bool findElement(Node* node, const KeyType& key) {
        if (node == nullptr) {
            return false;
        }

        if (key < node->key)
            findElement(node->left, key);
        else if (key > node->key)
            findElement(node->right, key);
        else {
            return true;
        }
    }

private:

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

    set() {
        this->m_size = 0;
    }

    ~set() {
        clear();
    }

    void insert(const KeyType& key) {
        root = insert(nullptr, root, key);
    }

    void erase(const KeyType& key) {
        root = deleteNode(root, key);
    }

    void clear() {
        while (m_size)
            this->root = deleteNode(this->root, this->root->key);
    }

    template <typename ... Args>
    void emplace(Args&& ... args) {
        KeyType key = KeyType(std::forward<Args>(args)...);

        this->push(key);
    }

    void print() {
        S = "";
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

            return node->key;
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
                if (node->parent && node->key < node->parent->key)
                    node = node->parent;
                else {
                    while (node->parent && node->key > node->parent->key) {
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
                if (node->parent && node->key > node->parent->key)
                    node = node->parent;
                else {
                    while (node->key < node->parent->key) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            }
            return node;
        }

        KeyType& operator*() {
            return node->key;
        }

        bool operator!=(const BSTIterator& other) { return node != other.node; }
        bool operator==(const BSTIterator& other) { return node == other.node; }
    };

    bool contains(const KeyType& key) {
        return findElement(this->root, key);
    }

    BSTIterator find(const KeyType& key) {
        if (contains(key)) {
            auto it = set<KeyType>::BSTIterator(this->begin());
            for (it; it != this->back(); it++) {
                if (*it == key)
                    return it;
            }
        }
        else {
            return this->end();
        }
    }

    BSTIterator lower_bound(const KeyType& key) {
        for (auto it = set<KeyType>::BSTIterator(this->begin()); it != this->end(); it++) {
            if (*it >= key)
                return it;
        }
        return nullptr;
    }

    BSTIterator upper_bound(const KeyType& key) {
        for (auto it = set<KeyType>::BSTIterator(this->begin()); it != this->end(); it++) {
            if (*it > key)
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

#endif // SET_H
