//
// Created by usuario on 11/12/22.
//

#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include "solver.h"
#include <fstream>

int main(int argc, char *argv[]) {

    if (argc != 5) {
        cerr << "Argumentos incorrectos" << endl;
        exit(-1);
    }

    Dictionary dic;
    LettersSet letters;
    bool score_game = false;
    int num_letters = 0;
    ifstream f_diccionario(argv[1]);


    if (!f_diccionario) {
        cerr << "Error al abrir el archivo " << argv[1] << endl;
        exit(-1);
    }

    f_diccionario >> dic;

    f_diccionario.close();

    ifstream f_letras(argv[2]);
    if (!f_letras) {
        cerr << "Error al abrir el archivo " << argv[2] << endl;
        exit(-1);
    }

    f_letras >> letters;

    f_letras.close();

    if (argv[3] != "L" || argv[3] != "P") {
        cerr << "Modo de juego no disponible" << endl;
        exit(-1);
    }

    if (argv[3] == "P") {
        score_game = true;
    }
    else {
        score_game = false;
    }

    num_letters = atoi(argv[4]);
    if (num_letters <= 0) {
        cerr << "Cantidad de letras inadecuada" << endl;
        exit(-1);
    }
    LettersBag bag(letters);
    vector <char> available_letters = bag.extractLetters(num_letters);

    Solver solver(dic,letters);




    return 0;
}