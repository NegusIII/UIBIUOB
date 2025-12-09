#include "dictionary.h"

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