#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include <map>
#include <iostream>


/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */
class LettersSet {

public:

    struct LetterInfo {
        int repeticiones;
        int puntuacion;
    };
private:
    //Creamos un registro interno para guardar la informacion sobre cada letra

    //Usamos un map para asociar cada caracter con su informacion, de esta forma
    //es mas sencillo encontrar los puntos asociados a una letra concreta
    std::map<char, LetterInfo> letters;

public:
    /**
     * @brief Constructor por defecto
     */
    LettersSet();

    /**
     * @brief Metodo que inserta una letra en el conjunto
     * @param val: caracter de la letra
     * @param cantidad: cantidad de veces que aparece la letra
     * @param puntuacion: puntuacion de la letra
     */
    void Insert(const char & val, const int & cantidad, const int & puntuacion);

    /**
     * @brief Calcula la puntuacion de una palabra completa
     * @param palabra: palabra a evaluar
     * @return Suma de los puntos de cada letra. Devuelve 0 si alguna letra no existe
     */
    int getPuntuacion(std::string palabra);

    /**
     * @brief Obteine el mapa completo de letras (sera util para la Bolsa)
     * @return Referencia constante al mapa interno de la clase
     */
    const std::map<char, LetterInfo>& getLetters() const;

    /**
     * @brief Sobrecarga del operador de entrada
     * Lee el archivo letras.txt saltandose la cabecera
     */
    friend std::istream & operator>>(std::istream & is, LettersSet & cl);

    /**
     * @brief Sobrecarga del operador de salida
     * Muestra las letras y sus propiedades
     */
    friend std::ostream & operator<<(std::ostream & os, const LettersSet & cl);

};
#endif
