#include <iostream>
#include <cassert>

using namespace std;

template <typename T>

class Stack{
    private:
    T* storage_;
    T top_;
    unsigned int capacity_;
    unsigned int size_;

    void Resize(){
        cout << "Resize" << endl;
        capacity_ = capacity_ * 1.5;
        T* storage2_ = new T[capacity_];
        for(int i = 0; i < size_; i++){
            storage2_[i] = storage_[i];
        }
        delete [] storage_;
        storage_ = storage2_;
    }

    public:
    Stack(){
        capacity_ = 5;
        top_ = T();
        storage_ = new T[capacity_];
        size_ = 0;
    }

    unsigned int size() const {
        return size_;
    }

    bool empty() const {
        return (size_ == 0);
    }

    T peek(){
        return top_;
    }

    void push(const T element){
        if(size_ == capacity_){
            Resize();
        } 
        storage_[size_] = element;
        size_++;
        top_ = element;
    }

    void pop(){
        assert(size_ > 0);
        size_--;
        top_ = storage_[size_ - 1];
        cout << top_ << endl;
    }

    void print(){ //Operacion que imprime los elementos del vector
        for(int i = size_ - 1; i >= 0; i--){
            cout << storage_[i] << " ";
        }
        cout << " " << endl;
    }
};

int main(){
    return 0;
}