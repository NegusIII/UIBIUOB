#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

#include <list>
#include <vector>
#include <iostream>
#include "letters_set.h"



/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag {

    private:
        std::list<char> letras;

    public:
        /**
         * @brief Constructor por defecto
         */
        LettersBag();

        /**
         * @brief constructor de la clase LettersBag que recibe un LettersSet
         * @param letras_info
         */
        LettersBag(const LettersSet & letras_info);

        /**
         * @brief metodo que inserta un caracter en la bolsa
         *
         * @param c
         */
        void insertar(char c);

        /**
         *
         * @return un caracter aleatorio de la bolsa
         */
        char extraer();


        /**
         *
         * @return el tamaño de la bolsa
         */
        int size() const;


        /**
         * @brief vacía la bolsa
         */
        void clear();

        /**
         *
         * @param n numero de letras a extraer
         * @return un vector con n letras extraídas aleatoriamente
         * @pre n<size()
         */
        std::vector<char> extraer_varias(int n);

        friend std::ostream & operator<<(std::ostream & os, const LettersBag & bag);
};

#endif
