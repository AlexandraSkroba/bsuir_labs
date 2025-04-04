#ifndef MAP_H
#define MAP_H

#include <QString>

template<class keyType, class valueType>
class map
{
private:

    struct node // структура для представления узлов дерева
    {
        std::pair<keyType, valueType> kv; //ключ и значение
        size_t height; //высота поддерева с корнем в данном узле
        node* left; //указатель на левое поддерево
        node* right; //указатель на правое поддерево
        node* prev; //указатель на предыдущий узел
        node(keyType k, valueType v, node* prev = nullptr):
            prev(prev),
            kv(k, v),
            left(nullptr),
            right(nullptr),
            height(1)
        {}
        ~node() { if (left) delete left; if (right) delete right; }
    };

    node* root;
    size_t _size;

    static void destroyNode(node* node) {
            if (node) {
                destroyNode(node->left);
                destroyNode(node->right);
                delete node;
            }
    }


    //О(1)
    static unsigned char height(node* p) //get
    {
        return p ? p->height : 0;
    }

    static int balanceFactor(node* p) //показатель баланса
    {
        return height(p->right) - height(p->left);
    }

    static void updateHeight(node* p) //обновление высоты
    {
        size_t hl = height(p->left);
        size_t hr = height(p->right);
        p->height = std::max(hl, hr) + 1;
    }

    static node* rotateRight(node* p)
    {
        node* q = p->left;
        node* parent = p->prev;
        p->left = q->right;
        q->right = p;

        p->prev = q;
        q->prev = parent;
        q->left->prev = q;
        q->right->prev = q;
        updateHeight(p);
        updateHeight(q);
        return q;
    }

    static node* rotateLeft(node* q)
    {
        node* parent = q->prev;
        node* p = q->right;
        q->right = p->left;

        p->left = q;
        p->left->prev = p;
        p->right->prev = p;
        p->prev = parent;
        updateHeight(q);
        updateHeight(p);
        return p;
    }

    static node* balance(node* p)
    {
        if (p == nullptr)
            return nullptr;
        updateHeight(p);
        if (balanceFactor(p) == 2) {
            if (balanceFactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (balanceFactor(p) == -2) {
            if (balanceFactor(p->left) > 0)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p; //балансировка не нужна
    }

    bool exists(node* p, keyType key)
    {
        if (!p) return false;
        if (p->kv.first == key) return true;
        if (key < p->kv.first) return exists(p->left, key);
        return exists(p->right, key);
    }

    bool empty()
    {
//        if (!p) return true;
//        else return false;
        return _size == 0;
    }

    node* insert(node* p, keyType key, valueType value, node* prev)
    {
        if (exists(p, key)) return p;
        if (!p) {
            ++_size;
            return new node(key, value, prev);
        }
        if (key < p->kv.first)
            p->left = insert(p->left, key, value, prev);
        else
            p->right = insert(p->right, key, value, prev);
        return balance(p);
    }

    void Insert(keyType key, valueType value) {
        root = insert(root, key, value, nullptr);
    }

    static node* findMin(node* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left ? findMin(p->left) : p;
    }

    static node* removeMin(node* p) // удаление узла с минимальным ключом из дерева p
    {
        if (p->left == 0)
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }

    node* remove(node* p, keyType key) // удаление ключа k из дерева p
    {
        if (!p) return 0;
        if (key < p->kv.first)
            p->left = remove(p->left,key);
        else if (key > p->kv.first)
            p->right = remove(p->right,key);
        else {
            node* q = p->left;
            node* r = p->right;
            node* parent = p->prev;
            delete p;
            --_size;
            if( !r ) return q; //если правое поддерево пустое, то возвращаем указатель на левое поддерево
            node* min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            min->prev = parent;

            if (min->right)
                min->right->prev = min;
            if (min->left)
                min->left->prev = min;
            return balance(min);
        }
        return balance(p);
    }

    void Remove(keyType key){
        root = remove(root, key);
    }

public:
    map() :
        root(nullptr), _size(0){}

    class iterator{
        using T = std::pair<keyType, valueType>;
        node* elem;

    public:
        iterator(node* node) : elem(node) {}

        iterator(const iterator& other) : elem(other.elem) {}

        T& operator*()
        {
            return this->elem->kv;
        }

        T* operator->(){
            return &this->elem->kv;
        }

        iterator operator++(){
            keyType min = elem->kv.first;
            if (elem->right && min < elem->right->kv.first) {
                elem = elem->right;
                while (elem->left){
                    elem = elem->left;
                }
                return *this;
            }
            if (elem->prev && elem->prev->kv.first > min){
                elem = elem->prev;
                return *this;
            }
            while (elem->prev && elem->prev->kv.first < min) {
                elem = elem->prev;
            }
            if (elem->prev && min < elem->prev->kv.first) {
                elem = elem->prev;
                return *this;
            }
            elem = nullptr;
            return *this;
        }

        iterator operator++(int) {
            return ++*this;
        }

        bool operator!=(const iterator& other) {
            return this->elem != other.elem;
        }

        bool operator==(const iterator& other) {
            return this->elem == other.elem;
        }

        operator bool() {
            return elem;
        }
        friend void map<keyType, valueType>::erase(const iterator& it);
    };

    iterator begin(){
        node* elem = root;
        while (elem && elem->left) elem = elem->left;
        return iterator(elem);
    }

    iterator end(){
        return iterator(nullptr);
    }

    iterator find(const keyType& key){
        node* elem = root;
        while (elem) {
            if (key < elem->kv.first) {
                elem = elem->left;
            }
            else if (key > elem->kv.first) {
                elem = elem->right;
            }
            else {
                return iterator(elem);
            }
        }
        return iterator(elem);
    }

    void insert(keyType key, valueType value) {
        Insert(key, value);
    }

    void erase(keyType key)
    {
        Remove(key);
    }

    void erase(const iterator& it)
    {
        if(!it.elem){
            throw 0;
        }
        Remove(it.elem->key);
    }

    valueType& search(const keyType& key){
        node** p = &root;
        node* prev = nullptr;
        while (*p) {
            if (key < (*p)->kv.first) {
                prev = *p;
                p = &(*p)->left;
            }
            else if (key > (*p)->kv.first) {
                prev = *p;
                p = &(*p)->right;
            }
            else {
                return (*p)->kv.second;
            }
        }
        ++_size;
        *p = new node(key, valueType());
        (*p)->prev = prev;
        valueType& value = (*p)->kv.second;
        (*p)->prev = balance((*p)->prev);
        return value;
    }

    int size() { return _size; }

    void clear(){
        destroyNode(root);
        root = nullptr;
        _size = 0;
    }

    int count(keyType key){
        return find(key) != iterator(nullptr);
    }

    valueType& at(keyType key){
        return search(key);
    }

    valueType& operator[](keyType key){
        return at(key);
    }
};

#endif // MAP_H
