//
// Created by Korisnik on 27.01.2021.
//
#ifndef STABLO_CPP
#define STABLO_CPP

#include "Stablo.h"

template <typename tip>
bool Binarno_stablo_pretrage<tip>::pronadji_element(tip element, Cvor *cvor)
{
    if (cvor == nullptr) return false;
    if(cvor->element == element) return true;

    if (cvor->element > element) return pronadji_element(element, cvor->lijevo_dijete);
    else return pronadji_element(element, cvor->desno_dijete);
}

template <typename tip>
bool Binarno_stablo_pretrage<tip>::da_li_je_izbalansirano(Cvor *korijen, Cvor *&neizbalansirano_stablo)
{
    if (visina_stabla(korijen) < 3) return false;

    if (korijen->broj_lijevih_potomaka >= 2 * korijen->broj_desnih_potomaka ||
        korijen->broj_desnih_potomaka >= 2 * korijen->broj_lijevih_potomaka)
    {
        neizbalansirano_stablo = korijen;
        return true;
    }
    else if (korijen->lijevo_dijete != nullptr)
    {
        if (visina_stabla(korijen->lijevo_dijete) >= 3)
        {
            return da_li_je_izbalansirano(korijen->lijevo_dijete, neizbalansirano_stablo);
        }
    }
    else
    {
        if (visina_stabla(korijen->desno_dijete) >= 3)
        {
            return da_li_je_izbalansirano(korijen->desno_dijete, neizbalansirano_stablo);
        }
    }
}

template <typename tip>
typename Binarno_stablo_pretrage<tip>::Cvor *Binarno_stablo_pretrage<tip>::pronalazak_cvora(tip element)
{
    Cvor *trenutni_cvor(korijen);
    while (trenutni_cvor != nullptr)
    {
        if (trenutni_cvor->element == element) return trenutni_cvor;
        if (trenutni_cvor->element > element) trenutni_cvor = trenutni_cvor->lijevo_dijete;
        else trenutni_cvor = trenutni_cvor->desno_dijete;
    }
    return nullptr;
}

template <typename tip>
void Binarno_stablo_pretrage<tip>::ubacivanje_elemenata_u_niz(tip *&niz, Cvor *korijen, unsigned short int &indeks)
{
    if (korijen->lijevo_dijete != nullptr) ubacivanje_elemenata_u_niz(niz, korijen->lijevo_dijete, indeks);
    niz[indeks] = korijen->element;
    indeks++;
    if (korijen->desno_dijete != nullptr) ubacivanje_elemenata_u_niz(niz, korijen->desno_dijete, indeks);
}

template <typename tip>
typename Binarno_stablo_pretrage<tip>::Cvor *Binarno_stablo_pretrage<tip>::balansiranje_stabla(const tip *niz,
                                                                                               int pocetak, int kraj)
{
    if (pocetak > kraj) return nullptr;
    int sredina_niza((pocetak + kraj) / 2);
    Cvor *cvor = new Cvor(niz[sredina_niza]);

    cvor->lijevo_dijete = balansiranje_stabla(niz, pocetak,sredina_niza - 1);
    if (cvor->lijevo_dijete != nullptr) cvor->lijevo_dijete->roditelj = cvor;

    cvor->desno_dijete = balansiranje_stabla(niz, sredina_niza + 1, kraj);
    if (cvor->desno_dijete != nullptr) cvor->desno_dijete->roditelj = cvor;

    if (cvor->lijevo_dijete != nullptr)
    {
        cvor->broj_lijevih_potomaka = cvor->lijevo_dijete->broj_lijevih_potomaka + cvor->lijevo_dijete->broj_desnih_potomaka + 1;
    }
    if (cvor->desno_dijete != nullptr)
    {
        cvor->broj_desnih_potomaka = cvor->desno_dijete->broj_lijevih_potomaka + cvor->desno_dijete->broj_desnih_potomaka + 1;
    }

    velicina++;
    return cvor;
}

