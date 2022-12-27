#include <iostream>
#include <fstream>

#include <solver.h>
#include <dictionary.h>
#include <letters_set.h>
#include <letters_bag.h>

#include <chrono>
#include <vector>

using namespace  std;


void chrono_experiment(int vector_size, int repetitions) {
    // Inicializamos el experimento antes del bucle de conteo de tiempo para no afectar al análisis
    vector<int> collection;
    for (int i = 0; i < vector_size; ++i){
        collection.push_back(rand() % 1000);
    }

    // Medimos el tiempo antes de iniciar el expermiento
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // Realizamos el experimento tantas veces como indique repetitions, para tener cierta robustez
    // en el resultado (no todas las ejecuciones tardan lo mismo)
    for (int k = 0; k < repetitions; ++k){
        //bubbleSort(collection);
    }

    // Medimos el tiempo al finalizar el experimento
    chrono::high_resolution_clock::time_point finish_time = chrono::high_resolution_clock::now();

    // Calculamos la diferencia entre el inicio y el final
    chrono::duration<double> total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Dividimos el tiempo total entre el número de repeticiones para obtener el tiempo medio por ejecución
    cout << vector_size << "\t" << total_duration.count()/repetitions << endl;
}

void ChronoPalabras(const Dictionary & dic, const LettersSet & conjunto_letras, int repeticiones){

    // Iniciamos los solvers fuera del experimento

    int num_letras = 9;
    int npalabras = dic.size();
    Solver solver(dic,conjunto_letras);
    EfficientSolver solver_efi(dic, conjunto_letras);


    /*********************************************SOLVER BASICO**************************************************/
    // Medimos el tiempo
    chrono::high_resolution_clock::time_point start_time1 = chrono::high_resolution_clock::now();

    // Realizamos tantas repeticiones como queramos
    for (int k = 0; k < repeticiones; ++k){
        LettersBag bag1 (conjunto_letras);
        vector<char> available_letters1 = bag1.extractLetters(num_letras);
        solver.getSolutions(available_letters1,true);
    }

    // Medimos el tiempo final
    chrono::high_resolution_clock::time_point finish_time1 = chrono::high_resolution_clock::now();

    // Calculamos lo que tarda
    chrono::duration<double> total_duration1 = chrono::duration_cast<chrono::duration<double>>(finish_time1 - start_time1);

    cout << "Solver Básico    \t" << npalabras << "\t" << total_duration1.count()/repeticiones << endl;
    /*********************************************SOLVER EFICIENTE**************************************************/

    // Medimos el tiempo
    chrono::high_resolution_clock::time_point start_time2 = chrono::high_resolution_clock::now();

    // Realizamos tantas repeticiones como queramos
    for (int k = 0; k < repeticiones; ++k){
        LettersBag bag2 (conjunto_letras);
        vector<char> available_letters2 = bag2.extractLetters(num_letras);
        solver_efi.getSolutions(available_letters2,true);
    }

    // Medimos el tiempo final
    chrono::high_resolution_clock::time_point finish_time2 = chrono::high_resolution_clock::now();

    // Calculamos lo que tarda
    chrono::duration<double> total_duration2 = chrono::duration_cast<chrono::duration<double>>(finish_time2 - start_time2);


    /*********************************************RESULTADOS**************************************************/
    // Obtenemos el tiempo medio de ejecución
    cout << "Solver Eficiente \t" << npalabras << "\t" << total_duration2.count()/repeticiones << endl;
}


