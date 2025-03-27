#ifndef HASH_H //предотвращает попытку многократного включения заголовочных файлов
#define HASH_H

#include "../../LR6/stack.h"
#include <vector>
#include <iostream>
#include <QString>

template <typename T>
class HashTable {
public:

    class Item {
    public:
        int key;
        T data;

        Item() {
            this->key = int();
            this->data = T();
        }

        Item(int key, T data = T()) {
            this->key = key;
            this->data = data;
        }
    };

    std::vector<stack<Item>> vector;
    int size;
    size_t m_size = 0;
    QString s = "";

public:
    HashTable() {
        this->vector.resize(97);
        this->size = this->vector.size();
    }

    int hash(int key) {
        return key % this->size; //построение хеш-ф-и методом деления с остатком
    }

    /* Добавление в таблицу */
    void insert(int key, T data = T()) {
        int index = hash(key);
        Item tmp(key, data);
        m_size++;

        vector[index].push(tmp);
    }

    /* Посик по ключу */
    void search(int key) {
        s = "";
        QString q;
        int index = hash(key);
        for (int i = 0; i < vector[index].getSize(); i++) {
            if (vector[index][i].key == key) {
                QString w;
                q += "key : ";
                q+=w.setNum(vector[index][i].key);
                q+=" data : ";
                q+=vector[index][i].data;
                q+="\n";
            }
        }
        s += q;
    }

    /* существует ли уже такой ключ */
    bool contains(int key)
    {
        int index = hash(key);
        for (int i = 0; i < vector[index].getSize(); i++) {
            if (vector[index][i].key == key) {
                return true;
            }
        }
        return false;
    }

    /* Удаление по ключу */
    void deleteByKey(int key) {
        int index = hash(key);

        if (!vector[index].isEmpty()) {
            stack<Item> newStack;
            while (vector[index].getSize()) {
                if (vector[index].get().key == key) {
                    vector[index].pop();
                    m_size--;
                    break;
                }
                newStack.push(vector[index].get());
                vector[index].pop();
            }
            while (newStack.getSize()) {
                vector[index].push(newStack.get());
                newStack.pop();
            }
            std::cout << vector[index].getSize();
        }
    }
};


#endif // HASH_H
// определение класса
