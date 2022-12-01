#include "letters_set.h"
#include <map>
#include <string>

LettersSet::LettersSet() = default;

LettersSet::LettersSet(const LettersSet &other) = default;

bool LettersSet::insert(const pair<char,LetterInfo> &val){
    pair<map<char,LetterInfo>::iterator,bool> p = letters.insert(val);
    return p.second;
}

bool LettersSet::erase(const char &key){
    return letters.erase(key) > 0;
}

void LettersSet::clear(){
    letters.clear();
}

bool LettersSet::empty() const{
    return letters.empty();
}

unsigned int LettersSet::size() const{
    return letters.size();
}

int LettersSet::getScore(std::string word) const {

    int score = 0;
    for(char &c : word) {
        score += letters.at(c).score;
    }

    return score;
}

LettersSet &LettersSet::operator=(const LettersSet &cl) {
    if(&cl != this)
        letters = cl.letters;
    return *this;
}

LetterInfo &LettersSet::operator[](const char &val) {
    return letters[val];
}

typedef LettersSet::const_iterator iter;

iter &iter::operator++() {
    ++it;
    return *this;
}

iter &iter::operator--() {
    --it;
    return *this;
}

const pair<const char, LetterInfo> &iter::operator*() const{
    return *it;
}



bool iter::operator==(const iter &other) {
    return it == other.it;
}

bool iter::operator!=(const iter &other) {
    return it != other.it;
}

iter LettersSet::begin() const {
    iter it;
    it.it = letters.begin();
    return it;
}

iter LettersSet::end() const {
    iter it;
    it.it = letters.end();
    return it;
}

ostream &operator<<(ostream &os, const LettersSet &cl){

    map<char,LetterInfo>::const_iterator it;
    for( it = cl.letters.begin(); it != cl.letters.end(); ++it)
        os << it->first << '\t' << it->second.repetitions << '\t' << it->second.score << endl;

    return os;
}

istream &operator>>(istream &is, LettersSet &cl){
    char key;
    LetterInfo value;
    string cabecera;
    getline(is,cabecera);

    while (is) {
        is >> key >> value.repetitions >> value.score;
        cl.insert({key, value});
    }

    return is;
}