#include <iostream>
#include <cassert>
#include <time.h>
#include <fstream>
using namespace std;

template <typename T>

class Vector {
private:
    T* storage_ ;
    unsigned int capacity_;
    unsigned int size_;
    unsigned int resizesCounter_; //Este atributo es para el punto de analizar las políticas

    void Resize(){
        //cout << "Resize" << endl;
        capacity_ = capacity_ * 1.5;
        T* storage2_ = new T[capacity_];
        for(int i = 0; i < size_; i++){
            storage2_[i] = storage_[i];
        }
        delete [] storage_;
        storage_ = storage2_;
    }

public:
    Vector(){ //Constructor principal, para inicializar los atributos
        //cout << "Hi!" << endl;
        capacity_ = 10;
        storage_ = new T[capacity_];
        size_ = 0;
        resizesCounter_ = 0;
    }

    Vector(unsigned int amount, T elem = T()){//Constructor que inicializa el vector con una cantidad específica
        cout << "Hi!" << endl;
        capacity_ = amount;
        storage_ = new T[capacity_];
        size_ = 0;
        resizesCounter_ = 0;
    }

    Vector(const initializer_list<T> vector){//Constructor que inicializa el vector con una cantidad y un dato específico
        capacity_ = vector.size();
        storage_ = new T[capacity_];
        unsigned int index = 0;
        for(const T& i : vector){
            storage_[index++] = i;
        }
        size_ = capacity_;
        resizesCounter_ = 0;
    }

    unsigned int size() { //Operacion que devuelve el tamaño hasta el momento del vector
        return size_;
    }

    unsigned int counter(){
        return resizesCounter_;
    }

    unsigned int capacity() const {
        return capacity_;
    }

    bool empty() const{
        return size_ == 0;
    }

    void print(){ //Operacion que imprime los elementos del vector
        for(int i = 0; i < size(); i++){
            cout << storage_[i] << " ";
        }
        cout << " " << endl;
    }

    T& at(unsigned int position){ //Operacion que devuelve un puntero a lo que hay en position¿?
        assert(position >= 0 && position < size_);
        return storage_[position];
    }

    void push_back(const T& elem){
        if(size_ == capacity_){
            Resize();
            resizesCounter_++;
        }
        storage_[size_] = elem;
        size_++;
    }

    void pop_back(){
        assert(size_);
        size_--;
    }

    unsigned int waste() const{
        return capacity_ - size_;
    }

    void insert(unsigned int index, T element){
        if(size_ == capacity_){
            Resize();
        }
        for(int i = size_ - 1; i >= index; i--){
            storage_[i + 1] = storage_[i];  
        }
        storage_[index] = element;
        size_++;
    }

    void erase(unsigned int index){
        for(int i = index; i < size_; i++){
            storage_[i] = storage_[i + 1];  
        }
        size_--;
    }
};

template <typename T>
Vector<T> removeDuplicates(Vector<T> &vector){
    unsigned int size = vector.size();
    unsigned int index = 1;
    while(index < size){
        if(vector.at(index) == vector.at(index - 1)){
            vector.erase(index);
            size--;
        } else {
            index++;
        }
    }
    return vector;
}

void AnalyzeInsertions(){
    srand(time(0));
    int num = 0;
    Vector<int> insertions;
    Vector<unsigned int> capacities(1000);
    Vector<unsigned int> sizes(1000); 
    ofstream file("analysis.txt");
    for(int i = 0; i < 1000000; i++){
        if((i % 1000) == 0){
            capacities.push_back(insertions.capacity());
            sizes.push_back(insertions.size());
        } else {
            insertions.push_back(num);
        }  
    }
    file << "Capacities:\n";
    for (int i = 0; i < capacities.size(); i++) {
        file << capacities.at(i) << " ";
    }
    /*file << "\n\n\nSizes:\n";
    for (int i = 0; i < sizes.size(); i++) {
        file << sizes.at(i) << " ";
    }*/
    file << "\n\n\nCounter: " << insertions.counter() << endl;

    // Cerrar el archivo
    file.close();
}

void Merge(Vector<int> *totalVector, int left, int mid, int right) {
    int i = left, j = mid + 1;
    Vector<int> temp;

    while (i <= mid && j <= right) {
        if (totalVector->at(i) <= totalVector->at(j)) {
            temp.push_back(totalVector->at(i));
            i++;
        } else {
            temp.push_back(totalVector->at(j));
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(totalVector->at(i));
        i++;
    }
    while (j <= right) {
        temp.push_back(totalVector->at(j));
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        totalVector->at(left + k) = temp.at(k);
    }
}

void MergeSort(Vector<int> *totalVector, int left, int right) {
    if (left >= right) return; 

    int mid = (left + right) / 2;

    MergeSort(totalVector, left, mid);
    MergeSort(totalVector, mid + 1, right);

    Merge(totalVector, left, mid, right);
}

Vector<int> mergeSortedVectors(Vector<int> &vector1, Vector<int> &vector2){
    Vector <int> totalVector;
    for(int i = 0; i < vector1.size(); i++){
        totalVector.push_back(vector1.at(i));
    }
    for(int i = 0; i < vector2.size(); i++){
        totalVector.push_back(vector2.at(i));
    }

    MergeSort(&totalVector, 0, totalVector.size() - 1);

    return totalVector;
}

int main(){
    AnalyzeInsertions();
    return 0;
}