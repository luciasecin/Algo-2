
template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _longitud(0) {}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
    while (_raiz != nullptr) {
        remover(_raiz->valor);
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    bool res = false;
    while (!res && actual != nullptr){
        if (clave > actual->valor) {
            res = clave == actual->valor;
            actual = actual->der;
        }
        else if (clave < actual->valor) {
            res = clave == actual->valor;
            actual = actual->izq;
        }
        else if (clave == actual->valor)
            res = true;
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (!this->pertenece(clave)) {
        Nodo* nuevo = new Nodo(clave);
        if (_raiz == nullptr)
            _raiz = nuevo;
        else {
            Nodo *actual = _raiz;
            while (actual != nuevo) {
                if (clave > actual->valor) {
                    if (actual->der == nullptr)
                        actual->der = nuevo;
                    actual = actual->der;
                } else if (clave < actual->valor) {
                    if (actual->izq == nullptr)
                        actual->izq = nuevo;
                    actual = actual->izq;
                }
            }
        }
        _longitud++;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (this->pertenece(clave)){
        Nodo *actual = _raiz;
        Nodo *anterior = _raiz;
        while (clave != actual->valor) {
            if (clave > actual->valor) {
                anterior = actual;
                actual = actual->der;
            }
            else if (clave < actual->valor) {
                anterior = actual;
                actual = actual->izq;
            }
        }

        if (actual->der == nullptr || actual->izq == nullptr){
            if (actual->der == nullptr && actual->izq == nullptr) {
                if (_raiz == actual) {
                    _raiz = nullptr;
                    delete actual;
                } else if (anterior->der != nullptr && clave == anterior->der->valor) {
                    anterior->der = nullptr;
                    delete actual;
                } else if (anterior->izq != nullptr && clave == anterior->izq->valor) {
                    anterior->izq = nullptr;
                    delete actual;
                }
            } else if (actual->der == nullptr) {
                if (actual == _raiz){
                    _raiz = actual->izq;
                    delete actual;
                } else {
                    if (anterior->der != nullptr && clave == anterior->der->valor) {
                        anterior->der = actual->izq;
                        delete actual;
                    } else if (anterior->izq != nullptr && clave == anterior->izq->valor) {
                        anterior->izq = actual->izq;
                        delete actual;
                    }
                }
            } else {
                if (actual == _raiz) {
                    _raiz = actual->der;
                    delete actual;
                } else {
                    if (anterior->der != nullptr && clave == anterior->der->valor) {
                        anterior->der = actual->der;
                        delete actual;
                    } else if (anterior->izq != nullptr && clave == anterior->izq->valor) {
                        anterior->izq = actual->der;
                        delete actual;
                    }
                }
            }
        } else {
            const T siguiente = this->siguiente(actual->valor);
            this->remover(siguiente);
            actual->valor = siguiente;
            _longitud++;
        }
    }
    _longitud--;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    if (this->pertenece(clave)) {
        Nodo *actual = _raiz;
        Nodo *siguiente = _raiz;
        while (clave != actual->valor) {
            if (clave > actual->valor)
                actual = actual->der;
            else if (clave < actual->valor) {
                siguiente = actual;
                actual = actual->izq;
            }
        }
        if (actual->der != nullptr) {
            actual = actual->der;
            while (actual->izq != nullptr) {
                actual = actual->izq;
            }
            return actual->valor;
        } else {
            return siguiente->valor;
        }
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    if(_raiz->izq == nullptr){
        return _raiz->valor;
    }
    Nodo* actual = _raiz->izq;
    while (actual->izq != nullptr){
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    if(_raiz->der == nullptr){
        return _raiz->valor;
    }
    Nodo* actual = _raiz->der;
    while (actual->der != nullptr){
        actual = actual->der;
    }
    return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _longitud;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

