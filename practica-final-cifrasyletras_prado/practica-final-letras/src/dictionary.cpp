#include "dictionary.h"

#include <set>
#include <string>

Diccionario::Diccionario():datos(){}

int Diccionario::size() const {
    return datos.size();
}
vector<string> Diccionario::PalabrasLongitud(int longitud) {

    vector<string> v;

    for (set<string>::iterator it=datos.begin(); it !=datos.end(); ++it) {

        if (*it->length()==longitud) v.push_back(*it);
    }
    return v;
}

bool Diccionario::Esta(string palabra) {
    return (datos.find() != datos.end());
}

//METODOS DE LA CLASE ITERATOR
Diccionario::iterator::operator*{
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

ostream & operator<<(ostream & os, Diccionario &D) {
    set<string>::const_iterator it;

    for (it = D.datos.begin(); it != D.datos.end(); ++it) {
        os << *it << endl;
    }
    return os;
}