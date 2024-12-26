#pragma once

template <typename T>
class Arr{

  private:
    unsigned int size;
    unsigned int pos;
    T* *arr;

    void InitArr(int start);
    void expand();

  public:
   
    Arr(unsigned int size=5);
    Arr(const Arr& obj);
    ~Arr();
    
    T& operator[](int index);
    void operator=(const T& obj);

    void add(T value);
    void erase(int index);
    void clear();
    unsigned int Size();
};

template <typename T>
Arr<T>::Arr(unsigned int size){
    this->size=size;
    this->pos=0;
    this->arr= new T*[this->size];
    this->InitArr(0);
}

template <typename T>
Arr<T>::Arr(const Arr& obj){
    this->pos=obj.pos;
    this->size=obj.size;

    this->arr = new T*[this->size];
    for(size_t i=0;i<this->pos;i++)
        this->arr[i] = new T(*obj.arr[i]);
    this->InitArr(this->pos);
}



template <typename T>
Arr<T>::~Arr(){
    for (size_t i = 0; i < this->pos; i++) {
        delete this->arr[i];
    }
    delete[] this->arr;
}

template <typename T>
T& Arr<T>::operator[](int index){
    if(index < 0 || index >= this->pos)
        throw ("out of size");
    return *this->arr[index];
}

template <typename T>
void Arr<T>::operator=(const T& obj){
    for(size_t i=0;i<this->pos;i++)
        delete this->arr[i];
    delete[] this->arr;
    this->size=obj.size;
    this->pos=obj.pos;
    this->arr = new T*[this->size];
    for(size_t i=0;i<this->pos;i++)
        this->arr[i]=new T*(obj.arr[i]);
    this->InitArr(this->pos);
}

template <typename T>
void Arr<T>::InitArr(int start){
    for(size_t i=start;i<this->size;i++)
        this->arr[i]=nullptr;
}

template <typename T>
void Arr<T>::expand(){
    this->size*=2;
    T* *temp = new T*[this->size];
    for(size_t i=0;i<this->pos;i++){
        temp[i]=this->arr[i];
    }
    delete []this->arr;
    this->arr=temp;
    InitArr(this->pos);
}

template <typename T>
void Arr<T>::add(T value){
    if(this->pos >= this->size)
        this->expand();
    this->arr[this->pos++]=new T (value);
}

template <typename T>
void Arr<T>::erase(int index){
    if(index <0 || index>=this->pos)
        throw("out of size");
    delete this->arr[index];
    this->arr[index]=this->arr[this->pos-1];
    this->arr[--pos]=nullptr;
}

template <typename T>
unsigned int Arr<T>::Size(){
    return this->pos;
}

template <typename T>
void Arr<T>::clear(){
    for(size_t i=0;i<this->pos;i++)
        delete this->arr[i];
    this->InitArr(0);
    this->pos=0;
}
