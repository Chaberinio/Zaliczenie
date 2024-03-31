#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void otworzPlik(const string& nazwaPliku) {
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

void zapiszDoPliku(const string& nazwaPliku) {
    ofstream plik(nazwaPliku);
    if (plik.is_open()) {
        string tekst;
        cout << "Wprowadz tekst (wpisz 'koniec', aby zakonczyc):\n";
        while (true) {
            getline(cin, tekst);
            if (tekst == "koniec") break;
            plik << tekst << endl;
        }
        plik.close();
        cout << "Tekst zapisano do pliku." << endl;
    }
    else {
        cout << "Nie udalo sie otworzyc pliku." << endl;
    }
}

void szyfrujPlik(const std::string& nazwaPliku, int przesuniecie) {
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
    szyfrujPlik(nazwaPliku, 26 - przesuniecie);
    std::cout << "Zawartosc pliku zostala odszyfrowana pomyslnie." << std::endl;
}

int main() {
    int wybor;
    int przesuniecie;
    string nazwaPliku;

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
            cout << "Podaj nazwe pliku do zapisu: ";
            cin >> nazwaPliku;
            zapiszDoPliku(nazwaPliku);
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
            deszyfrujPlik(nazwaPliku,przesuniecie);
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
