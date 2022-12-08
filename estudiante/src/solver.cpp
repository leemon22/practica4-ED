//
// Created by usuario on 5/12/22.
//

#include "solver.h"

/** Solver *////////////////////////////////////////////////////////////////////////////////////////////////////////////

Solver::Solver(const Dictionary &dic, const LettersSet &letters_set) {

}

pair<vector<string>, int> Solver::getSolutions(const vector<char> &available_letters, bool score_game) {

}

/** Solver Eficiente *//////////////////////////////////////////////////////////////////////////////////////////////////

EfficientSolver::EfficientSolver(const Dictionary &dic, const LettersSet &letters_set):
    dic(dic), letters_set(letters_set), points(0), sol_words()
{}

void EfficientSolver::borrarSoluciones() {

    points = 0;
    sol_words.clear();
}

pair<vector<string>, int> EfficientSolver::getSolutions(const vector<char> &available_letters, bool score_game) {

    // Borramos la información de la partida anterior
    borrarSoluciones();

    // Iteramos
    for(Dictionary::possible_words_iterator it = dic.possible_words_begin(available_letters); it != dic.possible_words_end(); ++it){

        // Resuelvo según el juego
        if(score_game)
            jugarPorPuntuacion(*it);
        else
            jugarPorLongitud(*it);
    }

    return {sol_words, points};
}

void EfficientSolver::jugarPorLongitud(const std::string &palabra) {

    if(sol_words.empty()){
        aniadirSolucion(palabra);
        points = palabra.length();
    }
    else if(palabra.length() == sol_words[0].length()){
        aniadirSolucion(palabra);
    }
    else if(palabra.length() > sol_words[0].length()){
        borrarSoluciones();
        aniadirSolucion(palabra);
        points = palabra.length();
    }
}

void EfficientSolver::jugarPorPuntuacion(const std::string &palabra) {

    if(sol_words.empty()){
        aniadirSolucion(palabra);
        points = getScore(palabra);
    }
    else{
        int puntuacion = getScore(palabra);

        if(puntuacion > points){
            borrarSoluciones();
            aniadirSolucion(palabra);
            points = puntuacion;
        }
        else if(puntuacion == points){
            aniadirSolucion(palabra);
        }
    }
}