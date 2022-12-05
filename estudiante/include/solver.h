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