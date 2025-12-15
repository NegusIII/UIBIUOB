#include "letters_bag.h"
#include <random>
#include <vector>

using namespace std;

LettersBag::LettersBag() {}

LettersBag::LettersBag(const LettersSet &set_letters) {
    map<char, LettersSet::LetterInfo> set = set_letters.getLetters();

    map<char, LettersSet::LetterInfo>::iterator it;
    for (it = set.begin(); it != set.end(); ++it) {
        char actual=it->first;
        int cantidad=it->second.repeticiones;
        for (int i=0; i<cantidad; i++) {
            insertar(actual);
        }
    }
}

void LettersBag::insertar(char c) {
    letras.push_back(c);
}

char LettersBag::extraer() {

    list<char>::iterator it = letras.begin();

    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(0, letras.size() - 1);
    int pasos = dis(gen);

    std::advance(it, pasos);
    char c = *it;
    letras.erase(it);

    return c;
}

int LettersBag::size() const {
    return letras.size();
}

void LettersBag::clear() {

    letras.clear();
}

vector<char> LettersBag::extraer_varias(int n) {

    vector<char> v;
    for (int i = 0; i < n; i++) {
        v.push_back(extraer());
    }
    return v;
}

ostream & operator<<(ostream & os, const LettersBag & bag) {

    list<char>::const_iterator it;
    for (it = bag.letras.begin(); it != bag.letras.end(); ++it) {
        os << *it << endl;
    }
    return os;
}
