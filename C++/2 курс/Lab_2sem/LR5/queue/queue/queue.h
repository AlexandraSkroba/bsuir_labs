#pragma once
#include <iostream>
#include <assert.h>

template <typename T>
class Node {
public:
    Node* next;
    Node* prev;
    T data;

    Node(T data = T()) {
        this->data = data;
    }

    ~Node() {

    }
};

template <typename T>
class queue {
private:

    Node<T>* head;
    Node<T>* tail;
    size_t m_size;

public:

    queue() {
        this->m_size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    ~queue() {
        clear();
    }

    void push(T data) {
        Node<T>* tmp = new Node<T>(data);
        tmp->next = nullptr;

        if (head == nullptr) {
            tmp->prev = nullptr;
            head = tail = tmp;
        }
        else {
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
        m_size++;
    }

    template<typename... Args>
    void emplace(Args && ...args) {
        T element = T(std::forward<Args>(args)...);

        push(element);
    }

    void swap(queue<T>& newQ) {
        Node<T>* tmpHead = this->head;
        Node<T>* tmpTail = this->tail;
        size_t tmpSize = this->m_size;

        this->head = newQ.head;
        this->tail = newQ.tail;

        newQ.head = tmpHead;
        newQ.tail = tmpTail;

        this->m_size = newQ.m_size;
        newQ.m_size = tmpSize;
    }

    void pop() {
        assert(m_size > 0 && "size = 0");
        Node<T>* tmp = head;
        if (m_size == 1) {
            delete tmp;
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;

            delete tmp;
        }
        m_size--;
    }

    T& operator[](const int index) {
        assert(m_size > index && "out of range");

        Node<T>* current = this->head;
        int counter = 0;
        while (current != nullptr) {
            if (counter == index) {
                return current->data;
            }
            current = current->next;
            counter++;
        }
    }

    size_t size() const {
        return m_size;
    }

    bool empty() const {
        return !m_size;
    }

    void clear() {
        while (m_size) {
            pop();
        }
    }

    class Iterator {
    private:
        Node<T>* cur;
    public:
        Iterator(Node<T>* first) {
            this->cur = first;
        }

        Node<T>& operator+(int n) { 
            for (int i = 0; i < n; i++) {
                cur = cur->next;
            }
            return *cur;
        }
        Node<T>& operator-(int n) { 
            for (int i = 0; i < n; i++) {
                cur = cur->prev;
            }
            return *cur; 
        }

        Node<T>& operator++(int) { cur = cur->next; return *cur; }
        Node<T>& operator--(int) { cur = cur->prev;  return *cur; }
        Node<T>& operator++() { cur = cur->next; return *cur->next; }
        Node<T>& operator--() { cur = cur->prev; return *cur->prev; }

        bool operator!=(const Iterator& it) { return cur != it.cur; }
        bool operator==(const Iterator& it) { return cur == it.cur; }
        T& operator*() { return cur->data; }
    };

    Iterator front() { return Iterator(head); }
    Iterator back() { return Iterator(tail); }
};
