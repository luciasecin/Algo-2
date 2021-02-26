#include "Lista.h"

Lista::Lista() : _length(0), _first(nullptr), _last(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    // Completar
    Nodo* actual = this->_first;
    for (int j = 0; j < this->_length ; ++j) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    while(this->_length != 0){
        this->eliminar(0);
    }
    Nodo* aux = aCopiar._first;
    while(aux){
        this->agregarAtras(aux->valor);
        aux = aux->siguiente;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    nuevo->siguiente = _first;
    _first = nuevo;
    if (nuevo->siguiente != nullptr){
        nuevo->siguiente->anterior = nuevo;
    } else {
        _last = nuevo;
    }
    _length = _length + 1;
}

void Lista::agregarAtras(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    nuevo->anterior = _last;
    _last = nuevo;
    if (nuevo->anterior != nullptr) {
        nuevo->anterior->siguiente = nuevo;
    } else {
        _first = nuevo;
    }
    _length = _length + 1;
}

void Lista::eliminar(Nat i) {
    // Completar
    if (i < this->_length) {
        Nodo *actual = this->_first;
        for (int j = 0; j < i; ++j) {
            actual = actual->siguiente;
        }
        Nodo *anterior = actual->anterior;
        Nodo *siguiente = actual->siguiente;

        if (anterior != nullptr){
            anterior->siguiente = siguiente;
        } else {
            _first = siguiente;
        }
        if (siguiente != nullptr){
            siguiente->anterior = anterior;
        } else {
            _last = anterior;
        }

        delete actual;
        _length = _length - 1;
    }
}

int Lista::longitud() const {
    // Completar
    return _length;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* actual = this->_first;
    for (int j = 0; j < i ; ++j) {
        actual = actual->siguiente;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* actual = this->_first;
    for (int j = 0; j < i ; ++j) {
        actual = actual->siguiente;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
    std::cout << "[";
    for (int i = 0; i < this->_length  - 1; ++i) {
        std::cout << this->iesimo(i) << ", ";
    }
    std::cout << this->iesimo(this->_length) <<"]" << std::endl;
}
