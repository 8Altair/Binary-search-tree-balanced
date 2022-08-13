//
// Created by Korisnik on 27.01.2021.
//

#ifndef STABLO_STABLO_H
#define STABLO_STABLO_H


template <typename tip>
class Binarno_stablo_pretrage final
{
    unsigned short int velicina;
    struct Cvor final
    {
        tip element;
        int broj_lijevih_potomaka, broj_desnih_potomaka;

        Cvor *roditelj, *lijevo_dijete, *desno_dijete;
        explicit Cvor(tip element, Cvor *roditelj = nullptr, Cvor *lijevo_dijete = nullptr,
                      Cvor *desno_dijete = nullptr, int broj_lijevih_potomaka = 0, int broj_desnih_potomaka = 0):
                element(element), roditelj(roditelj), lijevo_dijete(lijevo_dijete), desno_dijete(desno_dijete),
                broj_lijevih_potomaka(broj_lijevih_potomaka), broj_desnih_potomaka(broj_desnih_potomaka) {}
    };

    Cvor *korijen;

    bool pronadji_element(tip element, Cvor *cvor);
    bool da_li_je_izbalansirano(Cvor *korijen, Cvor *&neizbalansirano_stablo);
    Cvor *pronalazak_cvora(tip element);
    void dodavanje_elementa(tip element);

    void ubacivanje_elemenata_u_niz(tip *&niz, Cvor *korijen, unsigned short int &indeks);
    Cvor *balansiranje_stabla(const tip *niz, int pocetak, int kraj);
    Cvor *rekonstrukcija_stabla(Cvor *neizbalansirano_stablo);

    void operacija_nad_cvorovima(Cvor *korijen, void (funkcija)(tip &));
    unsigned short int broj_listova(Cvor *korijen) const;
    int visina_stabla(Cvor *korijen) const;
    tip suma_elemenata(Cvor *korijen) const;
    tip proizvod_elemenata(Cvor *korijen) const;

    void izbrisi_cvor(Cvor *korijen);
public:

    Binarno_stablo_pretrage() : korijen(nullptr), velicina(0) {}
    void dodaj_element(tip element);
    void brisanje_elementa(tip element);
    bool pronadji_element(tip element) {return pronadji_element(element, korijen);}

    void operacija_nad_elementima(void (funkcija)(tip &)) {operacija_nad_cvorovima(korijen, funkcija);}
    unsigned short int broj_listova() const {return broj_listova(korijen);}
    int visina_stabla() const {return visina_stabla(korijen);}
    int visina_stabla(tip element) const {return visina_stabla(pronalazak_cvora(element));}
    tip suma_elemenata() const {return suma_elemenata(korijen);}
    tip proizvod_elemenata() const {return proizvod_elemenata(korijen);}

    ~Binarno_stablo_pretrage() {izbrisi_cvor(korijen);}
};


#include "Stablo.cpp"

#endif //STABLO_STABLO_H