template <typename tip>
typename Binarno_stablo_pretrage<tip>::Cvor *Binarno_stablo_pretrage<tip>::rekonstrukcija_stabla(Cvor *neizbalansirano_stablo)
{
    int duzina_niza(neizbalansirano_stablo->broj_lijevih_potomaka + neizbalansirano_stablo->broj_desnih_potomaka + 1);
    tip *niz_elemenata_stabla = new tip[duzina_niza];
    unsigned short int indeks(0);
    ubacivanje_elemenata_u_niz(niz_elemenata_stabla, neizbalansirano_stablo, indeks);

    izbrisi_cvor(neizbalansirano_stablo);

    return balansiranje_stabla(niz_elemenata_stabla,0, duzina_niza - 1);
}

template <typename tip>
void Binarno_stablo_pretrage<tip>::operacija_nad_cvorovima(Cvor *korijen, void (*funkcija)(tip &))
{
    if (korijen->lijevo_dijete != nullptr) operacija_nad_cvorovima(korijen->lijevo_dijete, funkcija);
    funkcija(korijen->element);
    if (korijen->desno_dijete != nullptr) operacija_nad_cvorovima(korijen->desno_dijete, funkcija);
}

template <typename tip>
unsigned short int Binarno_stablo_pretrage<tip>::broj_listova(Cvor *korijen) const
{
    if (korijen == nullptr) return 0;
    if (korijen->lijevo_dijete == nullptr && korijen->desno_dijete == nullptr) return 1;

    if (korijen->lijevo_dijete != nullptr && korijen->desno_dijete != nullptr)
    {
        return broj_listova(korijen->lijevo_dijete) + broj_listova(korijen->desno_dijete);
    }
    else if (korijen->lijevo_dijete != nullptr && korijen->desno_dijete == nullptr)
    {
        return broj_listova(korijen->lijevo_dijete);
    }
    else
    {
        return broj_listova(korijen->desno_dijete);
    }
}

template <typename tip>
int Binarno_stablo_pretrage<tip>::visina_stabla(Cvor *korijen) const
{
    if (korijen == nullptr) return -1;
    else if (korijen->lijevo_dijete == nullptr && korijen->desno_dijete == nullptr) return 0;
    else
    {
        int lijeva_visina(visina_stabla(korijen->lijevo_dijete));
        int desna_visina(visina_stabla(korijen->desno_dijete));
        if (lijeva_visina > desna_visina) return lijeva_visina + 1;
        else return desna_visina + 1;
    }
}

template <typename tip>
tip Binarno_stablo_pretrage<tip>::suma_elemenata(Cvor *korijen) const
{
    if (korijen == nullptr) return 0;
    if (korijen->lijevo_dijete == nullptr && korijen->desno_dijete == nullptr) return korijen->element;
    return suma_elemenata(korijen->lijevo_dijete) + suma_elemenata(korijen->desno_dijete);
}

template <typename tip>
tip Binarno_stablo_pretrage<tip>::proizvod_elemenata(Cvor *korijen) const
{
    if (korijen == nullptr) return 0;
    if (korijen->lijevo_dijete == nullptr && korijen->desno_dijete == nullptr) return korijen->element;
    return suma_elemenata(korijen->lijevo_dijete) * suma_elemenata(korijen->desno_dijete);
}

template <typename tip>
void Binarno_stablo_pretrage<tip>::izbrisi_cvor(Cvor *korijen)
{
    if (korijen != nullptr)
    {
        if (korijen->lijevo_dijete != nullptr) izbrisi_cvor(korijen->lijevo_dijete);
        if (korijen->desno_dijete != nullptr) izbrisi_cvor(korijen->desno_dijete);

        if (korijen->roditelj == nullptr)
        {
            korijen->lijevo_dijete = nullptr;
            korijen->desno_dijete = nullptr;
        }
        else if (korijen->roditelj->lijevo_dijete == korijen)
        {
            korijen->roditelj->lijevo_dijete = nullptr;
            korijen->roditelj->broj_lijevih_potomaka--;
        }
        else
        {
            korijen->roditelj->desno_dijete = nullptr;
            korijen->roditelj->broj_desnih_potomaka--;
        }

        velicina--;
        delete korijen;
        korijen = nullptr;
    }
}

