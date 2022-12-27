//
// Created by fluque1995 on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){
    int res = 0;
    if (toupper((*curr_node).character) == c) {
        ++res;
    }

    if(!curr_node.left_child().is_null()) {
        res += getOccurrences(curr_node.left_child(),c);
    }

    if (!curr_node.right_sibling().is_null()) {
        res += getOccurrences(curr_node.right_sibling(),c);
    }

    return res;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){
    pair<int,int> res(0,0);
    pair<int,int> izq(0,0);
    pair<int,int> dch(0,0);
    if(!curr_node.left_child().is_null()) {
        izq = getTotalUsages(curr_node.left_child(),c);
    }
    if(!curr_node.right_sibling().is_null()) {
        dch = getTotalUsages(curr_node.right_sibling(),c);
    }

    res.first = izq.first + dch.first;
    res.second = izq.second + dch.second;

    if (toupper((*curr_node).character) == c) {
        res.first += izq.second;
    }

    if ((*curr_node).valid_word) {
        ++res.second;
        if (toupper((*curr_node).character) == c) {
            ++res.first;
        }
    }
    return res;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

/*std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}*/

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){

    return getOccurrences(words.get_root(),c);
}

int Dictionary::getTotalUsages(const char c){
    return getTotalUsages(words.get_root(),c).first;
}
///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() : iter(), curr_word("") {
    ++(*this);
}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter)  {
    this->iter = iter;
    curr_word ="";
    ++(*this);

}

std::string Dictionary::iterator::operator*() {
    return curr_word;
}

/*
Dictionary::iterator &Dictionary::iterator::operator++() {

    int current_level = iter.get_level();
    ++iter;

    bool sigo = true;
    if (iter.get_level() == 0) {
        sigo = false;
        curr_word = "";

    }
    while (sigo) {

        if (iter.get_level() > current_level) {
            curr_word.push_back((*iter).character);
        } else if (iter.get_level() == current_level) {
            curr_word.pop_back();
            curr_word.push_back((*iter).character);
        } else {
            curr_word.pop_back();
            while (current_level != iter.get_level() && current_level != 0) {
                curr_word.pop_back();
                current_level--;
            }
            curr_word.push_back((*iter).character);
        }

        if ((*iter).valid_word) {
            sigo = false;

        }
        else {
            current_level = iter.get_level();
            ++iter;
        }
    }

    return *this;
}*/

Dictionary::iterator &Dictionary::iterator::operator++() {

    int current_level = iter.get_level();
    ++iter;



    bool sigo = true;
    if (iter.get_level() == 0) {
        sigo = false;
        curr_word = "";

    }
    while (sigo) {

        if (iter.get_level() == current_level) {
            curr_word.pop_back();
        }
        else if (iter.get_level() < current_level) {
            curr_word.pop_back();
            while (current_level != iter.get_level() && current_level != 0) {
                curr_word.pop_back();
                current_level--;
            }

        }
        curr_word.push_back((*iter).character);

        if ((*iter).valid_word) {
            sigo = false;

        }
        else {
            current_level = iter.get_level();
            ++iter;
        }
    }

    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return iter == other.iter && curr_word == other.curr_word;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return iter != other.iter || curr_word != other.curr_word;
}

Dictionary::iterator Dictionary::begin() const {
    return words.cbegin_preorder();
}

Dictionary::iterator Dictionary::end() const {
    return words.cend_preorder();
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    return possible_words_iterator(words.get_root(), available_characters);
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    return possible_words_iterator(words.get_root(),{});
}

Dictionary::possible_words_iterator::possible_words_iterator():
    available_letters(), current_node(), current_word(""){}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters):
        current_node(current_node), available_letters(available_letters.begin(), available_letters.end()){
    ++(*this);
}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other) = default;

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) = default;

bool Dictionary::possible_words_iterator::isEqual(const Dictionary::possible_words_iterator &other) const {
    return current_word == other.current_word && current_node == other.current_node;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    return isEqual(other);
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return !isEqual(other);
}

void Dictionary::possible_words_iterator::avanzarHijo(const Dictionary::node &hijo) {

    char letraHijo = letraNodo(hijo);

    multiset<char>::iterator it = available_letters.find(letraHijo);
    available_letters.erase(it);

    current_node = hijo;

    current_word += letraHijo;
}

void Dictionary::possible_words_iterator::avanzarHermano(const Dictionary::node &hermano) {

    avanzarPadre();
    avanzarHijo(hermano);
}

void Dictionary::possible_words_iterator::avanzarPadre() {

    char miLetra = letraNodo(current_node);

    available_letters.insert(miLetra);

    current_node = current_node.parent();

    current_word.pop_back();
}

Dictionary::node Dictionary::possible_words_iterator::obtenerHermanoValido(const node &primer_hermano) const {

    // Esta condición no es necesaria, pero acelera la ejecución del programa
    if(available_letters.empty())
        return node();

    for(node hermano = primer_hermano; !hermano.is_null(); hermano = hermano.right_sibling()){
        char letraHermano = letraNodo(hermano);

        if(available_letters.count(letraHermano) > 0)
            return hermano;
    }

    return node();
}

void Dictionary::possible_words_iterator::retrocederEnArbol() {

    while (hayPadre()){
        avanzarPadre();
        node tio = obtenerHermanoValido(current_node.right_sibling());

        if(!tio.is_null()){
            avanzarHermano(tio);
            return;
        }
    }
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {

    bool termina = current_node.is_null();

    while(!termina){

        // Accedo al primer hijo
        node hijo = obtenerHermanoValido(current_node.left_child());

        if(!hijo.is_null()){

            // Si existe el hijo, avanzo el iterador al hijo
            avanzarHijo(hijo);
            // Veo si es el final de una palabra
            if(soyNodoFinal())
                termina = true;
        }
        else{
            // Si no existe el hijo, accedo al hermano
            node hermano = obtenerHermanoValido(current_node.right_sibling());

            if(!hermano.is_null()){

                // Si existe el hermano, avanzo el iterador al hermano
                avanzarHermano(hermano);
                // Veo si es el final de una palabra
                if(soyNodoFinal())
                    termina = true;
            }
            else{
                // Si no se ha encontrado nodos para continuar en los hijos o en los hermanos, retrocedemos en el arbol
                retrocederEnArbol();

                // Paramos el bucle si retrocediendo en el arbol estamos en un nodo final o en un nodo nulo
                if(!hayPadre() || soyNodoFinal())
                    termina = true;
            }
        }
    }

    return *this;
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return current_word;
}
