#include<stdlib.h>

using namespace std;

class Sciezka{
public:
    struct Lista_sasiadow{
        Lista_sasiadow *nast;
        int sasiad;
        int waga;
    };
    const int inf = 2147483647;

    Lista_sasiadow ** sasiedzi;
    Lista_sasiadow *p, *r;

    int ** graf;
    int l_krawedzi, l_wierzcholkow, wierzcholek_pocz;
    int waga;
    int gestosc;
    int *poprzednik;
    long long *koszt_dojscia;

    void menu_sciezki();
    void stworz_graf_z_pliku();
    void wygeneruj_graf();

    void wyswietl_macierz();
    void wyswietl_liste_sasiadow();

    void Dijkstra_macierzowo();
    void Dijkstra_lista();

    void Ford_macierzowo();
    void Ford_lista();

    void wypisz_sciezki();

    void pomiar_czasu();
};

#endif // Sciezka_H
