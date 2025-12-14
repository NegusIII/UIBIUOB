#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <cctype> // Para toupper

#include "diccionary.h"
#include "letters_set.h"
using namespace std;

int main(int argc, char* argv[]) {
    //1-Comprobamos que la cantidad de parametros es correcta
    if (argc != 4) {
        cout << "Error: Numero de parametros incorrecto." << endl;
        cout << "Uso: " << argv[0] << <fichero_diccionario> <fichero_letras> <fichero_salida>" << endl;
        return 1;
    }

    //2-Cargamos el diccionario
    Diccionario D;
    ifstream f_dict(argv[1]);
    if (!f_dict) {
        cout << "Error: No se ha podido abrir el fichero diccionario: " << argv[1] << endl;
        return 1;
    }
    f_dict >> D; //Usando el operator >> de la clase diccionary

    //3-Cargams el conjunto de letras original
    //Lo usamos para saber los caracteres que debemos contar
    LettersSet letras_info;
    ifstream f_letras(argv[2]);
    if (!f_letras) {
        cout << "Error: No se ha podido abrir el fichero letras: " << argv[2] << endl;
        return 1;
    }
    f_letras >> letras_info;

    //4-Contamos las apariciones
    //Usamos un map para contar las veces que aparece cada letra en todo el diccionario
    map<char, int> conteo;

    //Inicializamos el mapa con las letras validas a cero
    const map<char, LettersSet::LetterInfo>& mapa_letras = letras_info.getLetters();
    map<char, LettersSet::LetterInfo>::const_iterator it_let;

    for (it_let = mapa_letras.begin(); it_let != mapa_letras.end(); ++it_let) {
        conteo[it_let->first] = 0;
    }

    //Ahora recorremos el diccionario completo
    Diccionario::iterator it_dict;
    for (it_dict = D.begin(); it_dict != D.end(); ++it_dict) {
        string palabra = *it_dict; //Obtenemos la palabra

        //Recorremos la palabra caracter a caracter y vamos contando las veces que aparece cada uno
        //Solo si existen en el conjunto de letras que ya tenemos
        for (unsigned int i = 0; i < palabra.length(); i++) {
            char c = toupper(palabra[i]);

            //Si la letra existe en nuestro conjunto sumamos 1
            if (conteo.count(c)) {
                conteo[c]++;
            }
        }
    }

    //5-Calculamos maximos y minimos para calcular posteriormente los puntos
    //Necesitamos saber cual es la letra que mas veces aparece y cual la que menos
    int max_freq = 0;
    int min_freq = 2000000000; //Cogemos un numero muy grande inicialmente

    map<char, int>::iterator it_count;
    for (it_count = conteo.begin(); it_count != conteo.end(); ++it_count) {
        if (it_count->second > max_freq) {
            max_freq = it_count->second;
        }
        if (it_count->second < min_freq) {
            min_freq = it_count->second;
        }
    }

    //6-Escribimos el fichero de salida que en nuestro caso sera letras.txt
    ofstream f_out(argv[3]);
    if (!f_out) {
        cout << "Error: No se ha podido crear el fichero de salida: " << argv[3] << endl;
        return 1;
    }

    //Escribimos la cabecera
    f_out << "#Letra Cantidad Puntos" << endl;

    //Recorremos el mapa de conteos para calcular la puntuacion y escribir
    for (it_count = conteo.begin(); it_count != conteo.end(); ++it_count) {
        char letra = it_count->first;
        int cantidad = it_count->second;
        int puntos = 0;

        //La formula lo que hace es que:
        //max_freq -> 1 punto
        //min_freq -> 10 puntos

        if (max_freq != min_freq) {
            //Formula: 1 + (9*(Max - Actual)) / (Max - Min)
            puntos = 1 + (9*(max_freq - cantidad))/(max_freq - min_freq);
        }
        else {
            puntos = 1;
        }

        //Si la cantidad es 0 (no aparece en el diccionario), los puntos se quedan a cero
        if (cantidad == 0) puntos = 0;

        f_out << letra << "\t" << cantidad << "\t" << puntos << endl;
    }

    //Cerramos los ficheros
    f_dict.close();
    f_letras.close();
    f_out.close();

    return 0;
}