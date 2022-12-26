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

/**
 * @brief T.D.A Solver
 * Resuelve el Juego de las letras (ya sea a puntuación o a longitud de palabras).
 */
class Solver {
private:

    /**
     * @brief Solución de una partida del juego.
     */
    vector<string> sol_words;

    /**
     * @brief Puntos obtenidos en una partida.
     */
    int points;

    /**
     * Diccionario con las palabras con las que se juega.
     */
    Dictionary dic;

    /**
     * Conjunto de letras que servirá como consulta de puntuación de cada letra.
     */
    LettersSet letters_set;
    //LettersBag bag;
public:

    /**
     * @brief Constructor con argumentos. Inicializa una partida del juego de las letras con un diccionario @param dic
     * @brief y un conjunto de letras @param letters_set determinados.
     * @param dic Diccionario con el que se va a jugar al juego de las letras.
     * @param letters_set Conjunto de letras con el que se va a jugar.
     */
    Solver(const Dictionary & dic, const LettersSet & letters_set);

    /**
     * @brief Juega una partida del juego de las letras. Dada una serie de letras disponibles @param available_letters,
     * @brief y un modo de juego score_game, determina las palabras que tienen la longitud (@param score_game = false)
     * @brief o la puntuación (@param score_game = true) más alta posible
     * @param available_letters Letras con las que se dispone para formar palabras.
     * @param score_game Modo de juego (puntuación si es true, longitud si es false).
     * @return Palabras formadas con la longitud o puntuación más alta, así como dicha longitud o puntuación.
     */
    pair<vector<string>,int> getSolutions (const vector <char> & available_letters, bool score_game);
private:

    /**
     * @brief Función auxiliar que determina si se puede formar la palabra @param word con las letras @param available_letters
     * @param word Palabra a estudiar.
     * @param available_letters Letras disponibles.
     * @return True si se puede formar la palabra @param word, false en otro caso.
     */
    bool PalabraDisponible(string word, const vector<char> & available_letters);

    /**
     * @brief Función auxiliar que indica si la palabra @param pal supera la longitud o puntuación máxima
     * @brief (dependiendo del tipo de juego dado por @param score_game).
     * @brief De superar la puntuación o longitud máxima, se actualizará dicho valor con el correspondiente a @param pal.
     * @param pal Palabra a estudiar.
     * @param score_game Tipo de juego (True si es a puntuación, false si es a longitud).
     * @return True si se supera la puntuación o longitud máximas, false en otro caso.
     */
    bool SuperaMax(string pal, bool score_game);

    /**
     * @brief Función auxiliar que indica si la palabra @param pal tiene la longitud o puntuación máxima
     * @brief (dependiendo del tipo de juego dado por @param score_game).
     * @param pal Palabra a estudiar.
     * @param score_game Tipo de juego (True si es a puntuación, false si es a longitud).
     * @return True si @param pal tiene la puntuación o longitud máximas, false en otro caso.
     */
    bool IgualQueMax(string pal, bool score_game);

    /**
     * @brief Añade la palabra @param word al vector de soluciones.
     * @param word palabra a añadir.
     */
    void AniadirPalabra(string word);

    /**
     * @brief Restaura la solución de la partida, limpiando el vector de soluciones y poniendo
     * @brief puntuación a 0.
     */
    void InicializarSolucion();

    /**
     * @brief Limpia el vector de soluciones.
     */
    void LimpiarSolucion();
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
     * @return Puntuación de la palabra.
     */
    int getScore(const string &palabra);

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