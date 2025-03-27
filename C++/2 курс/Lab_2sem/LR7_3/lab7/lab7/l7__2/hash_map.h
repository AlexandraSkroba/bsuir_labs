#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <utility>
#include <vector>
#include <string>
#include <QString>

namespace myhash
{
    template<class _Key>
    struct hash { };


    template<>
    struct hash<std::string>
    {
        size_t operator()(std::string str) const
        {
            char* s = const_cast<char*>(str.data());
            unsigned long hash_key = 0;
            for (; *s; ++s)
                hash_key = 5 * hash_key + *s;
            return size_t(hash_key);
        }
    };

    template<>
    struct hash<char*>
    {
        size_t operator()(const char* s) const
        {
            unsigned long hash_key = 0;
            for (; *s; ++s)
                hash_key = 5 * hash_key + *s;
            return size_t(hash_key);
        }
    };

    template<>
    struct hash<const char*>
    {
        size_t operator()(const char* s) const
        {
            unsigned long hash_key = 0;
            for (; *s; ++s)
                hash_key = 5 * hash_key + *s;
            return size_t(hash_key);
        }
    };

    template<>
    struct hash<char>
    {
        size_t operator()(char __x) const
        {
            return __x;
        }
    };

    template<>
    struct hash<short>
    {
        size_t operator()(short __x) const
        {
            return __x;
        }
    };

    template<>
    struct hash<unsigned short>
    {
        size_t operator()(unsigned short __x) const
        {
            return __x;
        }
    };

    template<>
    struct hash<int>
    {
        size_t operator()(int __x) const
        {
            return __x;
        }
    };

    template<>
    struct hash<unsigned int>
    {
        size_t operator()(unsigned int __x) const
        {
            return __x;
        }
    };

    template<>
    struct hash<long>
    {
        size_t operator()(long __x) const
        {
            return __x;
        }
    };

    template<>
    struct hash<unsigned long>
    {
        size_t operator()(unsigned long __x) const
        {
            return __x;
        }
    };
}


template<class KeyType, class ValueType, class Hash = myhash::hash<KeyType>>
class hash_map
{
private:

    size_t _size;
    size_t capacity;
    const double MAX_LOAD_FACTOR = 0.8;

    size_t hash_function(KeyType key) {
        return Hash()(key) % capacity;
    }
    struct Node
    {
        std::pair<KeyType, ValueType> kv;
        Node* next;

        Node(const KeyType& key, const ValueType& value) :
            kv(key, value), next(nullptr)
        {}
    };


    std::vector<Node*> data;

    void reserve()
    {
        capacity *= 2;
        rehash();
    }

    void load_check() {
        if (load_factor() > MAX_LOAD_FACTOR)
            reserve();
    }

    bool data_insert(std::vector<Node*>& v, const KeyType& key, const ValueType& value) {
        size_t hash = hash_function(key);
        Node** cell = &v[hash];
        while (*cell) {
            if ((*cell)->kv.first == key)
            {
                return false;
            }
            cell = &(*cell)->next;
        }
        *cell = new Node(key, value);
        return true;
    }

    bool data_erase(std::vector<Node*>& v, const KeyType& key) {
        size_t hash = hash_function(key);
        Node* cell = v[hash];
        Node* prev_cell = nullptr;
        while (cell) {
            if (cell->kv.first == key)
            {
                if (prev_cell)
                    prev_cell->next = cell->next;
                else
                    v[hash] = cell->next;
                delete cell;
                return true;
            }
            prev_cell = cell;
            cell = cell->next;
        }
        return false;
    }

    void rehash()
    {
        std::vector<Node*> new_data(capacity);
        for (int i = 0; i < data.size(); ++i) {
            Node* cell = data[i];
            data[i] = nullptr;
            while (cell) {
                Node* tmp = cell->next;
                auto p = cell->kv;
                delete cell;
                data_insert(new_data, p.first, p.second);
                cell = tmp;
            }
        }
        data.assign(new_data.begin(), new_data.end());
    }


    double load_factor()
    {
        return static_cast<double>(_size) / capacity;
    }

public:
    hash_map() :
        capacity(100),
        _size(0),
        data(capacity)
    {}

    ~hash_map() {
        clear();
    }

    bool insert(const KeyType& key, const ValueType& value) {
        bool inserted = data_insert(data, key, value);
        _size += inserted;
        load_check();
        return inserted;
    }

    void clear() {
        for (int i = 0; i < capacity; ++i) {
            Node* cell = data[i];
            data[i] = nullptr;
            while (cell) {
                Node* tmp = cell->next;
                delete cell;
                cell = tmp;
            }
        }
        _size = 0;
    }

    bool empty() {
        return _size == 0;
    }

    size_t size() {
        return _size;
    }

    bool erase(const KeyType& key) {
        bool erased = data_erase(data, key);
        _size -= erased;
        return erased;
    }

    ValueType& operator[](const KeyType& key) {
        size_t hash = hash_function(key);
        Node** cell = &data[hash];
        while (*cell) {
            if ((*cell)->kv.first == key)
            {
                return (*cell)->kv.second;
            }
            cell = &(*cell)->next;
        }
        *cell = new Node(key, ValueType());
        ++_size;
        return (*cell)->kv.second;
    }

    QString toString(){
        QString ans;
        for(int i = 0; i < capacity; ++i){
            if(data[i]){
                Node* tmp = data[i];
                ans += QString::number(data[i]->kv.second) + ' ';
                while(tmp->next){
                    ans += QString::number(tmp->next->kv.second) + ' ';
                    tmp = tmp->next;
                }
            }
        }
        return ans;
    }

    bool count(const KeyType& key){
        size_t hash = hash_function(key);
        Node* tmp = data[hash];
        while(tmp){
            if(tmp->kv.first == key){
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
};

#endif // HASH_MAP_H
