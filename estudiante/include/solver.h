//
// Created by usuario on 5/12/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#endif //P04_JUEGO_LETRAS_SOLVER_H

#include "letters_set.h"
#include "letters_bag.h"
#include "dictionary.h"
#include <vector>
#include <utility>

class Solver {
private:
    vector<string> sol_words;
    int points;
public:
    Solver(const Dictionary & dic, const LettersSet & letters_set);
    pair<vector<string>,int> getSolutions (const vector <char> & available_letters, bool score_game);

};

/**
 * @brief T.D.A Solver Eficiente
 * Resuelve el Juego de las letras de forma más eficiente que el T.D.A porque usa iteradores inteligentes.
 */
class EfficientSolver{
private:
    /** @brief Vector de soluciones */
    vector<string> sol_words;
    /** @brief Puntuación de las soluciones */
    int points;

    /** @brief Conjunto de letras en el que va a mirar la puntuación de las letras */
    LettersSet letters_set;
    /** @brief Diccionario donde mirará las palabras válidas */
    Dictionary dic;

    /**
     * @brief Añade o no la palabra según su puntuación
     * @param palabra Palabra candidata a ser solución
     */
    void jugarPorPuntuacion(const string &palabra);

    /**
     * @brief Añade o no la palabra según su longitud
     * @param palabra Palabra candidata a ser solución
     */
    void jugarPorLongitud(const string &palabra);

    /**
     * @brief Deja vacío el vector de soluciones
     */
    void borrarSoluciones();

    /**
     * @brief Añade la palabra al vector de soluciones
     * @param palabra Palabra añadida a las soluciones
     */
    void aniadirSolucion(const string &palabra){ sol_words.push_back(palabra);};

    /**
     * @brief Devuelve la puntuación de una palabra
     * @param palabra Palabra a la que queremos mirar su puntuación
     * @return Puntuación de la palabra
     */
    int getScore(const string &palabra){ return letters_set.getScore(palabra);};

public:

    /**
     * @brief Constructor con parámetros.
     * @param dic Diccionario sobre el que resolverá
     * @param letters_set LetterSet sobre el que calculará puntuaciones.
     */
    EfficientSolver(const Dictionary & dic, const LettersSet & letters_set);

    /**
     * @brief Resuelve el Juego de las Letras
     * @param available_letters Letras disponibles para la partida
     * @param score_game Indica el tipo de partida. True si resuelve por puntuación, false si resuelve por longitud
     * @return {el vector de mejores soluciones, la puntuación (longitud o puntuación según el letters_set)}
     */
    pair<vector<string>,int> getSolutions (const vector <char> & available_letters, bool score_game);
};