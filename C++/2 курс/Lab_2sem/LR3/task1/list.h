#ifndef List_H
#define List_H

#include "trainexception.h"
#include "train.h"

template <class T>
class List {
private:
    struct node {
        T value;
        node* left;
        node* right;

        node(const T& new_value, node* new_left, node* new_right) :
            value(new_value), left(new_left), right(new_right) {}
    };
    node* head = nullptr;
    node* back = nullptr;
    int sz = 0;
    node* it = nullptr;
    void pointer_erase(node* p);
public:
    List();
    ~List();
     void clear();
     int size();
     bool empty() const;
     T& at(int n);
     void add_front(const T& value);
     void add_back(const T& value);
     void pop_back();
     void pop_front();
     void erase(const T& key);
     void erase_number(int n);

     void setIt(int n);
     T& getIt();
     void incIt();
     void decIt();
};

template <class T>
 void List<T>::pointer_erase(node* p) {
    if (p == head) {
        pop_front();
        return;
    }
    if (p == back) {
        pop_back();
        return;
    }
    p->left->right = p->right;
    p->right->left = p->left;
    delete p;
    p = nullptr;
    sz--;
}

template <class T>
 List<T>::List() {

}

template <class T>
 List<T>::~List() {
    clear();
}

template <class T>
 void List<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template <class T>
 int List<T>::size() {
    return sz;
}

template <class T>
 bool List<T>::empty() const {
   return (head == nullptr);
}

template <class T>
 T& List<T>::at(int n) {
    if (head == nullptr) {
        throw TrainException("Empty List");
    }
    if (n < 0) {
        throw TrainException("Invalid number");
    }
    int i = 0;
    node* cur = head;
    while ((cur != back) && (i < n)) {
        cur = cur->right;
        i++;
    }
    if (i < n) {
        throw TrainException("Invalid number");
    }
    return cur->value;
}

template <class T>
 void List<T>::add_front(const T& value) {
    if (head == nullptr) {
        back = head = new node(value, nullptr, nullptr);
    } else {
        head->left = new node(value, nullptr, head);
        head = head->left;
    }
    sz++;
}

template <class T>
 void List<T>::add_back(const T& value) {
    if (back == nullptr) {
        head = back = new node(value, nullptr, nullptr);
    } else {
        back->right = new node(value, back, nullptr);
        back = back->right;
    }
    sz++;
}

template <class T>
 void List<T>::pop_back() {
    if (back == nullptr) {
        throw TrainException("Empty List");
    }
    if (head == back) {
        delete back;
        head = back = nullptr;
    } else {
        back = back->left;
        delete back->right;
        back->right = nullptr;
    }
    sz--;
}

template <class T>
 void List<T>::pop_front() {
    if (head == nullptr) {
        throw TrainException("Empty List");
    }
    if (head == back) {
        delete head;
        back = head = nullptr;
    } else {
        head = head->right;
        delete head->left;
        head->left = nullptr;
    }
    sz--;
}

template <class T>
 void List<T>::erase(const T& key) {
    if (head != nullptr) {
        node* cur = head;
        while (cur != back) {
            if (cur->value == key) {
                pointer_erase(cur);
                return;
            }
            cur = cur->right;
        }
    }
}

template <class T>
 void List<T>::erase_number(int n) {
    if (head == nullptr) {
        throw TrainException("Empty List");
    }
    if (n < 0) {
        throw TrainException("Invalid number");
    }
    int i = 0;
    node* cur = head;
    while ((cur != back) && (i < n)) {
        cur = cur->right;
        i++;
    }
    if (i < n) {
        throw TrainException("Invalid number");
    }
    pointer_erase(cur);
}

template <class T>
 void List<T>::setIt(int n) {
    if (head == nullptr) {
        throw TrainException("Empty List");
    }
    if (n < 0) {
        throw TrainException("Invalid number");
    }
    int i = 0;
    node* cur = head;
    while ((cur != back) && (i < n)) {
        cur = cur->right;
        i++;
    }
    if (i < n) {
        throw TrainException("Invalid number");
    }
    it = cur;
}

template <class T>
 T& List<T>::getIt() {
    if (it == nullptr) {
        throw TrainException("Invalid pointer");
    }
    return it->value;
}

template <class T>
 void List<T>::incIt() {
    if (it != nullptr) {
        it = it->right;
    }
}
template <class T>
 void List<T>::decIt() {
    if (it != nullptr) {
        it = it->left;
    }
}

#endif // List_H
