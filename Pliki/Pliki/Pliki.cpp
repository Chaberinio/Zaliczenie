#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool czyPlikIstnieje(const string& nazwaPliku) {
    ifstream plik(nazwaPliku);
    return plik.good();
}

void otworzPlik(const string& nazwaPliku) {

    if (!czyPlikIstnieje(nazwaPliku)) {
        cout << "Plik nie istnieje." << endl;
        return;
    }
    ifstream plik(nazwaPliku);
    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            cout << linia << endl;
        }
        plik.close();
    }
    else {
        cout << "Nie udalo sie otworzyc pliku." << endl;
    }
}

void zapiszDoPliku(const std::string& nazwaPliku, const std::string& tekst) {
    if (!czyPlikIstnieje(nazwaPliku)) {
        cout << "Plik nie istnieje." << endl;
        return;
    }
    std::ofstream plik(nazwaPliku);
    if (plik.is_open()) {
        plik << tekst;
        std::cout << "Tekst zostal zapisany do pliku: " << nazwaPliku << std::endl;
        plik.close();
    }
    else {
        std::cerr << "Blad otwarcia pliku do zapisu." << std::endl;
    }
}

void szyfrujPlik(const std::string& nazwaPliku, int przesuniecie) {

    if (!czyPlikIstnieje(nazwaPliku)) {
        cout << "Plik nie istnieje." << endl;
        return;
    }
    std::ifstream plikWe(nazwaPliku);
    if (!plikWe) {
        std::cerr << "Nie udalo sie otworzyc pliku do odczytu." << std::endl;
        return;
    }

    std::string linia;
    std::string zaszyfrowanyTekst;

    while (std::getline(plikWe, linia)) {
        for (char& znak : linia) {
            if (isalpha(znak)) {
                char start = isupper(znak) ? 'A' : 'a';
                znak = start + (znak - start + przesuniecie) % 26;
            }
        }
        zaszyfrowanyTekst += linia + '\n';
    }

    plikWe.close();

    std::ofstream plikWy(nazwaPliku);
    if (!plikWy) {
        std::cerr << "Nie udalo sie otworzyc pliku do zapisu." << std::endl;
        return;
    }

    plikWy << zaszyfrowanyTekst;
    std::cout << "Zawartosc pliku zostala zaszyfrowana pomyslnie." << std::endl;
}

void deszyfrujPlik(const std::string& nazwaPliku, int przesuniecie) {
    if (!czyPlikIstnieje(nazwaPliku)) {
        cout << "Plik nie istnieje." << endl;
        return;
    }
    szyfrujPlik(nazwaPliku, 26 - przesuniecie);
    std::cout << "Zawartosc pliku zostala odszyfrowana pomyslnie." << std::endl;
}

int main() {
    int wybor;
    int przesuniecie;
    string nazwaPliku,tekst;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Otworz plik" << endl;
        cout << "2. Zapisz do pliku" << endl;
        cout << "3. Szyfruj plik" << endl;
        cout << "4. Deszyfruj plik" << endl;
        cout << "5. Zakoncz program" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            cout << "Podaj nazwe pliku do otwarcia: ";
            cin >> nazwaPliku;
            otworzPlik(nazwaPliku);
            break;
        case 2:
            std::cout << "Podaj nazwe pliku do zapisu: ";
            std::cin >> nazwaPliku;
            std::cin.ignore(); 
            std::cout << "Wprowadz tekst do zapisania: ";
            std::getline(std::cin, tekst);
            zapiszDoPliku(nazwaPliku, tekst);
            break;
        case 3:
            cout << "Podaj nazwe pliku do zaszyfrowania: ";
            cin >> nazwaPliku;
            cout << "Podaj przesuniecie: ";
            cin >> przesuniecie;
            szyfrujPlik(nazwaPliku, przesuniecie);
            break;
        case 4:
            cout << "Podaj nazwe pliku do odszyfrowania: ";
            cin >> nazwaPliku;
            cout << "Podaj przesuniecie: ";
            cin >> przesuniecie;
            deszyfrujPlik(nazwaPliku, przesuniecie);
            break;
        case 5:
            cout << "Koniec programu." << endl;
            return 0;
        default:
            cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
        }
    }

    return 0;
}