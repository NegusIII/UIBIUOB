#ifndef __BAG_H__
#define __BAG_H__
#include <cstdlib>
#include <stdlib.h>
#include <vector>

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */
template <class T>
class Bag {
private:
    vector<T> v;

public:
    /**
     * @brief Constructor por defecto
     * Crea una bolsa vacia
     */
    Bag() {}

    /**
     * @brief Constructor de copia
     * @param other: la otra bolsa a copiar
     */
    Bag(const Bag<T> & other) {
        v = other.v;
    }

    /**
     * @brief Añade un elemento a la bolsa
     * @param elemento: Elemento a añadir
     */
    void add(const T & elemento) {
        v.push_back(elemento);
    }

    /**
     * @brief Extrae un elemento aleatorio de la bolsa
     * Elimina el elemento de la bolsa una vez se saca
     * @return El elemento extraido
     * @pre La bolsa no debe ser vacia
     */
    T get() {
        //Elegimos una posicion aleatoria dentro del tamaño del vector
        int index = rand() % v.size();

        //Guardamos el emento que vamos a devolver
        T elemento = v[index];

        //Como el orden no importa en la bolsa, lo que hacemos es copiar el
        //ultimo elemento del vector en la posicion index y borramos el ultimo
        v[index] = v[v.size() - 1];
        v.pop_back();

        return elemento;
    }

    /**
     * @brief Devuelve el numero de elementos en la bolsa
     * @return Numero de elementos
     */
    int size() {
        return v.size();
    }

    /**
     * @brief Comprueba si la bolsa esta vacia
     * @return 'true' si esta vacia, 'false' en caso contrario
     */
    bool empty() {
        return (v.empty());
    }

    /**
     * @brief Operador de asignacion
     * @param other: la bolsa a copiar
     * @return Referencia a la bolsa modificada
     */
    const Bag<T> & operator=(const Bag<T> & other) {
        if (this != &other) {
            v = other.v;
        }
        return (*this);
    }
};
#endif
