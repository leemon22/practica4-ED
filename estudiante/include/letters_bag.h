#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

#include <bag.h>
#include <vector>
#include <letters_set.h>

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag{

private:
    Bag<char> letters;

public:

    /**
     * @brief Constructor por defecto.
     */
    LettersBag();

    /**
     * @brief Contructor por copia.
     * @param other LettersBag del que se quiere copiar su bolsa de letras
     */
    LettersBag(const LettersBag &other);

    /**
     * @brief Constructor por copia, a partir de un LetterSet.
     * @param letters_set Letters_set del que se va a copiar su conjunto de letras.
     * @pos Se copiará cada letra tantas veces como esté en el letters_set.
     */
    LettersBag(const LettersSet & letters_set);

    /**
     * @brief Inserta una letra a la bolsa
     * @param l Letra que queremos insertar en la bolsa
     */
    void insertLetter(const char &l);

    /**
     * @brief Elimina una letra de la bolsa y la devuelve.
     * @return Letra eliminada de la bolsa.
     * @pre La bolsa no está vacía ( size() > 0 ).
     */
    char extractLetter();

    /**
     * @brief Elimina @b num letras y las devuelve en forma de vector.
     * @param num Número de elementos que se quieren eliminar.
     * @return Un vector con los elementos eliminados.
     * @pre En la bolsa debe haber por lo menos num elementos ().
     */
    vector<char> extractLetters(int num);

    /**
     * @brief Elimina los caracteres de la bolsa
     */
    void clear();

    /**
     * @brief Tamaño de la bolsa
     * @return Número de caracteres dentro de la bolsa
     */
    unsigned int size() const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other LettersBag del que se quiere copiar su bolsa de letras.
     * @return El propio elemento para poder encadenar asignaciones.
     */
    LettersBag &operator=(const LettersBag &other);
};

#endif