template <typename tip>
void Binarno_stablo_pretrage<tip>::dodavanje_elementa(tip element)
{
    if (korijen == nullptr)
    {
        korijen = new Cvor(element);
        velicina = 1;
        return;
    }

    Cvor *trenutni_cvor(korijen);
    while(trenutni_cvor != nullptr)
    {
        if (trenutni_cvor->element == element)
        {
            Cvor *njegov_roditelj(trenutni_cvor->roditelj);
            while (njegov_roditelj != nullptr)
            {
                if (njegov_roditelj->lijevo_dijete->element == trenutni_cvor->element)
                {
                    njegov_roditelj->broj_lijevih_potomaka--;
                }
                else
                {
                    njegov_roditelj->broj_desnih_potomaka--;
                }
                trenutni_cvor = njegov_roditelj;
                njegov_roditelj = njegov_roditelj->roditelj;
            }
            break;
        }
        if (trenutni_cvor->element > element)
        {
            trenutni_cvor->broj_lijevih_potomaka++;
            if (trenutni_cvor->lijevo_dijete != nullptr) trenutni_cvor = trenutni_cvor->lijevo_dijete;
            else
            {
                trenutni_cvor->lijevo_dijete = new Cvor(element, trenutni_cvor);
                velicina++;
                break;
            }
        }

        else
        {
            trenutni_cvor->broj_desnih_potomaka++;
            if (trenutni_cvor->desno_dijete != nullptr) trenutni_cvor = trenutni_cvor->desno_dijete;
            else
            {
                trenutni_cvor->desno_dijete = new Cvor(element, trenutni_cvor);
                velicina++;
                break;
            }
        }
    }
}

template <typename tip>
void Binarno_stablo_pretrage<tip>::dodaj_element(tip element)
{
    dodavanje_elementa(element);

    Cvor *neizbalansirano_stablo;
    if (da_li_je_izbalansirano(korijen, neizbalansirano_stablo))
    {
        Cvor *balansirano_stablo;
        if (neizbalansirano_stablo == korijen)
        {
            korijen = rekonstrukcija_stabla(neizbalansirano_stablo);
        }
        else
        {
            Cvor *novi_roditelj = neizbalansirano_stablo->roditelj;
            short int spoji(-1);
            if (neizbalansirano_stablo->roditelj->desno_dijete == neizbalansirano_stablo) spoji = 1;
            balansirano_stablo = rekonstrukcija_stabla(neizbalansirano_stablo);
            balansirano_stablo->roditelj = novi_roditelj;

            if (spoji == -1)
            {
                balansirano_stablo->roditelj->lijevo_dijete = balansirano_stablo;
            }
            else
            {
                balansirano_stablo->roditelj->desno_dijete = balansirano_stablo;
            }
        }
    }
}

