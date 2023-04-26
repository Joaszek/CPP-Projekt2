#include "Kolejka.h"
#include<stdlib.h>

using namespace std;

class Tree{

    struct Node{
        Node *next;
        int w, wage;
    };

private:
    Node **neighbours;
    int dl;
    int wage;

public:
    stworz_drzewo(int n);
    usun_drzewo();
    void dodaj_krawedz_do_drzewa(Krawedz k);
    Node *poczatek_listy(int n);
    void wyswietl_drzewo();
};
