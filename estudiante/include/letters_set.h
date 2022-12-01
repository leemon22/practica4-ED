/**
 * @file letters_set.h
 * @brief Archivo de especificación de los TDA LetterInfo y TDA LettersSet
 * @author Pedro Javier Pérez Jiménez
 * @author Alejandro Martínez del Castillo
 */

#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include <map>
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado caracter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */
struct LetterInfo {
    int repetitions;
    int score;
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra.
 */
class LettersSet{

private:

    /**
     * @brief El map que relaciona las letras con su información correspondiente.
     */
    map<char,LetterInfo> letters;

public:

    /**
     * @brief Constructor por defecto. No hay letras.
     */
    LettersSet();

    /**
     * @brief Constructor de copia.
     * @param other LettersSet del que se copia la información.
     */
    LettersSet(const LettersSet &other);

    /**
     * @brief @b Inserta el elemento val en el LettersSet.
     * @param val Par {letra, LetterInfo} asociados que se quiere insertar.
     * @return True si se ha podido insertar la letra en el LettersSet. @val solo se inserta si
     * la letra no estaba en el conjunto.
     */
    bool insert(const pair<char,LetterInfo> &val);

    /**
     * @brief @b Borra el elemento con clave @b key.
     * @param key La clave del elemento.
     * @return Devuelve true si el elemento con clave key existía y se ha borrado.
     */
    bool erase(const char &key);

    /**
     * @brief Limpia todo el contenido del LettersSet
     */
    void clear();

    /**
     * @brief Comprueba que el conjunto está vacío.
     * @return True si no hay elementos en el LettersSet.
     */
    bool empty() const;

    /**
     * @brief El tamaño de LettersSet.
     * @return El número de elementos en LettersSet.
     */
    unsigned int size() const;

    /**
     * @brief Calcula la puntuación de una palabra.
     * @param word Palabra a la que se le quiere calcular su puntuación.
     * @return La puntuación de la palabra.
     */
    int getScore(string word) const;

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param cl LettersSet del que se quiere copiar los elementos.
     * @return Referencia a *this para poder encadenar asignaciones.
     */
    LettersSet &operator=(const LettersSet &cl);

    /**
     * @brief Sobrecarga del operador de consulta. Nos permite acceder a los elementos de la clase.
     * @param val Letra a la que queremos acceder a sus elementos.
     * @return La información asociada a @b val, {número de repeticiones, puntuación}.
     */
    LetterInfo &operator[](const char &val);

    /**
     * @brief Clase iteradora de LettersSet.
     */
    class const_iterator;

    /**
     * @brief Iterador inicial.
     * @return Un iterador al elemento en la primera posición de LettersSet.
     */
    LettersSet::const_iterator begin() const;

    /**
     * @brief Iterador final.
     * @return Devuelve un iterador a la posición siguiente al último elemento.
     */
    LettersSet::const_iterator end() const;

    /**
     * @brief Sobrecarga del operador de salida.
     * @param os Flujo de salida.
     * @param cl El LetterSel escrito en el flujo de salida.
     * @return El flujo de salida, para poder encadenar operaciones de salida.
     * @post El el flujo de salida se escribirá en cada línea la informción de cdada letra de
     * LettersSet con el siguente formato:
     * <letra>  <nº repeticiones>   <puntuación>
     * Donde los campos están separados por tabulaciones.
     */
    friend ostream &operator<<(ostream &os, const LettersSet &cl);

    /**
     * @brief Sobrecarga del operador de entrada.
     * @param is Flujo de entrada.
     * @param cl LettersSet donde se insertará la entrada.
     * @return El flujo de entrada, para poder encadenar operaciones de entrada.
     * @pre El formato de la entrada debe ser:
     * <letra>  <nº repeticiones>   <puntuación>
     * para poder ser leído correctamente.
     * @post Si la letra ya estaba en cl, no reemplazará a la anterior.
     * @brief Esta función lee los datos de la entrada de elemento a elemento.
     */
    friend istream &operator>>(istream &is, LettersSet &cl);

};

/**
 * @brief Clase iteradora de LettersSet, con todos los métodos para poder funcionar
 * correctamente como iterador.
 */
class LettersSet::const_iterator {

private:
    map<char,LetterInfo>::const_iterator it;
public:

    /**
     * @brief Constructor por defecto.
     */
    const_iterator() = default;
    /**
     * @brief Constructor de copia.
     * @param other Otro objeto del que se hace la copia.
     */
    const_iterator(const const_iterator &other) = default;
    /**
     * @brief Destructor.
     */
    ~const_iterator() = default;
    /**
     * @brief Sobrecarga del operador asignación.
     * @param other Otro objeto del que se hace la copia.
     * @return El mismo para encadenar asignaciones.
     */
    const_iterator &operator=(const const_iterator &other) = default;

    /**
     * @brief Sobrecarga del operador ++.
     * @return El propio iterador apuntando al siguiente elemento.
     */
    const_iterator &operator++();
    /**
     * @brief Sobrecarga del operador --.
     * @return El propio iterador apuntando al anterior elemento.
     */
    const_iterator &operator--();
    /**
     * @brief Sobrecarga del operador *.
     * @return El par <Clave,Valor> al que apunta el iterador.
     */
    const pair<const char, LetterInfo> &operator*() const;

    /**
     * @return Clave a la que apunta el iterador.
     */
    char key() const{return it->first;};

    /**
     * @return Valor al que apunta el iterador.
     */
    LetterInfo value() const{return it->second;};

    /**
     * @brief Sobrecarga del operador ==.
     * @param other Otro objeto con el que se quiere comparar.
     * @return True si los iteradores son iguales.
     */
    bool operator==(const const_iterator &other);
    /**
     * @brief Sobrecarga del operador !=.
     * @param other Otro objeto con el que se quiere comparar.
     * @return True si los iteradores son distintos.
     */
    bool operator!=(const const_iterator &other);

    friend class LettersSet;

};

#endif
