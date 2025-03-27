#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <iterator>
#include <cmath>
#include <limits>

template <class T>
class vector
{
private:
    size_t _size = 0;
    size_t _capacity = 1;
    T* v{};
public:
    class iterator
    {
    private:
        T* value;
    public:

        iterator(T* vec)
        {
            value = vec;
        }

        T& operator*()
        {
            return *value;
        }

        iterator& operator++()
        {
            ++value;
            return *this;
        }

        iterator operator++(int)
        {
            return iterator(value++);
        }

        iterator& operator--()
        {
            --value;
            return *this;
        }

        iterator operator--(int)
        {
            return iterator(value--);
        }

        int operator-(const iterator& next)
        {
            return this->base() - next.base();
        }

        T* base() const
        {
            return value;
        }

        inline bool operator==(iterator rhs)
        { return value == rhs.base(); }

        inline bool operator!=(iterator rhs)
        { return value != rhs.base(); }

        inline bool operator<(iterator rhs)
        { return value < rhs.base(); }

        inline bool operator>(iterator rhs)
        { return value > rhs.base(); }

        inline bool operator<=(iterator rhs)
        { return value <= rhs.base(); }

        inline bool operator>=(iterator rhs)
        { return value >= rhs.base(); }

        inline iterator operator+(int i){
            return iterator(value + i);
        }
    };

    class reverse_iterator{
    private:
        T* value;
    public:

        reverse_iterator(T* vec)
        {
            value = vec;
        }

        T& operator*()
        {
            return *value;
        }

        reverse_iterator& operator++()
        {
            --value;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            return reverse_iterator(value++);
        }

        reverse_iterator& operator--()
        {
            ++value;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            return reverse_iterator(value--);
        }


        T* base() const
        {
            return value;
        }

        inline bool operator==(reverse_iterator rhs)
        { return value == rhs.base(); }

        inline bool operator!=(reverse_iterator rhs)
        { return value != rhs.base(); }

        inline bool operator<(reverse_iterator rhs)
        { return value < rhs.base(); }

        inline bool operator>(reverse_iterator rhs)
        { return value > rhs.base(); }

        inline bool operator<=(reverse_iterator rhs)
        { return value <= rhs.base(); }

        inline bool operator>=(reverse_iterator rhs)
        { return value >= rhs.base(); }
    };

    ~vector(){
        delete[] v;
    }

    vector(){
        v = new T[1];
        //_capacity = 1;
    }

    vector(size_t size) {
        _size = size;
        while(_capacity <= size){
            _capacity *= 2;
        }
        v = new T[_capacity];
        for(size_t i = 0; i < _size; ++i){
            v[i] = {};
        }
    }
    vector(const vector& other) {
        if (this != &other) {
            delete[] v;
            v = new T[other._capacity];
            for(size_t i = 0; i < other._size; ++i) v[i] = other.v[i];
            _size = other._size;
            _capacity = other._size;
        }
    }
//    vector(const vector & arg)
//        :_size(arg._size), v(new T[arg._capacity])
//    {
//        for (size_t index = 0; index < arg._size; ++index)
//            v[index] = arg.v[index];
//    }
//    vector(vector&& other)  noexcept {
//        if (this != &other) {
//            delete[] v;
//            v = new T[other._capacity];
//            for(size_t i = 0; i < other._size; ++i) v[i] = other.v[i];
//            _size = other._size;
//            _capacity = other._capacity;
//        }
//    }
    void push_back(const T& value){
        if(!_capacity){
            _capacity = _size + 1;
            v = new T[_capacity];
        }
        else if (_size == _capacity){
            _capacity *= 2;
            T* tmp = v;
            v = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) v[i] = tmp[i];
            delete[] tmp;
        }
        ++_size;
        v[_size-1] = value;
    }
    void pop_back(){
        if(!_size){
            return;
        }
        --_size;
        if (_capacity / 2 >= _size ){
            _capacity /= 2;
            T* tmp = v;
            v = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) v[i] = tmp[i];
            delete[] tmp;
        }
    }

    vector operator=(const vector& other) {
        if (this != &other) {
            delete[] v;
            v = new T[other._capacity];
            for(size_t i = 0; i < other._size; ++i) v[i] = other.v[i];
            _size = other._size;
            _capacity = other._size;
        }
        return *this;
    }

