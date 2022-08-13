#include <iostream>
#include "Stablo.h"

using namespace std;

void ispis_elemenata(int &element)
{
    cout << element << " ";
}

int main()
{
    //vector<int> elementi{2, 1, 5, 7, 8, 7, 6};
//    vector<int> elementi{20, 10, 40, 5, 15, 30, 50, 2, 7, 12, 18, 25, 35, 45, 55}; // balansirano dubina 3 // PADA
//    vector<int> elementi{20, 10, 40, 15, 30, 50, 25}; // disbalansirano
//    vector<int> elementi{20, 10, 5, 15, 2, 7, 12, 18}; // bez desne grane
//    vector<int> elementi{20, 10, 5, 2, 7}; // bez desne + bez desne grane
//    vector<int> elementi{50, 25, 13, 6, 19, 3, 1}; // 2x balansira
//    vector<int> elementi{50, 21, 76, 4, 32, 64, 100, 2, 15, 52, 70, 83, 3, 14, 80, 87}; // 2x balansira
//    vector<int> elementi{57, 48, 65, 24, 50, 61, 75, 7, 30, 53, 59}; // balansira 1x

    /*Binarno_stablo_pretrage<int> s;
    s.dodaj_element(57);
    s.dodaj_element(48);
    s.dodaj_element(65);
    s.dodaj_element(24);
    s.dodaj_element(50);
    s.dodaj_element(61);
    s.dodaj_element(75);
    s.dodaj_element(7);
    s.dodaj_element(30);
    s.dodaj_element(53);
    s.dodaj_element(59);
    s.brisanje_elementa(61);
    s.operacija_nad_elementima(ispis_elemenata);
    cout << endl;*/

    Binarno_stablo_pretrage<int> t;
    t.dodaj_element(50);
    t.dodaj_element(21);
    t.dodaj_element(76);
    t.dodaj_element(4);
    t.dodaj_element(32);
    t.dodaj_element(64);
    t.dodaj_element(100);
    t.dodaj_element(2);
    t.dodaj_element(15);
    t.dodaj_element(52);
    t.dodaj_element(70);
    t.dodaj_element(83);
    t.dodaj_element(3);
    t.dodaj_element(14);
    t.dodaj_element(80);
    t.dodaj_element(87);

    t.brisanje_elementa(32);
    t.brisanje_elementa(80);
    t.brisanje_elementa(50);

    cout << "Elementi stabla su: ";
    t.operacija_nad_elementima(ispis_elemenata);

    cout << endl << "Visina stabla je " << t.visina_stabla() << endl;
    cout << "Broj listova stabla je "  << t.broj_listova() << endl;
    cout << "Suma elemenata stabla je "  << t.suma_elemenata() << endl;
    cout << "Proizvod elemenata stabla je "  << t.proizvod_elemenata() << endl;

    return 0;
}
