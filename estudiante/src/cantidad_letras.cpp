//
// Created by usuario on 1/12/22.
//

#include "dictionary.h"
#include "letters_set.h"
#include <fstream>

int main(int argc, char *argv[])
{
    if(argc != 3){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero con las letras" << endl;
        return 1;
    }

    ifstream f_diccionario(argv[1]);
    ifstream f_letras(argv[2]);

    if(!f_diccionario){
        cout << "No puedo abrir el fichero " << argv[1] << endl;
        return 0;
    }

    if(!f_letras){
        cout << "No puedo abrir el fichero " << argv[2] << endl;
        return 0;
    }

    Dictionary diccionario;
    f_diccionario >> diccionario;

    LettersSet letras;
    f_letras >> letras;

    cout << "Letra\tUsos\tOcurrencias" << endl;
    int usos = 0, ocurrencias = 0;

    for (LettersSet::const_iterator it = letras.begin(); it != letras.end(); ++it) {

        usos = diccionario.getTotalUsages((*it).first);
        ocurrencias = diccionario.getOccurrences((*it).first);

        cout << (*it).first << "\t" << usos << "\t" << ocurrencias << endl;
    }

    return 0;
}
