#include <string.h>

#include <iostream>
#include <fstream>

#include <vector>
#include <string>

#include <dictionary.h>
#include <letters_set.h>
#include <solver.h>
#include <letters_bag.h>

using namespace std;

void mensajeError(char * error);

int main(int argc, char *argv[]){

    // Entrada de argumentos
    if(argc != 5){
        mensajeError("Número de argumentos inválido");
        exit(1);
    }

    char *ruta_diccionario = argv[1];
    char *ruta_letras = argv[2];

    if(argv[3][0] != 'L' && argv[3][0] != 'P'){
        mensajeError("Modo de juego no válido");
        exit(1);
    }

    // Procesamiento de los argumentos
    bool modo_juego = argv[3][0] == 'P';
    int num_letras = stoi(argv[4]);

    ifstream ifs;

    // Lectura del diccionario
    Dictionary diccionario;

    ifs.open(ruta_diccionario);
    if(ifs.bad()){
        mensajeError("Error al abrir el diccionario");
        exit(1);
    }
    else{
        ifs >> diccionario;
    }
    ifs.close();

    // Lectura del archivo de letras
    LettersSet lettersSet;

    ifs.open(ruta_letras);
    if(ifs.bad()){
        mensajeError("Error al abrir el archivo de letras");
        exit(1);
    }
    else{
        ifs >> lettersSet;
    }
    ifs.close();

    // Creación del Solver
    EfficientSolver solver(diccionario, lettersSet);

    // Creación de la Lettersbag que extraerá las letras
    LettersBag bolsa(lettersSet);

    // Sacamos las letras de la bolsa
    vector<char> letras = bolsa.extractLetters(num_letras);

    // Damos formato en minúscula para recorrer el diccionario
    for(char &c : letras)
        c = tolower(c);

    // Resolvemos
    pair<vector<string>, int> solucion = solver.getSolutions(letras, modo_juego);

    // Mostramos la salida por consola
    cout << "LETRAS DISPONIBLES:" << endl;
    for(char c : letras)
        cout << c << " ";
    cout << endl;
    cout << "SOLUCIONES:" << endl;
    for(string &palabra : solucion.first)
        cout << palabra << endl;
    cout << "PUNTUACION:" << endl;
    cout << solucion.second << endl;

    return 0;
}

void mensajeError(char * error){
    cerr << error << endl;
    cerr << "./build/partida_letras_eficiente <ruta/del/diccionario> <ruta/del/archivo/de/letras> <modo de juego> <letras por partida>" << endl;
    cerr << "Modo de juego:" << endl;
    cerr << "\tL: longitud" << endl;
    cerr << "\tP: puntuación" << endl;
}