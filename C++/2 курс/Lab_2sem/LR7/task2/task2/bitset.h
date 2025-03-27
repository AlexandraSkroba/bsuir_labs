#ifndef BITSET_H
#define BITSET_H

#include<string>

template<size_t N> //size_t - беззнаковый целочисленный тип
class bitset{

    unsigned char arr[(N + 7) / 8];

public:
    class reference {        //прокси-класс, который предоставляет ссылки на биты в объекте bitset,
        friend class bitset; //используемые для доступа к отдельным битам и их обработки
                             //в качестве вспомогательного класса для operator[] класса bitset
        unsigned char &word; //хранит блок(байт),который передается в конструкторе
        size_t nBit; //нужный бит в байте высчитываешься по pos%8 и хранится в nBit

        reference(unsigned char &word, size_t nBit) : word(word), nBit(nBit){}
    public:
        reference &operator=(bool x){
            x ? word |= (1 << nBit) : word &= ~(1 << nBit);
            return *this; //ссылка на бит в заданной bitset позицией аргумента для отражения значения измененного бита в bitset
        }
        operator bool(){
            return (word & (1 << nBit)) != 0;
        }
    };

    /* operator[] */
    bool operator[](size_t pos) const{                 //возвращает ссылку на бит в указанной позиции в bitset,
        return (arr[pos / 8] & (1 << (pos % 8))) != 0; //если bitset может быть изменен; в противном случае возвращается
    }                                                  //значение бита в этой позиции
    reference operator[](size_t pos){
        return reference(arr[N / 8], pos % 8); //вот тут
    }
/*---------------------------------------------------------------------------------------------------*/

    bitset() { //заполняем bitset нулями
        for(int i = 0; i < (N + 7) / 8; i++) {
            arr[i] = 0;
        }
    }

    /* дружественные функции(&, |, ~)  имеют доступ к закрытым членам класса, не являясь членами этого класса */
    friend bitset operator&(const bitset &Lbts, const bitset &Rbts){ // побитовое сочетание битовых наборов с побитовой операцией
        bitset result;
        for(int i = 0; i < (N + 7) / 8; i++) {
            result.arr[i] = Lbts.arr[i] & Rbts.arr[i];
        }
        return result;
    }

    friend bitset operator|(const bitset &Lbts, const bitset &Rbts){
        bitset result;
        for(int i = 0; i < (N + 7) / 8; i++){
            result.arr[i] = Lbts.arr[i] | Rbts.arr[i];
        }
        return result;
    }

    friend bitset operator~(const bitset &bts){
        bitset result;
        for(int i = 0; i < (N + 7) / 8; i++){
            result.arr[i] = ~bts.arr[i];
        }
        return result;
    }
/*-----------------------------------------------------------------------------------------------*/

    bool all() { //проверяет, все ли биты имеют значение true
        for(int i = 0; i < N; i++){
            if((arr[i / 8] & (1 << (i % 8))) == 0){
                return false;
            }
        }
        return true;
    }

    bool any() { //проверяет, равен ли какой-либо бит в последовательности 1
        for(int i = 0; i < N; i++) {
            if((arr[i / 8] & (1u << (1 % 8))) != 0)
                return true;
        }
        return false;
    }

    size_t count() { //возвращает количество бит, заданных в последовательности бит
        size_t result = 0;
        for(int i = 0; i < N; i++){
            if((arr[i / 8] & (1u << (i % 8))) != 0){
                result++;
            }
        }
        return result;
    }

    size_t size() { //возвращает количество бит в объекте bitset
        return N;
    }

    bool test(size_t pos) { //проверяет, присвоено ли биту в указанной позиции в bitset значение 1
        return (arr[pos / 8] & (1u << (pos % 8))) != 0;
    }

    std::string to_string(char zero = '0', char one = '1') { //преобразует объект bitset в строковое представление
        std::string result;
        for(int i = 0; i < N; i++) {
            result += test (N - i - 1) ? one : zero;
        }
        return result;
    }

    unsigned long long to_ullong() { //возвращает сумму значений бит в bitset как unsigned long long
        unsigned long long result = 0;

        for(int i = 0; i < (N + 7) / 8; ++i){
            result = arr[i];
        }
        return result;
    }

    unsigned long to_ulong(){ //возвращает сумму значений бит в bitset как unsigned long
        unsigned long result = 0;

        for(int i = 0; i < (N + 7) / 8; ++i){
            result = arr[i];
        }
        return result;
    }

    bool none() { //проверяет, присвоено ли хотя бы одному биту в объекте bitset значение 1
        for(int i = 0; i < N; i++){
            if((arr[i / 8] & (1u << (i % 8))) != 0){
                return false;
            }
        }
        return true;
    }

    /* set */
    bitset &set(){ //присваивает биту в указанной позиции значение 1
        for(int i = 0; i < N; ++i){
            arr[i / 8] |= (1u << (i % 8));
        }
        return *this; //копия измененного bitset объекта, для которого была вызвана функция-член
    }
    bitset &set(size_t pos) { //вторая функция-член создает out_of_range исключение, если указанная позиция больше размера bitset
        arr[pos / 8] |= (1u << (pos % 8));
        return *this;
    }

    /* flip */
    bitset &flip(){ //инвертирует один бит в указанной позиции
        for(int i = 0; i < N; ++i){
            arr[i / 8] ^= (1u << (i % 8));
        }
        return *this; //копия измененного bitset объекта, для которого была вызвана функция-член
    }
    bitset &flip(size_t pos){              //вторая функция-член создает out_of_range исключение, если позиция,
        arr[pos / 8] ^= (1u << (pos % 8)); //указанная в качестве параметра, больше размера N бита bitset<N> которого была инвертирована
        return *this;
    }

    /* reset */
    bitset &reset(){
        for(int i = 0; i < N; ++i){ //сбрасывает бит в указанной позиции в 0
            arr[i / 8] &= ~(1 << (i % 8));
        }
        return *this; //копия bitset , для которой была вызвана функция-член
    }
    bitset &reset(size_t pos) { //вторая функция-член создает out_of_range исключение, если указанная позиция больше размера bitset.
        arr[pos / 8] &= ~(1u << (pos % 8));
        return *this;
    }

};

#endif // BITSET_H
