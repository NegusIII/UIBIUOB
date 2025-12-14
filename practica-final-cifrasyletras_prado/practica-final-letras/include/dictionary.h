#ifndef __Diccionario_h__
#define __Diccionario_h__
#include <set>
#include <string>
#include <vector>

using namespace std;

class Diccionario{
private:
    set<string> datos;
public:
    /**
    @brief Construye un diccionario vacío.
    **/
    Diccionario();
    /**
    8
    #Letra Cantidad Puntos
    A 12 1
    E 12 1
    O 9 1
    I 6 1
    S 6 1
    N 5 1
    L 1 1
    R 6 1
    U 5 1
    T 4 1
    D 5 2
    G 2 2
    C 5 3
    B 2 3
    M 2 3
    P 2 3
    H 2 4
    F 1 4
    V 1 4
    Y 1 4
    Q 1 5
    J 1 8
    X 1 8
    Z 1 10
    @brief Devuelve el numero de palabras en el diccionario
    **/
    int size() const ;

    set<string> getDatos();
    /**
    @brief Obtiene todas las palabras en el diccionario de un longitud dada
    @param longitud: la longitud de las palabras de salida
    @return un vector con las palabras de longitud especifica en el parametro de entrada
    **/
    vector<string> PalabrasLongitud(int longitud);
    /**
    @brief Indica si una palabra está en el diccionario o no
    @param palabra: la palabra que se quiere buscar
    @return true si la palabra esta en el diccionario. False en caso contrario
    **/
    bool Esta(string palabra);
    /**
    @brief Lee de un flujo de entrada un diccionario
    @param is:flujo de entrada
    @param D: el objeto donde se realiza la lectura.
    @return el flujo de entrada
    **/
    friend istream & operator>>(istream & is,Diccionario &D);
    /**
    @brief Escribe en un flujo de salida un diccionario
    @param os:flujo de salida
    @param D: el objeto diccionario que se escribe
    @return el flujo de salida
    **/
    friend ostream & operator<<(ostream & os, const Diccionario &D);


    class iterator{
        private:
            set<string>::iterator it;
        public:
            iterator ();

            string operator *();
            iterator & operator ++();
            bool operator ==(const iterator &i);
            bool operator !=(const iterator &i);
            friend class Diccionario;
        };
        iterator begin();
        iterator end();
};

#endif
