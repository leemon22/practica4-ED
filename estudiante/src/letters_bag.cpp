#include <letters_bag.h>
#include <bag.h>

LettersBag::LettersBag():letters() {}

LettersBag::LettersBag(const LettersBag &other):letters(other.letters) {}

LettersBag::LettersBag(const LettersSet & letters_set) {
    for (LettersSet::const_iterator it = letters_set.begin(); it != letters_set.end(); ++it) {
        for(int i = 0; i < it.value().repetitions; ++i)
            letters.add((*it).first);
    }
}
void LettersBag::insertLetter(const char &l) {
    letters.add(l);
}

char LettersBag::extractLetter() {
    return letters.get();
}

vector<char> LettersBag::extractLetters(int num) {

    vector<char> resultado;
    for(int i = 0; i < num; ++i)
        resultado.push_back(letters.get());

    return resultado;
}

void LettersBag::clear() {
    letters.clear();
}

unsigned int LettersBag::size() const {
    return letters.size();
}

LettersBag &LettersBag::operator=(const LettersBag &other) {

    if(this != &other)
        letters = other.letters;

    return *this;
}