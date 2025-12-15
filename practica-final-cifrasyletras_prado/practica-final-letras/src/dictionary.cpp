#include "dictionary.h"

#include <set>
#include <string>
#include <iostream>

using namespace std;

Diccionario::Diccionario():datos(){}

int Diccionario::size() const {
    return datos.size();
}
vector<string> Diccionario::PalabrasLongitud(int longitud) {

    vector<string> v;

    for (set<string>::iterator it=datos.begin(); it !=datos.end(); ++it) {
        string actual = *it;
        if (actual.length()==longitud) v.push_back(actual);
    }
    return v;
}

set<string> Diccionario::getDatos() {
    return datos;
}

bool Diccionario::Esta(string palabra) {
    return (datos.find(palabra) != datos.end());
}

//METODOS DE LA CLASE ITERATOR
string Diccionario::iterator::operator*(){
    return *it;
}

Diccionario::iterator & Diccionario::iterator::operator++() {
    ++it;
    return *this;
}

bool Diccionario::iterator::operator==(const iterator &i) {
    return it == i.it;
}

bool Diccionario::iterator::operator!=(const iterator &i) {
    return it != i.it;
}

//GENERADORES DE ITERADORES
Diccionario::iterator::iterator() {}


Diccionario::iterator Diccionario::begin() {
    Diccionario::iterator i;
    i.it = datos.begin();
    return i;
}

Diccionario::iterator Diccionario::end() {
    Diccionario::iterator i;
    i.it = datos.end();
    return i;
}

//OPERADORES DE ENTRADA Y SALIDA
istream & operator>>(istream & is, Diccionario &D) {
    string palabra;
    while (is>>palabra) {
        D.datos.insert(palabra);
    }
    return is;
}

ostream & operator<<(ostream & os, const Diccionario &D) {
    set<string>::const_iterator it;

    for (it = D.datos.begin(); it != D.datos.end(); ++it) {
        os << *it << endl;
    }
    return os;
}