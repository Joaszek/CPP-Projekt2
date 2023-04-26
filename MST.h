#include<stdlib.h>

using namespace std;

class MST{
public:
    struct Krawedz{
        int v1, v2, waga;
    };
    struct Lista_sasiadow{
        Lista_sasiadow *nast;
        int sasiad;
        int waga;
    };
    struct Zbiory{
        int korzen, moc;
    };

    Lista_sasiadow ** sasiedzi;
    Lista_sasiadow *p;

    Zbiory *Z;
    int ** graf;
    int l_krawedzi, l_wierzcholkow, pozycja;
    int waga;
    int gestosc;

    void menu_MST();
    void stworz_graf_z_pliku();
    void wygeneruj_graf();

    void wyswietl_macierz();
    void wyswietl_liste_sasiadow();
    void wyswietl_mst(Krawedz mst[]);

    void Prim_macierzowo();
    void Prim_lista();

    void Kruskal_macierzowo();
    void Kruskal_lista();

    Krawedz korzen(Krawedz kolejka[]);
    void wstaw_do_kolejki( Krawedz k, Krawedz kolejka[]);
    void usun_pierwszy_z_kolejki(Krawedz kolejka[]);
    void usun_pierwszy_z_kolejki_Kruskal(Krawedz kolejka[]);

    void stworz_zbior(int v);
    int znajdz_zbior(int v);
    void polacz_zbiory(Krawedz k);

    void pomiar_czasu();
};

#endif // MST_H
