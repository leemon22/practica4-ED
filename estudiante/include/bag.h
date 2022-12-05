#ifndef __BAG_H__
#define __BAG_H__
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
/**
 *  \brief TDA abstracto Bolsa
 *
 *  @details Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 *
 *  Además, se podrán realizar operaciones básicas como añadir elementos, dejarla vací o consultar el tamaño.
 *
 */

template <class T>
class Bag {
private:

    vector<T> v;

public:

    /**
     * @brief Constructor por defecto.
     * @post Genera una instancia de la clase Bag con O elementos.
     */
    Bag() {}

    /**
     * @brief Constructor de copia.
     * @param other referencia a la Bolsa que queremos copiar.
     */
    Bag(const Bag<T> & other) : v(other.v) {}

    /**
     * @brief Añade el elemento @p element en la Bolsa.
     * @param element Elemento a añadir en la Bolsa.
     * @pos Con el fin de obtener eficiencia lineal, se añadirá al final del vector.
     */
    void add(const T & element) {

        v.push_back(element);
    }

    /**
     * @brief Extrae un elemento aleatorio de la Bolsa.
     * @pos Con el fin de obtener eficiencia lineal, se intercambiará el elemento a extraer
     * @pos por el último y se eliminará en la última posición.
     * @return El elemento elegido aleatoriamente.
     */
    T get() {
        //srand(time(NULL));
        int elem = rand() % v.size();
        T ret = v[elem];
        if (elem != v.size()-1) {
            v[elem] = *(v.end()-1);
        }
        v.pop_back();
        return ret;
    }

    /**
     * @brief Deja vacía la Bolsa; es decir, sin elementos.
     * @pos Deja el tamaño del mismo nulo.
     */
    void clear() {v.clear();}

    /**
     * @brief Método de consulta del número de elementos que hay en la Bolsa.
     * @return El tamaño de la Bolsa (del vector de T).
     */
    unsigned int size() const {return v.size();}

    /**
    * @brief Comnprueba si la bolsa está vacía.
    * @return true si está vacía, false en otro caso.
    */
    bool empty() {return v.empty();}

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param other Bolsa a asignar.
     * @return La bolsa implícita.
     */
    const Bag<T>& operator=(const Bag<T> & other) {
        if (this != &other) {
            v = other.v;
        }
        return *this;
    }


};
#endif
