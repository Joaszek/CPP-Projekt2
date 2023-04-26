#include "Drzewo.h"
#include <iomanip>
#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "Kolejka.h"

using namespace std;

Drzewo::Drzewo(int n){

    sasiedzi = new Wezel *[n];
    for(int i = 0; i < n; i++){
        sasiedzi[i] = NULL;
    }
    dl = n - 1;
    waga = 0;
}
Drzewo::~Drzewo(){

    Wezel *p, *r;

    for(int i = 0; i < dl; i++){
        p = sasiedzi[i];
        while(p){
            r = p;
            p = p->nastepny;
            delete r;
        }
    }

    delete [] sasiedzi;
}
void Drzewo::dodaj_krawedz(Krawedz k){
    Wezel *p;

    waga = waga + k.waga;
    p = new Wezel;
    p->w = k.v2;
    p->waga = k.waga;
    p->nastepny = sasiedzi[k.v1];
    sasiedzi[k.v1] = p;

    waga = waga + k.waga;
    p = new Wezel;
    p->w = k.v1;
    p->waga = k.waga;
    p->nastepny = sasiedzi[k.v2];
    sasiedzi[k.v2] = p;
}
Wezel *Drzewo::poczatek_listy(int n){
        return sasiedzi[n]
}
void Drzewo::print(){
    Wezel *p;

    for(int i = 0; i < dl; i++){
        cout << "\nWierzcho�ek " << i << " - ";
        for(p = sasiedzi[i]; p; p = p->nastepny)
            cout << p->w << ":" << p->waga << " ";
    }
    cout << "\n\n Waga MST: " << waga;
}
