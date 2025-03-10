#include <iostream>
#include <cassert>

using namespace std;

template <typename T>

class Stack{ //Se crea la clase Stack, esta será manejada por medio de un vector
    private: //Los atributos son los mismos que los de la estructura Vector, pero se le agrega top_ 
    T* storage_;
    T top_;
    unsigned int capacity_;
    unsigned int size_;

    void Resize(){
        capacity_ = capacity_ * 1.5;
        T* storage2_ = new T[capacity_];
        for(int i = 0; i < size_; i++){
            storage2_[i] = storage_[i];
        }
        delete [] storage_;
        storage_ = storage2_;
    }

    public:
    Stack(){ //Constructor por defecto
        capacity_ = 5; //5 es capacity por defecto si no es especificada
        top_ = T();
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Stack(unsigned int initialSize){ // Constructor para crear una pila de un tamaño inicial
        capacity_ = initialSize;
        top_ = T();
        storage_ = neww T[capacity_];
        size_ = 0;
    }

    unsigned int size() const { //Método para saber la cantidad de elementos en la pila
        return size_;
    }

    bool empty() const { //Método que determina si la pila está o no vacía
        return (size_ == 0);
    }

    T peek() const{ //Retorna el valor del primer elemento(el que está en la parte superior) de la pila
        return top_;
    }

    void push(const T element){ //Mete un elemento en la pila
        if(size_ == capacity_){
            Resize();
        } 
        storage_[size_] = element;
        size_++;
        top_ = element;
    }

    void pop(){ //Borra el último elemento que ingreso
        assert(size_ > 0);
        size_--;
        top_ = storage_[size_ - 1];
        cout << top_ << endl;
    }

    void print(){ //Método que imprime los elementos de la pila
        for(int i = 0; i < size_ ; i++){
            cout << storage_[i] << " ";
        }
        cout << " " << endl;
    }
};

int main(){
    //EJEMPLO DE CÓDIGO PARA PROBAR TODOS LOS MÉTODOS CONSTRUIDOS
    Stack<int> prueba;
    prueba.push(10);
    prueba.push(4);
    prueba.push(7);
    prueba.print(); //Se espera 10, 4, 7 (imprime al revés para apreciar mejor que se pone en la parte superior de la pila)

    prueba.pop();
    prueba.print(); //Se espera 10, 4

    cout << prueba.empty() << endl; //Se espera 0 (No está vacía)
    cout << prueba.peek() << endl; //Se espera 4 (Está en la parte superior de la pila)

    return 0;
}