#include "letters_set.h"
#include <iostream>

using namespace std;

LettersSet::LettersSet(){}

void LettersSet::Insert(const char & val, const int & cantidad, const int & puntuacion) {
    LetterInfo info;
    info.repeticiones = cantidad;
    info.puntuacion = puntuacion;

    //Guardamos en el mapa con clase val
    letters[val] = info;
}

int LettersSet::getPuntuacion(string palabra) {
    int puntuacion_total = 0;

    for (int i = 0; i < palabra.length(); i++) {
        char c = palabra[i];
        //Convertimos a mayuscula
        c = toupper(c);
        if (letters.count(c)) {
            puntuacion_total += letters.at(c).puntuacion;
        }
    }
    return puntuacion_total;
}

const map<char, LettersSet::LetterInfo>& LettersSet::getLetters() const {
    return letters;
}

//Operador de entrada: lectura de letras.txt
istream & operator>>(istream & is, LettersSet & cl) {
    string cabecera; //La primera linea debemos saltarla
    //Saltamos la cabecera
    getline(is, cabecera);

    char letra;
    int cantidad, puntos;
    //Luego leemos mientras haya datos

    while (is >> letra >> cantidad >> puntos) {
        cl.Insert(letra, cantidad, puntos);
    }
    return is;
}

//Operador de salida
ostream & operator<<(ostream & os, const LettersSet & cl) {
    os << "Letras\tCantidad\tPuntos" << endl;

    map<char, LettersSet::LetterInfo>::const_iterator it;

    for (it = cl.letters.begin(); it != cl.letters.end(); ++it) {
        //it->first (es la clave)
        //it->second (es el struct LetterInfo)
        os << it->first << "\t"
            << it->second.repeticiones << "\t"
            << it->second.puntuacion << endl;
    }
    return os;
}

