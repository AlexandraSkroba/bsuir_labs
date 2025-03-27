#ifndef PAIR_H
#define PAIR_H

#include <iostream>

template<typename T1, typename T2>
struct pair
{
    T1 first;
    T2 second;

    pair() {
        this->first = T1();
        this->second = T2();
    }

    pair(T1 first, T2 second) {

        this->first = first;
        this->second = second;
    }

    ~pair() {}

    void swap(pair<T1, T2>& b) {

        pair<T1, T2> temp = b;

        b.first = this->first;
        b.second = this->second;

        this->first = temp.first;
        this->second = temp.second;

    }

    void operator=(pair<T1, T2> b) {

        this->first = b.first;
        this->second = b.second;
    }

    bool operator==(pair<T1, T2> b) {

        return this->first == b.first && this->second == b.second;
    }

    bool operator!= (pair<T1, T2> b) {

        return this->first != b.first || this->second != b.second;
    }

};

template<typename T1, typename T2>
pair<T1, T2> make_pair(T1 first, T2 second) {

    return pair<T1, T2>(first, second);
}



#endif // PAIR_H
