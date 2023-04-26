#include <iostream>
#include "Sciezka.h"
#include <iomanip>
#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

void Sciezka::menu_sciezki(){

    int opcja=-1;

        while(opcja!=0)
        {
            printf("\n\nDrogi uzytkowniku! Co chcesz zrobic?\n");
            printf("1. Wczytac graf z pliku\n");
            printf("2. Wygenerowac losowy graf o zadanej gestosci\n");
            printf("3. Wyznaczyc najkrotsze sciezki algorytmem Dijkstry z listy\n");
            printf("4. Wyznaczyc najkrotsze sciezki algorytmem Dijkstry z macierzy\n");
            printf("5. Wyznaczyc najkrotsze sciezki algorytmem Forda-Bellmana z listy\n");
            printf("6. Wyznaczyc najkrotsze sciezki algorytmem Forda-Bellmana z macierzy\n");
            printf("7. Wyswietlic graf\n");
            printf("0. Wyjdz z programu\n");

            scanf("%i", &opcja);

            switch (opcja)                                                              //wybór opcji oraz wywo³anie odpowiedniego menu
            {
            case 0:
                break;
            case 1:
                graf = NULL;
                sasiedzi = NULL;
                l_wierzcholkow = 0;
                l_krawedzi = 0;
                stworz_graf_z_pliku();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
		        break;
            case 2:
                graf = NULL;
                sasiedzi = NULL;
                l_wierzcholkow = 0;
                l_krawedzi = 0;
                l_krawedzi = 0;
                printf("Podaj ilosc wierzcholkow w grafie, ktory chcesz wygenerowac: ");
                    cin >> l_wierzcholkow;
                printf("Podaj w procentach gestosc grafu, ktory chcesz wygenerowac: ");
                    cin >> gestosc;
                wygeneruj_graf();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 3:
                Dijkstra_lista();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 4:
                Dijkstra_macierzowo();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 5:
                Ford_lista();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 6:
                Ford_macierzowo();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 7:
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            default:
                printf("Podaj wlasciwa opcje."); Sleep(2000);
                break;
            }
		}
}
void Sciezka::stworz_graf_z_pliku(){

    string nazwa_pliku;
    int v1, v2, waga;

    printf("Podaj nazwe pliku, z którego chcesz wczytac graf: ");
    cin >> nazwa_pliku;
    ifstream plik;                                                                  //wczytanie pliku oraz rozmiaru kopca z niego
    plik.open(nazwa_pliku.c_str(), ios::in);
    plik >> l_krawedzi >> l_wierzcholkow >> wierzcholek_pocz;

    sasiedzi = new Lista_sasiadow *[l_krawedzi];

    graf = new int *[l_wierzcholkow];
    for(int i = 0; i < l_wierzcholkow; i++) graf[i] = new int [l_wierzcholkow];

    for(int i = 0; i < l_wierzcholkow; i++) sasiedzi[i] = NULL;
    for(int i = 0; i < l_wierzcholkow; i++) for(int j = 0; j < l_wierzcholkow; j++) graf[i][j] = 0;


    for(int i = 0; i < l_krawedzi; i++){
        plik >> v1 >> v2 >> waga;
        p = new Lista_sasiadow;
        p -> sasiad = v2;
        p -> nast = sasiedzi [v1];
        p -> waga = waga;
        sasiedzi [v1] = p;

        graf[v1][v2] = waga;
    }
}
void Sciezka::wyswietl_liste_sasiadow(){
    for(int i = 0; i < l_wierzcholkow; i++){
        cout << "\n" << i << " = ";
        p = sasiedzi[i];
        while( p ){
            cout << setw(3) << p->sasiad << ":" << p->waga;
            p = p->nast;
        }
    }
}
void Sciezka::wyswietl_macierz(){
    cout << "\n\n   ";
    for(int i = 0; i < l_wierzcholkow; i++)
        cout << setw(6) << i;
    cout << "\n";
    for(int i = 0; i < l_wierzcholkow; i++){
        cout << setw(6) << i;
        for(int j = 0; j < l_wierzcholkow; j++)
            cout << setw(6) << graf[i][j];
        cout << "\n";
    }
}
void Sciezka::wygeneruj_graf(){

    srand(time(NULL));
    sasiedzi = new Lista_sasiadow *[l_wierzcholkow * (l_wierzcholkow - 1) / 2];
    int v1, v2, waga;
    int index_z_grafu, index_spoza_grafu;

    graf = new int *[l_wierzcholkow];
    for(int i = 0; i < l_wierzcholkow; i++) graf[i] = new int [l_wierzcholkow];

    for(int i = 0; i < l_wierzcholkow; i++) sasiedzi[i] = NULL;
    for(int i = 0; i < l_wierzcholkow; i++) for(int j = 0; j < l_wierzcholkow; j++) graf[i][j] = 0;
    int w_grafie[l_wierzcholkow + 1];
    int nie_w_grafie[l_wierzcholkow];

    w_grafie[0] = 0;
    for(int i = 0; i < l_wierzcholkow - 1; i++) nie_w_grafie[i] = i+1;

    index_spoza_grafu = rand()%(l_wierzcholkow - 1);
    v2 = 0;
    v1 = nie_w_grafie[index_spoza_grafu];
    waga = rand()%100 + 1;
    p = new Lista_sasiadow;
    p -> sasiad = v2;
    p -> nast = sasiedzi [v1];
    p -> waga = waga;
    sasiedzi [v1] = p;graf[v1][v2] = waga;


    for(int i = 0; i < l_wierzcholkow - 1; i++){
        index_z_grafu = rand()%(i+1);
        index_spoza_grafu = rand()%(l_wierzcholkow - i - 1);
        v1 = w_grafie[index_z_grafu];
        v2 = nie_w_grafie[index_spoza_grafu];
        waga = rand()%100 + 1;
        nie_w_grafie[index_spoza_grafu] = 0;
        w_grafie[i+1] = v2;
        sort(nie_w_grafie, nie_w_grafie + l_wierzcholkow - i - 1, greater <int>());

        graf[v1][v2] = waga;

        p = new Lista_sasiadow;
        p -> sasiad = v2;
        p -> nast = sasiedzi [v1];
        p -> waga = waga;
        sasiedzi [v1] = p;
    }

    l_krawedzi = gestosc * l_wierzcholkow * (l_wierzcholkow - 1) / 2 / 100;

    for(int i = l_wierzcholkow - 1; i < l_krawedzi; i++){
        v1 = rand()%l_wierzcholkow;
        v2 = rand()%l_wierzcholkow;

        while(v1 == v2 || graf[v1][v2] != 0 ){
            v1 = rand()%l_wierzcholkow;
            v2 = rand()%l_wierzcholkow;
        }
        waga = rand()%1000000 + 1;

        graf[v1][v2] = waga;

        p = new Lista_sasiadow;
        p -> sasiad = v2;
        p -> nast = sasiedzi [v1];
        p -> waga = waga;
        sasiedzi [v1] = p;
    }
}
void Sciezka::Dijkstra_lista(){
    int u, j;
    bool *QS;

    koszt_dojscia = new long long [l_wierzcholkow];
    poprzednik = new int [l_wierzcholkow];
    QS = new bool [l_wierzcholkow];

    for(int i = 0; i < l_wierzcholkow; i++){
        koszt_dojscia[i] = inf;
        poprzednik[i] = -1;
        QS[i] = false;
    }

    koszt_dojscia[wierzcholek_pocz] = 0;

    for(int i = 0; i < l_wierzcholkow; i++){
        for(j = 0; QS[j]; j++);
        for(u = j++; j < l_wierzcholkow; j++)
            if(!QS[j] && (koszt_dojscia[j] < koszt_dojscia[u]))
                u = j;
        QS[u] = true;

        for( p = sasiedzi[u]; p; p = p->nast)
            if( !QS [p->sasiad] && (koszt_dojscia[p->sasiad] > koszt_dojscia[u] + p->waga))
            {
                koszt_dojscia [p->sasiad] = koszt_dojscia[u] + p->waga;
                poprzednik [p->sasiad] = u;
            }
    }

    wypisz_sciezki();
}
void Sciezka::Dijkstra_macierzowo(){
    int u, j;
    bool *QS;

    koszt_dojscia = new long long [l_wierzcholkow];
    poprzednik = new int [l_wierzcholkow];
    QS = new bool [l_wierzcholkow];

    for(int i = 0; i < l_wierzcholkow; i++){
        koszt_dojscia[i] = inf;
        poprzednik[i] = -1;
        QS[i] = false;
    }

    koszt_dojscia[wierzcholek_pocz] = 0;

    for(int i = 0; i < l_wierzcholkow; i++){
        for(j = 0; QS[j]; j++);
        for(u = j++; j < l_wierzcholkow; j++)
            if(!QS[j] && (koszt_dojscia[j] < koszt_dojscia[u]))
                u = j;
        QS[u] = true;

        for( int v = 0; v < l_wierzcholkow; v++)
            if( graf[u][v]!= 0 && !QS [v] && (koszt_dojscia[v] > koszt_dojscia[u] + graf[u][v]))
            {
                koszt_dojscia [v] = koszt_dojscia[u] + graf[u][v];
                poprzednik [v] = u;
            }
    }

    wypisz_sciezki();

    delete koszt_dojscia;
    delete poprzednik;
    delete QS;
}
void Sciezka::Ford_lista(){

    koszt_dojscia = new long long [l_wierzcholkow];
    poprzednik = new int [l_wierzcholkow];
    bool ujemny_cykl = false;
    bool test;

    for(int i = 0; i < l_wierzcholkow; i++){
        koszt_dojscia[i] = inf;
        poprzednik[i] = -1;
    }

    koszt_dojscia[wierzcholek_pocz] = 0;

    for(int i = 1; i < l_wierzcholkow; i++){
        test = true;

        for(int v = 0; v < l_wierzcholkow; v++)
            for(p = sasiedzi[v]; p; p = p -> nast)
                if(koszt_dojscia[p->sasiad] > koszt_dojscia[v] + p->waga)
                {
                    test = false;
                    koszt_dojscia[p->sasiad] = koszt_dojscia[v] + p->waga;
                    poprzednik[p->sasiad] = v;
                }
            if(test){
                cout <<"brak zmian";
                break;
            }
    }

    for(int v = 0; v < l_wierzcholkow; v++)
        for(p = sasiedzi[v]; p; p = p->nast)
            if(koszt_dojscia[p ->sasiad] > koszt_dojscia[v] + p->waga)
                ujemny_cykl = true;

    if(ujemny_cykl)
        cout << "\nW grafie wystepuje ujemny cykl\n";
    else
        wypisz_sciezki();
}
void Sciezka::Ford_macierzowo(){

    koszt_dojscia = new long long [l_wierzcholkow];
    poprzednik = new int [l_wierzcholkow];
    bool ujemny_cykl = false;
    bool test;

    for(int i = 0; i < l_wierzcholkow; i++){
        koszt_dojscia[i] = inf;
        poprzednik[i] = -1;
    }

    koszt_dojscia[wierzcholek_pocz] = 0;

    for(int i = 1; i < l_wierzcholkow; i++){
        test = true;

        for(int u = 0; u < l_wierzcholkow; u++)
            for(int v = 0; v < l_wierzcholkow; v++)
                if(graf[u][v]!= 0 && koszt_dojscia[v] > koszt_dojscia[u] + graf[u][v])
                {
                    test = false;
                    koszt_dojscia[v] = koszt_dojscia[u] + graf[u][v];
                    poprzednik[v] = u;
                }
            if(test){
                cout <<"brak zmian";
                break;
            }
    }

    for(int u = 0; u < l_wierzcholkow; u++)
        for(int v = 0; v < l_wierzcholkow; v++)
            if(graf[u][v]!= 0 && koszt_dojscia[v] > koszt_dojscia[u] + graf[u][v])
                ujemny_cykl = true;

    if(ujemny_cykl)
        cout << "\nW grafie wystepuje ujemny cykl\n";
    else
        wypisz_sciezki();
}
void Sciezka::wypisz_sciezki(){
    int *S, stos;

    S = new int [l_wierzcholkow];
    stos = 0;

    cout << "\nNajkrotsze sciezki z wierzcholka " << wierzcholek_pocz << "\n" ;
    for( int i = 0; i < l_wierzcholkow; i++)
    {
        cout << i << ": ";
        for(int j = i; j > -1; j = poprzednik[j])
            S [stos++] = j;

        while(stos)
            cout << S[ --stos ] << " ";

        cout << "$" << koszt_dojscia [i] << "\n";
    }
}
void Sciezka::pomiar_czasu(){

    int wielkosc[21][2] = { {10, 20}, {10, 60}, {10, 99}, {25, 20}, {25, 60}, {25, 99}, {50, 20}, {50, 60}, {50, 99},
                            {75, 20}, {75, 60}, {75, 99}, {100, 20}, {100, 60}, {100, 99}, {150, 20}, {150, 60}, {150, 99}, {200, 20}, {200, 60}, {200, 99}};

    for(int i = 0; i < 21; i++){

        l_wierzcholkow = wielkosc[i][0];
        gestosc = wielkosc[i][1];

        string nazwa;
        string txt = ".txt";
        string podkreslnik = "_";
        string rozmiar, gest;
        rozmiar = to_string(l_wierzcholkow);
        gest = to_string(gestosc);
        nazwa = "Sciezka_DijkstraLista_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;                                                 //stworzenie nazwy pliku

        ofstream fout;
        fout.open(nazwa);
        srand(time(NULL));


        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            wierzcholek_pocz = rand()%l_wierzcholkow;
            auto begin = std::chrono::steady_clock::now();
            Dijkstra_lista();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        nazwa = "Sciezka_DijkstraMacierz_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            wierzcholek_pocz = rand()%l_wierzcholkow;
            auto begin = std::chrono::steady_clock::now();
            Dijkstra_macierzowo();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        nazwa = "Sciezka_FordLista_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            wierzcholek_pocz = rand()%l_wierzcholkow;
            auto begin = std::chrono::steady_clock::now();
            Ford_lista();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        nazwa = "Sciezka_FordMacierz_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            wierzcholek_pocz = rand()%l_wierzcholkow;
            auto begin = std::chrono::steady_clock::now();
            Ford_macierzowo();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();
    }
}
