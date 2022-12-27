//
// Created by usuario on 5/12/22.
//

#include "solver.h"
#include "algorithm"

/** Solver *////////////////////////////////////////////////////////////////////////////////////////////////////////////

Solver::Solver(const Dictionary &dic, const LettersSet &letters_set) : sol_words(), points(0), dic(dic), letters_set(letters_set) {}

pair<vector<string>, int> Solver::getSolutions(const vector<char> &available_letters, bool score_game) {
    InicializarSolucion();
    string word;
    for (Dictionary::iterator it = dic.begin(); it != dic.end(); ++it) {
        word = ToUpper(*it);
        if(PalabraDisponible(word,available_letters)) {
            if (SuperaMax(word, score_game)) {
                LimpiarSolucion();
                AniadirPalabra(*it);

            } else if (IgualQueMax(word, score_game)) {
                AniadirPalabra(*it);
            }
        }
    }

    return {sol_words,points};
}

void Solver::InicializarSolucion() {
    LimpiarSolucion();
    points = 0;
}
void Solver::LimpiarSolucion() {
    sol_words.clear();
}

bool Solver::SuperaMax(string pal, bool score_game) {
    bool supera = false;
    int score_pal = 0;

    if (score_game) {
        score_pal = letters_set.getScore(pal);
    }

    else {
        score_pal = pal.length();
    }

    if (score_pal > points) {
        supera = true;
        points = score_pal;
    }


    return supera;
}



bool Solver::IgualQueMax(string pal, bool score_game) {
    bool igual = false;
    int score_pal = 0;

    if (score_game) {
        score_pal = letters_set.getScore(pal);
    }

    else {
        score_pal = pal.length();
    }


    if (score_pal == points) {
        igual = true;
    }

    return igual;
}

bool Solver::PalabraDisponible(string word, const vector<char> & available_letters) {
    bool disponible = true;
    int i = 0;
    int word_length = word.length();

    while (disponible && i < word_length) {
        if (count(word.begin(),word.end(), word.at(i)) > count(available_letters.begin(), available_letters.end(),word.at(i))  ) {
            disponible = false;
        }
        ++i;
    }
    return disponible;
}

void Solver::AniadirPalabra(string word) {
    sol_words.push_back(word);
}

string Solver::ToUpper(string word) {

    string palabra_may;
    for(char c: word)
    palabra_may += toupper(c);

    return palabra_may;
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

int EfficientSolver::getScore(const string &palabra){

    string palabra_may;
    for(char c: palabra)
        palabra_may += toupper(c);

    return letters_set.getScore(palabra_may);
}