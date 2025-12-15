#include "bag.h"
#include "dictionary.h"
#include "letters_bag.h"
#include "letters_set.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;


/*
./bin/letras ./data/diccionario.txt ./data/letras.txt 8 L
./bin/letras ./data/diccionario.txt ./data/letras.txt 8 P
 */

void Imprimir(string &archivo) {
    ifstream input(archivo);
    if (!input) {
        cout << "no se ha podido abrir el archivo" << endl;
    }
    else {
        string linea;
        while (getline(input, linea)) {
            cout << linea << endl;
        }
    }
}

int Puntuacion(string palabra, char tipo, LettersSet set) {
    if (tipo=='L') {
        return palabra.length();
    }
    return set.getPuntuacion(palabra);
}

vector<string> Posibles(Diccionario &D, vector<char> letras) {
    vector<string> posibles;
    Diccionario::iterator it;
    for (it = D.begin(); it != D.end(); ++it) {
        string palabra = *it;
        bool valido = true;
        vector<char> copia = letras;
        int i=0;
        while (i<palabra.size() && valido){
            char letra=toupper(palabra[i]);
            vector<char>::iterator it2;
            it2=find(copia.begin(), copia.end(), letra);
            if (it2==copia.end()){
                valido=false;
            }
            else{
                copia.erase(it2);
                i++;
            }
        }
        if (valido) posibles.push_back(palabra);
    }
    return posibles;
}

vector<string> calcularMejores(int puntuacion, char tipo, LettersSet set, vector<string> posibles){
    vector<string> soluciones;
    vector<string>::iterator it;
    for (it = posibles.begin(); it != posibles.end(); ++it) {
        string palabra = *it;
        if (Puntuacion(palabra, tipo, set) >= puntuacion){
            soluciones.push_back(palabra);
        }
    }

    return soluciones;
}

vector<string>::iterator MejorPuntuacion(int puntuacion, char tipo, LettersSet set, vector<string> posibles) {

    vector<string> soluciones = calcularMejores(puntuacion, tipo, set, posibles);
    vector<string>::iterator it;
    vector<string>::iterator mejor;
    int mejor_puntuacion = 0;

    for (it = soluciones.begin(); it !=soluciones.end(); ++it) {
        if (Puntuacion(*it, tipo, set) > mejor_puntuacion) {
            mejor_puntuacion = Puntuacion(*it, tipo, set);
            mejor = it;
        }
    }
    return mejor;
}

int main(int argc, char *argv[]) {

    bool continuar = true;

    if (argc != 5) {
        cout << "Error: Numero de parametros incorrecto." << endl;
        return 1;
    }

    if (argv[4][0] != 'L' && argv[4][0] != 'P') {
        cout << "Error: Tipo de puntuacion incorrecto." << endl;
        return 1;
    }

    if (argv[4][0] =='P') {
        string imprimir = argv[2];
        Imprimir(imprimir);
    }
    Diccionario D;

    ifstream archivo_diccionario(argv[1]);
    if (!archivo_diccionario) {
        cout << "Error: No se ha podido abrir el fichero diccionario: " << argv[1] << endl;
        return 1;
    }
    archivo_diccionario >> D;

    LettersSet letras_info;
    ifstream archivo_letras(argv[2]);
    if (!archivo_letras) {
        cout << "Error: No se ha podido abrir el fichero letras: " << argv[2] << endl;
        return 1;
    }

    archivo_letras >> letras_info;
    LettersBag bolsa_letras(letras_info);
    int n_letras=stoi(argv[3]);
    do {
        vector<char> letras = bolsa_letras.extraer_varias(n_letras);
        vector<string> posibles = Posibles(D, letras);

        cout << "Las letras son: ";
        for (int i = 0; i < n_letras; i++) {

            cout << letras[i] << " ";
        }
        cout << endl;

        string solucion;
        do {
            cout << "Dime tu solucion: ";
            getline(cin, solucion);
        }while (find(posibles.begin(), posibles.end(), solucion) == posibles.end());

        cout << endl << endl;
        int puntuacion=Puntuacion(solucion, argv[4][0], letras_info);

        cout << left << setw(8) << solucion << "   Puntuacion:" <<  puntuacion << endl;
        cout << "Mis soluciones son: " << endl;

        vector<string> soluciones = calcularMejores(puntuacion, argv[4][0], letras_info,posibles);
        for (int i = 0; i < soluciones.size(); i++) {
            cout << left << setw(8) << soluciones[i] << "   Puntuacion:  " << Puntuacion(soluciones[i], argv[4][0], letras_info) << endl;
        }
        cout << endl;

        vector<string>::iterator mejor = MejorPuntuacion(puntuacion, argv[4][0], letras_info, posibles);

        cout << "La mejor solucion es: " << *mejor << " con una puntuacion de " << Puntuacion(*mejor, argv[4][0], letras_info) << endl;
        string seguir;
        do {
            cout << "¿Quieres seguir jugando? [S/N]: ";

            getline(cin, seguir);
        }while (seguir != "S" && seguir != "N");
        if (seguir == "N") {
            continuar = false;
        }
    }
    while (continuar);

    return 0;
}
