//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Dictionary {
private:
    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        inline bool operator==(const char_info &rhs) {
          return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        inline bool operator*() { return this->character; }

        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
          os << other.character << (other.valid_word ? "✓" : "×");
          return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    int getOccurrences(node curr_node, char c);

    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    int getOccurrences(const char c);

    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    class iterator {
    private:
        std::string curr_word;
        tree<char_info>::const_preorder_iterator iter;

    public:

        iterator();

        iterator(tree<char_info>::const_preorder_iterator iter);

        std::string operator*();

        iterator &operator++();

        bool operator==(const iterator &other);

        bool operator!=(const iterator &other);

    };

    iterator begin() const;

    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    /**
     * @brief T.D.A Iterador Inteligente:
     * Esta clase itera por las palabras del diccionario que contienen las letras pasadas al constructor por parámetros
     */
    class possible_words_iterator {
    public:

        /**
         * @brief Constructor por defecto (usado por la función possible_words_end())
         */
        possible_words_iterator();

        /**
         * @brief Constructor con parámetros
         * @param current_node Nodo donde empezará el iterador.
         * @param available_letters Letras que usará para iterar por el diccionario.
         */
        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
         * @brief Constructor de copia.
         * @param other El otro iterador.
         */
        possible_words_iterator(const possible_words_iterator &other);

        /**
         * @brief Sobrecarga del operador asignación.
         * @param other El otro iterador.
         * @return *this para encadenar asignaciones.
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
         * @brief Operador igual.
         * @param other Iterador al que queremos comparar.
         * @return True si los iteradores apuntan al mismo nodo y comparten la misma palabra.
         */
        bool operator==(const possible_words_iterator &other) const;

        /**
         * @brief Operador distinto.
         * @param other Iterador al que queremos comparar.
         * @return True si los iteradores NO apuntan al mismo nodo o NO comparten la misma palabra.
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Avanza el iterador por el diccionario.
         * @return *this para encadenar incrementos.
         */
        possible_words_iterator &operator++();

        /**
         * @brief Operator dereference.
         * @return La palabra almacenada en el iterador.
         */
        std::string operator*() const;

    private:
        multiset<char> available_letters;
        int level;
        node current_node;
        string current_word;
    };

    /**
     * @brief iterador inteligente begin.
     * @param available_characters Letras que usará el iterador para avanzar.
     * @return El iterador apuntando a la primera palabra válida en el diccionario. Si no la encuentra, apuntará al nodo nulo padre.
     */
    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
     * @brief iterador inteligente begin.
     * @return Un iterador inteligente apuntando al nodo nulo padre.
     */
    possible_words_iterator possible_words_end() const;
};

#endif //TREE_DICTIONARY_HPP