template <typename tip>
void Binarno_stablo_pretrage<tip>::brisanje_elementa(tip element)
{
    if(!pronadji_element(element))
    {
        return;
    }

    Cvor *za_brisanje = pronalazak_cvora(element), *sljedbenik;

    //ako nas cvor ima desno dijete
    if (za_brisanje->desno_dijete != nullptr) {
        sljedbenik = za_brisanje->desno_dijete;
        while(sljedbenik->lijevo_dijete != nullptr)
            sljedbenik = sljedbenik->lijevo_dijete;

        Cvor *njegov_roditelj = sljedbenik->roditelj;

        while (njegov_roditelj != nullptr) {

            if (sljedbenik->element > njegov_roditelj->element) {
                njegov_roditelj->broj_desnih_potomaka = njegov_roditelj->broj_desnih_potomaka - 1;
            } else {
                njegov_roditelj->broj_lijevih_potomaka = njegov_roditelj->broj_lijevih_potomaka - 1;
            }

            njegov_roditelj = njegov_roditelj->roditelj;
        }

        // predzadnji list
        //ako je sljedbenik desno dijete od za_brisanje
        if (sljedbenik->roditelj == za_brisanje) {
            sljedbenik->roditelj = za_brisanje->roditelj;
            sljedbenik->lijevo_dijete = za_brisanje->lijevo_dijete;

            sljedbenik->broj_lijevih_potomaka = za_brisanje->broj_lijevih_potomaka;
            sljedbenik->broj_desnih_potomaka = za_brisanje->broj_desnih_potomaka;

            if (za_brisanje->lijevo_dijete != nullptr) {
                za_brisanje->lijevo_dijete->roditelj = sljedbenik;
            }

            if (za_brisanje == korijen) {
                korijen = sljedbenik;

            } else {
                //provjerimo da li je za_brisanje dd ili ld svog rod
                if (za_brisanje->roditelj->lijevo_dijete == za_brisanje) {
                    za_brisanje->roditelj->lijevo_dijete = sljedbenik;

                } else {
                    za_brisanje->roditelj->desno_dijete = sljedbenik;
                }
            }

        } else {
            sljedbenik->lijevo_dijete = za_brisanje->lijevo_dijete;
            sljedbenik->roditelj->lijevo_dijete = sljedbenik->desno_dijete;

            sljedbenik->broj_lijevih_potomaka = za_brisanje->broj_lijevih_potomaka;
            sljedbenik->broj_desnih_potomaka = za_brisanje->broj_desnih_potomaka;

            if(sljedbenik->desno_dijete != nullptr) {
                sljedbenik->desno_dijete->roditelj = sljedbenik->roditelj;
            }

            sljedbenik->roditelj = za_brisanje->roditelj;
            sljedbenik->desno_dijete = za_brisanje->desno_dijete;

            if(za_brisanje->lijevo_dijete != nullptr) {
                za_brisanje->lijevo_dijete->roditelj = sljedbenik;
            }

            if(za_brisanje == korijen) {
                korijen = sljedbenik;

            } else {
                //provjerimo da li je za_brisanje dd ili ld svog rod
                if(za_brisanje->roditelj->lijevo_dijete == za_brisanje) {
                    za_brisanje->roditelj->lijevo_dijete = sljedbenik;

                } else {
                    za_brisanje->roditelj->desno_dijete = sljedbenik;
                }
            }
        }

    }
        //ako nas cvor nema desno dijete
    else {

        if(za_brisanje->lijevo_dijete != nullptr) {
            za_brisanje->lijevo_dijete->roditelj = za_brisanje->roditelj;
        }

        if(za_brisanje == korijen) {
            korijen = za_brisanje->lijevo_dijete;

        } else {

            //provjerimo da li je za_brisanje dd ili ld svog rod
            if(za_brisanje->roditelj->lijevo_dijete == za_brisanje) {
                za_brisanje->roditelj->lijevo_dijete = za_brisanje->lijevo_dijete;

            } else {
                za_brisanje->roditelj->desno_dijete = za_brisanje->desno_dijete;
            }
        }

        Cvor *njegov_roditelj = za_brisanje->roditelj;

        while (njegov_roditelj != nullptr) {

            if (element > njegov_roditelj->element) {
                njegov_roditelj->broj_desnih_potomaka--;
            } else {
                njegov_roditelj->broj_lijevih_potomaka--;
            }

            njegov_roditelj = njegov_roditelj->roditelj;
        }
    }

    delete za_brisanje;
    velicina--;

    Cvor *neizbalansirano_stablo;
    if (da_li_je_izbalansirano(korijen, neizbalansirano_stablo))
    {
        Cvor *balansirano_stablo;
        if (neizbalansirano_stablo == korijen)
        {
            korijen = rekonstrukcija_stabla(neizbalansirano_stablo);
        }
        else
        {
            Cvor *novi_roditelj = neizbalansirano_stablo->roditelj;
            short int spoji(-1);
            if (neizbalansirano_stablo->roditelj->desno_dijete == neizbalansirano_stablo) spoji = 1;
            balansirano_stablo = rekonstrukcija_stabla(neizbalansirano_stablo);
            balansirano_stablo->roditelj = novi_roditelj;

            if (spoji == -1)
            {
                balansirano_stablo->roditelj->lijevo_dijete = balansirano_stablo;
            }
            else
            {
                balansirano_stablo->roditelj->desno_dijete = balansirano_stablo;
            }
        }
    }
}


#endif // STABLO_CPP