//    vector operator=(vector&& other) {
//        if (this != &other) {
//            delete[] v;
//            v = new T[other._capacity];
//            for(size_t i = 0; i < other._size; ++i) v[i] = other.v[i];
//            _size = other._size;
//            _capacity = other._capacity;
//        }
//        return *this;
//    }

    T& operator[](size_t index)  {
        return v[index];
    }

    const T& operator[](size_t index) const {
        return v[index];
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }

    iterator begin(){
        return iterator(v);
    }

    const iterator cbegin() const{
        return iterator(v);
    }

    iterator end(){
        if(!_size){
            return nullptr;
        }
        return iterator(&v[_size]);
    }

    const iterator cend() const{
        if(!_size){
            return nullptr;
        }
        return iterator(&v[_size]);
    }

    void assign(iterator start, iterator end){
        delete[] v;
        v = nullptr;
        _size = 0;
        _capacity = 1;
        iterator tmp = start;
        while(tmp != end){
            tmp++;
            ++_size;
            if(_size > _capacity){
                _capacity *= 2;
            }
        }
        v = new T[_capacity];
        for(int i = 0; start <= end; ++start, ++i){
            v[i] = *start.base();
        }
    }

    T& at(size_t i){
        if(i > _size - 1){
            return *v;
        }
        return v[i];
    }

    T& back() {
        if(!_size){
            return *v;
        }
        return v[_size-1];
    }

    T& front() {
        return v[0];
    }

    void clear(){
        delete[] v;
    }

    T* data() {
        return v;
    }

    bool empty(){
        if(!_size){
            return false;
        }
        return true;
    }

    void reserve(const size_t& n){
        _capacity = n;
        T* tmp = v;
        v = new T[_capacity];
        for(int i = 0; i < _size; ++i){
            v[i] = tmp[i];
        }
    }

    void resize(const size_t& n){
        if(!_capacity){
            _capacity = 1;
            while (_capacity < n) {
                _capacity *= 2;
            }
            v = new T[_capacity];
            for (size_t i = 0; i < n; ++i) v[i] = {};
            _size = n;
        }
        else{
            while(_capacity < n){
                _capacity *= 2;
            }
            T* tmp = v;
            v = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) v[i] = tmp[i];
            for(size_t i = _size; i < n; ++i) v[i] = 0;
            _size = n;
            delete[] tmp;
        }

    }

    void swap(vector& other){
        if(this != &other){
           vector<T> tmp(other);
           other = *this;
           *this = tmp;
        }
    }

    reverse_iterator rend(){
        return reverse_iterator(v-1);
    }

    reverse_iterator rbegin(){
        if(!_size){
            return nullptr;
        }
        return reverse_iterator(v + _size - 1);
    }

    const reverse_iterator crend() const {
        return iterator(v);
    }

    const reverse_iterator crbegin() const {
        if(!_size){
            return nullptr;
        }
        return iterator(&v[_size]);
    }

    unsigned long long max_size(){
        return pow(2, 64-sizeof(T)) - 1;
    }

    void insert(const iterator& it, const T& value){
        ++_size;
        size_t ind = it.base() - v;
        if(_size > _capacity){
            _capacity *= 2;
            T* tmp = v;
            v = new T[_capacity];
            for (size_t i = 0; i < ind; ++i) v[i] = tmp[i];
            v[ind] = value;
            for(size_t i = ind + 1; i < _size; ++i) v[i] = tmp[i-1];
            delete[] tmp;
        }
        else{
            for(size_t i = _size; i > ind; --i){
                v[i] = v[i-1];
            }
            v[ind] = value;
        }
    }

    void erase(const iterator& it){
        int ind = it.base() - v;
        --_size;
        for(size_t i = ind; i < _size; ++i){
            v[i] = v[i+1];
        }
    }

    void reverse(){
        for (int i = 0; i < _size / 2; ++i){
            std::swap(v[i], v[_size - i - 1]);
        }
    }

    template<class... Args>
    void emplace_back(Args&&... args) noexcept {
        using expander = int[];
        (void)expander{NULL,
        (void(push_back(args)), NULL)...};
//        ((push_back(args)),...);
    }

    template<class... Args>
    void emplace(const iterator& it, Args&&... args) noexcept {
        size_t pos = it.base() - v;
        size_t oldSize = _size;
        T* newV = new T[_size - pos];
        for(size_t i = pos - 1, j = 0; i < _size; ++i, ++j){
            newV[j] = v[i];
        }
        _size -= pos;
        emplace_back(args...);
        for(size_t i = 0; i < oldSize - pos + 1; ++i){
            push_back(newV[i]);
        }
        delete[] newV;
    }

    static int _Countl_zero_fallback(T _Val) noexcept {
        T _Yy = 0;

        unsigned int _Nn = std::numeric_limits<T>::digits;
        unsigned int _Cc = std::numeric_limits<T>::digits / 2;
        do {
            _Yy = static_cast<T>(_Val >> _Cc);
            if (_Yy != 0) {
                _Nn -= _Cc;
                _Val = _Yy;
            }
            _Cc >>= 1;
        } while (_Cc != 0);
        return static_cast<int>(_Nn) - static_cast<int>(_Val);
    }

    static int _Countr_zero_fallback(const T _Val) noexcept {
        constexpr int _Digits = std::numeric_limits<T>::digits;
        return _Digits - _Countl_zero_fallback(static_cast<T>(static_cast<T>(~_Val) & static_cast<T>(_Val - 1)));
    }

    template <class _Ret>
    struct _Vbase_compare_three_way {
        _Ret operator()(const T _Left, const T _Right) const noexcept {
            using _Vbase = T;
            const _Vbase _Differing_bits = _Left ^ _Right;

            if (_Differing_bits == 0) {
                return 0;
            }
            const int _Bit_index = _Countr_zero_fallback(_Differing_bits);
            const _Vbase _Mask = _Vbase{1} << _Bit_index;
            return (_Left & _Mask) == 0 ? -1 : 1;
        }
    };

    bool operator<(const vector<T>& rhs){
        //return _size < rhs._size;
        auto _First = v;
                auto _Other = rhs.v;

                const auto _Last = _First + std::min(_size, rhs._size);

                for (; _First != _Last; ++_First, (void) ++_Other) {
                    using _Comp = _Vbase_compare_three_way<signed char>;
                    const auto _Result = _Comp{}(*_First, *_Other);

                    if (_Result < 0) {
                        return true;
                    } else if (_Result > 0) {
                        return false;
                    }
                }

                return _size < rhs._size;
        for (int i = 0, sz = std::min(size(), rhs.size()); i < sz; ++i){
            if (v[i] < rhs[i]) {
                return true;
            }
            if (v[i] > rhs[i]){
                return false;
            }
        }
        return size() < rhs.size();
        return std::lexicographical_compare(v, v + _size, rhs.v, rhs.v + rhs._size);
    }

    bool operator>(const vector<T>& rhs){
        return rhs < this;
//        for (int i = 0, sz = std::min(size(), rhs.size()); i < sz; ++i){
//            if (v[i] > rhs[i]) {
//                return true;
//            }
//            if (v[i] < rhs[i]){
//                return false;
//            }
//        }
//        return size() > rhs.size();
    }

};


#endif // VECTOR_H
