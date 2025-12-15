#include "bag.h"
#include "dictionary.h"
#include "letters_bag.h"
#include "letters_set.h"

#include <iostream>
#include <fstream>

using namespace std;


/*
./bin/letras ./data/diccionario.txt ./data/letras.txt 8 L
./bin/letras ./data/diccionario.txt ./data/letras.txt 8 P
 */

void Imprimir(string archivo) {
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

void calcular() {


}

int main(int argc, char *argv[]) {

    if (argc != 5) {
        cout << "Error: Numero de parametros incorrecto." << endl;
        return 1;
    }

    if (argv[4][0] != 'L' && argv[4][0] != 'P') {
        cout << "Error en el tipo de puntuacion" << endl;
        return 1;
    }

    if (argv[4][0] =='P') {
        Imprimir(argv[2]);
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

    vector<char> letras = bolsa_letras.extraer_varias(n_letras);

    cout << "Las letras son: ";
    for (int i = 0; i < n_letras; i++) {

        cout << letras[i] << " ";
    }
    cout << endl;

    cout << "Dime tu solucion: ";
    string solucion;
    getline(cin, solucion);
    cout << endl << endl;




    return 0;
}