void ChronoLetras(const Dictionary &dict, const LettersSet &conjunto, int repeticiones, int n_letras){

    typedef chrono::high_resolution_clock::time_point instante_tiempo;
    typedef chrono::duration<double> diferencia_tiempo;

    // Inicio la imagen fuera del experimento
    Solver solverBasico(dict, conjunto);
    EfficientSolver solverEficiente(dict, conjunto);

    ////// Solver Básico ///////////////////////////////////////////////////////////////////////////////////////////

    // Medimos el tiempo
    instante_tiempo start_time = chrono::high_resolution_clock::now();

    // Realizamos tantas repeticiones como queramos
    for (int k = 0; k < repeticiones; ++k){
        // Creo un LettersBag
        LettersBag bolsa(conjunto);

        // Sacamos las letras de la bolsa
        vector<char> letras = bolsa.extractLetters(n_letras);

        // Damos formato en minúscula para recorrer el diccionario
        for(char &c : letras)
            c = tolower(c);

        // Resolvemos
        solverBasico.getSolutions(letras, true);
    }

    // Medimos el tiempo final
    instante_tiempo finish_time = chrono::high_resolution_clock::now();

    // Calculamos lo que tarda
    diferencia_tiempo total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Obtenemos el tiempo medio de ejecución
    cout << "Solver Básico    \t" << n_letras << "\t" << total_duration.count()/repeticiones << endl;

    ////// Solver Eficiente ////////////////////////////////////////////////////////////////////////////////////////

    // Medimos el tiempo
    start_time = chrono::high_resolution_clock::now();

    // Realizamos tantas repeticiones como queramos
    for (int k = 0; k < repeticiones; ++k){
        // Creo un LettersBag
        LettersBag bolsa(conjunto);

        // Sacamos las letras de la bolsa
        vector<char> letras = bolsa.extractLetters(n_letras);

        // Damos formato en minúscula para recorrer el diccionario
        for(char &c : letras)
            c = tolower(c);

        // Resolvemos
        solverEficiente.getSolutions(letras, true);
    }

    // Medimos el tiempo final
    finish_time = chrono::high_resolution_clock::now();

    // Calculamos lo que tarda
    total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Obtenemos el tiempo medio de ejecución
    cout << "Solver Eficiente \t" << n_letras << "\t" << total_duration.count()/repeticiones << endl;
}

vector<Dictionary> CargaDiccionarios();
LettersSet CargaLettersSet(string ruta);

int main(){

    vector<Dictionary> diccionarios = CargaDiccionarios();
    int ndics = diccionarios.size();
    LettersSet conjunto_letras = CargaLettersSet("./data/letras.txt");

    // Test en el que varia el tamaño del diccionario
    cout << "################ TEST DE PALABRAS ################" << endl;
    for (int k = 0; k < ndics; ++k) {

        ChronoPalabras(diccionarios[k], conjunto_letras,30);
    }

    // Test en el que varia el numero de letras.
    cout << "################ TEST DE LETRAS ################" << endl;
    for(int j = 5; j <= 90; j += 5){
        ChronoLetras(diccionarios[ndics-1], conjunto_letras, 50, j);
    }
    cout << endl;


}

vector<Dictionary> CargaDiccionarios(){

    vector<Dictionary> diccionarios;
    string directorio_diccionarios = "./data_eficiencia/";
    vector<string> rutas_diccionarios = {
        "diccionario_5000.txt",
        "diccionario_10000.txt",
        "diccionario_15000.txt",
        "diccionario_20000.txt",
        "diccionario_25000.txt",
        "diccionario_30000.txt",
        "diccionario_35000.txt",
        "diccionario_40000.txt",
        "diccionario_45000.txt",
        "diccionario_50000.txt",
        "diccionario_55000.txt",
        "diccionario_60000.txt",
        "diccionario_65000.txt",
        "diccionario_70000.txt",
    };

    for(string &ruta_dic : rutas_diccionarios){

        ifstream ifs;
        ifs.open((directorio_diccionarios + ruta_dic).c_str());

        if(ifs.bad()){
            cerr << "Error al abrir " << directorio_diccionarios + ruta_dic << endl;
            exit(1);
        }

        Dictionary diccionario;
        ifs >> diccionario;
        diccionarios.push_back(diccionario);

        ifs.close();
    }

    return diccionarios;
}

LettersSet CargaLettersSet(string ruta){

    ifstream ifs;
    ifs.open(ruta.c_str());
    if(ifs.bad()){
        cerr << "Error al abrir " << ruta << endl;
        exit(1);
    }

    LettersSet conjunto;
    ifs >> conjunto;

    ifs.close();

    return conjunto;
}