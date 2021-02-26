
#include "string_map.h"
using namespace std;
template <typename T>
string_map<T>::string_map():raiz(nullptr),_size(0){
    // COMPLETAR
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if(d._size!=0)
	buscar(d.raiz,"",this);
    return *this;
}


template<typename T>
void string_map<T> :: buscar(const Nodo* nodo,string clave, string_map<T>* copia){
    for (int i = 0 ; i<256;i++){
	Nodo* sig = nodo->siguientes[i];

	if(sig != nullptr){
	    if( sig->definicion != nullptr){
		copia->insert(make_pair(clave+char(i),*sig->definicion));
	    }

	    buscar(sig,clave+char(i),copia);
	}
    }
}



template <typename T>
string_map<T>::~string_map(){
    if(raiz != nullptr){
	borrar(raiz);
    }
}
template<typename T>
void string_map<T>::borrar(Nodo* nodo){
    for(int i=0;i<256;i++){
        if(nodo->siguientes[i]!= nullptr) {
            borrar(nodo->siguientes[i]);
        }
    }
    if(nodo->definicion != nullptr){
        delete  nodo->definicion;
    }
    delete nodo;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    T* t= new T;
    if(raiz == nullptr)
	    raiz = new Nodo();
    Nodo* nodo = raiz;
    for(unsigned int i = 0 ; i<clave.size();i++){

        if(nodo->siguientes[clave[i]] == nullptr) {
                nodo->siguientes[clave[i]] = new Nodo();
        }
        nodo = nodo->siguientes[clave[i]];

    }
    if(nodo->definicion != nullptr)
	*t= *nodo->definicion;
    nodo -> definicion = t;
    return *t;



}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz == nullptr){
	    return 0;
    }
    Nodo* nodo = raiz;
    for(unsigned int i = 0; i<clave.size();i++){
	if(nodo->siguientes[clave[i]] == nullptr)
	    return 0;
	nodo = nodo->siguientes[clave[i]];
    }
    if(nodo->definicion != nullptr){
        return 1;
    }else{
        return 0;
    }

}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* nodo = raiz;
    for(unsigned int i = 0 ; i<clave.size();i++){
	nodo = nodo->siguientes[clave[i]];
    }
    T& result = *nodo->definicion;
    return result;
}


template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
    Nodo* nodo = raiz;
    for(unsigned int i = 0 ; i<clave.size();i++){
	nodo = nodo->siguientes[clave[i]];
    }
    return *nodo->definicion;
} 

template <typename T>
void string_map<T>::erase(const string& clave) {
    if(this->count(clave)==1) {
        _size--;
        Nodo *nodo = raiz;
        Nodo *ult = nullptr;
        int pos = 0;
        for (unsigned int i = 0; i < clave.size(); i++) {
            nodo = nodo->siguientes[clave[i]];
            int hijos = 0;
            for (int e = 0; e < 256; e++) {
                if (nodo->siguientes[e] != nullptr)
                    hijos++;
            }
            if (nodo->definicion != nullptr || hijos > 1) {
                ult = nodo;
                pos = i;
            }
        }
        if (ult == nodo) {
            T *aBorrar = nodo->definicion;
            nodo->definicion = nullptr;
            delete aBorrar;
        } else {
            nodo = ult->siguientes[clave[pos]];
            ult->siguientes[clave[pos]] = nullptr;
            for (unsigned int i = pos + 1; i < clave.size(); i++) {
                ult = nodo;
                nodo = nodo->siguientes[clave[i]];
                if (ult->definicion != nullptr) {
                    T *aBorrarB = nodo->definicion;
                    nodo->definicion = nullptr;
                    delete aBorrarB;
                }

                delete ult;
            }
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size==0;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &par) {
    if (this->count(par.first) == 0)
        _size++;
    if (raiz == nullptr)
        raiz = new Nodo();
    Nodo *nodo = raiz;
    for (int i = 0; i < par.first.size(); i++) {
        if (nodo->siguientes[par.first[i]] == nullptr)
            nodo->siguientes[par.first[i]] = new Nodo();
        nodo = nodo->siguientes[par.first[i]];
    }
    if (nodo->definicion != nullptr) {
        T *aBorrar = nodo->definicion;
        nodo->definicion = nullptr;
        delete aBorrar;
    }
    T *def = new T;
    *def = par.second;
    nodo->definicion = def;


}
