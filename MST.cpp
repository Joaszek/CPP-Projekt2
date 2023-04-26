#include<iostream>
#include "MST.h"
#include <iomanip>
#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

void MST::menu_MST(){

    int opcja=-1;

        while(opcja!=0)
        {
            printf("\n\nDrogi uzytkowniku! Co chcesz zrobic?\n");
            printf("1. Wczytac graf z pliku\n");
            printf("2. Wygenerowac losowy graf o zadanej gestosci\n");
            printf("3. Wyznaczyc minimalne drzewo rozpinajace algorytmem Prima z listy\n");
            printf("4. Wyznaczyc minimalne drzewo rozpinajace algorytmem Prima z macierzy\n");
            printf("5. Wyznaczyc minimalne drzewo rozpinajace algorytmem Kruskala z listy\n");
            printf("6. Wyznaczyc minimalne drzewo rozpinajace algorytmem Kruskala z macierzy\n");
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
                printf("Podaj ilosc wierzcholkow w grafie, ktory chcesz wygenerowac: ");
                    cin >> l_wierzcholkow;
                printf("Podaj w procentach gestosc grafu, ktory chcesz wygenerowac: ");
                    cin >> gestosc;
                wygeneruj_graf();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 3:
                Prim_lista();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 4:
                Prim_macierzowo();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 5:
                Kruskal_lista();
                wyswietl_liste_sasiadow();
                wyswietl_macierz();
                break;
            case 6:
                Kruskal_macierzowo();
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
void MST::stworz_graf_z_pliku(){

    string nazwa_pliku;
    int v1, v2, waga;

    printf("Podaj nazwe pliku, z którego chcesz wczytac graf: ");
    cin >> nazwa_pliku;
    ifstream plik;                                                                  //wczytanie pliku oraz rozmiaru kopca z niego
    plik.open(nazwa_pliku.c_str(), ios::in);
    plik >> l_krawedzi >> l_wierzcholkow;

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

        p = new Lista_sasiadow;
        p -> sasiad = v1;
        p -> nast = sasiedzi [v2];
        p -> waga = waga;
        sasiedzi [v2] = p;

        graf[v1][v2] = waga;
        graf[v2][v1] = waga;

    }
}
void MST::wygeneruj_graf(){
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

    for(int i = 0; i < l_wierzcholkow - 1; i++){
        index_z_grafu = rand()%(i+1);
        index_spoza_grafu = rand()%(l_wierzcholkow - i - 1);
        v1 = w_grafie[index_z_grafu];
        v2 = nie_w_grafie[index_spoza_grafu];
        waga = rand()%1000000 + 1;
        nie_w_grafie[index_spoza_grafu] = 0;
        w_grafie[i+1] = v2;
        sort(nie_w_grafie, nie_w_grafie + l_wierzcholkow - i - 1, greater <int>());

        graf[v1][v2] = waga;
        graf[v2][v1] = waga;

        p = new Lista_sasiadow;
        p -> sasiad = v2;
        p -> nast = sasiedzi [v1];
        p -> waga = waga;
        sasiedzi [v1] = p;

        p = new Lista_sasiadow;
        p -> sasiad = v1;
        p -> nast = sasiedzi [v2];
        p -> waga = waga;
        sasiedzi [v2] = p;
    }

    l_krawedzi = gestosc * l_wierzcholkow * (l_wierzcholkow - 1) / 2 / 100;

    for(int i = l_wierzcholkow - 1; i < l_krawedzi; i++){
        v1 = rand()%l_wierzcholkow;
        v2 = rand()%l_wierzcholkow;

        while(v1 == v2 || graf[v1][v2] != 0 ){
            v1 = rand()%l_wierzcholkow;
            v2 = rand()%l_wierzcholkow;
        }
        waga = rand()%100 + 1;

        graf[v1][v2] = waga;
        graf[v2][v1] = waga;

        p = new Lista_sasiadow;
        p -> sasiad = v2;
        p -> nast = sasiedzi [v1];
        p -> waga = waga;
        sasiedzi [v1] = p;

        p = new Lista_sasiadow;
        p -> sasiad = v1;
        p -> nast = sasiedzi [v2];
        p -> waga = waga;
        sasiedzi [v2] = p;
    }
}
void MST::wyswietl_liste_sasiadow(){
    for(int i = 0; i < l_wierzcholkow; i++){
        cout << "\n" << i << " = ";
        p = sasiedzi[i];
        while( p ){
            cout << setw(3) << p->sasiad << ":" << p->waga;
            p = p->nast;
        }
    }
}
void MST::wyswietl_macierz(){
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
void MST::wyswietl_mst(Krawedz mst[]){
    cout << "Minimalne drzewo rozpinajace o wadze " << waga << ":\n";
    for(int i = 0; i < l_wierzcholkow - 1; i++){
        cout << mst[i].v1 << "-" << mst[i].v2 << ":" << mst[i].waga << "\n";
    }
}
void MST::Prim_lista(){
    Krawedz k;
    int v = 0;
    pozycja = 0;
    waga = 0;

    Krawedz kolejka[l_krawedzi];
    Krawedz mst[l_wierzcholkow - 1];
    bool *wierzcholki = new bool [ l_wierzcholkow ];

    for(int i = 0; i < l_wierzcholkow; i++)
        wierzcholki[i] = false;

    for(int i = 0; i < l_wierzcholkow - 1; i++){
        wierzcholki[v] = true;
        p = sasiedzi[v];
        while(p){
            if(!wierzcholki[p->sasiad]){
                k.v1 = v;
                k.v2 = p->sasiad;
                k.waga = p->waga;
                wstaw_do_kolejki(k, kolejka);
            }
            p = p->nast;
        }
        do{
            k = korzen(kolejka);
            usun_pierwszy_z_kolejki(kolejka);
        }while(wierzcholki[k.v1] && wierzcholki[k.v2] );

        if(wierzcholki[k.v1]){
            v = k.v2;
            wierzcholki[k.v2] = true;
        }
        else{
            v = k.v1;
            wierzcholki[k.v1] = true;
        }
        mst[i] = k;
        waga += k.waga;
    }
    wyswietl_mst(mst);
}
void MST::Prim_macierzowo(){
    Krawedz k;
    int v = 0;
    pozycja = 0;
    waga = 0;

    Krawedz kolejka[l_krawedzi];
    Krawedz mst[l_wierzcholkow - 1];
    bool *wierzcholki = new bool [ l_wierzcholkow ];

    for(int i = 0; i < l_wierzcholkow; i++)
        wierzcholki[i] = false;
    for(int i = 0; i < l_wierzcholkow - 1; i++){
        wierzcholki[v] = true;
        for(int j = 0; j < l_wierzcholkow; j++){
            if(!wierzcholki[j] && graf[v][j]!=0){
                k.v1 = v;
                k.v2 = j;
                k.waga = graf[v][j];
                wstaw_do_kolejki(k, kolejka);
            }
        }
        do{
            k = korzen(kolejka);
            usun_pierwszy_z_kolejki(kolejka);
        }while(wierzcholki[k.v1] && wierzcholki[k.v2] );

        if(wierzcholki[k.v1]){
            v = k.v2;
            wierzcholki[k.v2] = true;
        }
        else{
            v = k.v1;
            wierzcholki[k.v1] = true;
        }
        mst[i] = k;
        waga += k.waga;
    }
    wyswietl_mst(mst);
}
void MST::Kruskal_lista(){
    Krawedz k;

    Z = new Zbiory [l_wierzcholkow];
    Krawedz kolejka[l_krawedzi];
    Krawedz mst[l_wierzcholkow - 1];
    waga = 0;
    pozycja = 0;

    for(int i = 0; i < l_wierzcholkow; i++)
        stworz_zbior(i);
    for(int i = 0; i < l_wierzcholkow; i++){
        p = sasiedzi[i];
        while(p){
            if(p->sasiad >= i){
                k.v1 = i;
                k.v2 = p->sasiad;
                k.waga = p->waga;
                wstaw_do_kolejki(k, kolejka);
            }
            p = p->nast;
        }
    }
    for(int i = 0; i < l_wierzcholkow - 1; i++){
        do{
            k = korzen(kolejka);
            usun_pierwszy_z_kolejki(kolejka);
        }while(znajdz_zbior(k.v1)==znajdz_zbior(k.v2));

        mst[i] = k;
        polacz_zbiory(k);
        waga += k.waga;
    }
    wyswietl_mst(mst);                                                                                   //nienaiwna implementacja ziorów rozlacznych
}
void MST::Kruskal_macierzowo(){
    Krawedz k;

    Z = new Zbiory [l_wierzcholkow];
    Krawedz kolejka[l_krawedzi];
    Krawedz mst[l_wierzcholkow - 1];
    waga = 0;
    pozycja = 0;

    for(int i = 0; i < l_wierzcholkow; i++)
        stworz_zbior(i);
    for(int i = 0; i < l_wierzcholkow; i++){
        for(int j = i; j < l_wierzcholkow; j++){
            if(graf[i][j] != 0){
                k.v1 = i;
                k.v2 = j;
                k.waga = graf[i][j];
                wstaw_do_kolejki(k, kolejka);
            }
        }
    }

    for(int i = 0; i < l_wierzcholkow - 1; i++){
        do{
            k = korzen(kolejka);
            usun_pierwszy_z_kolejki_Kruskal(kolejka);
        }while(znajdz_zbior(k.v1)==znajdz_zbior(k.v2));

        mst[i] = k;
        polacz_zbiory(k);
        waga += k.waga;
    }
    wyswietl_mst(mst);
}
MST::Krawedz MST::korzen(Krawedz kolejka[]){
    return kolejka[0];
}
void MST::wstaw_do_kolejki(Krawedz k, Krawedz kolejka[]){
    int i, j;
    i = pozycja++;
    j = (i - 1) / 2;

    while(i > 0 && kolejka[j].waga > k.waga){
        kolejka[i] = kolejka[j];
        i = j;
        j = (i - 1)/2;
    }

    kolejka[i] = k;
}
void MST::usun_pierwszy_z_kolejki(Krawedz kolejka[]){
    int sl, sp;
    Krawedz k;

    pozycja--;
    kolejka[0] = kolejka[pozycja];

    int i, j;
    i = 0;
    sl = 1;
    sp = 2;

    while((kolejka[i].waga > min(kolejka[sl].waga, kolejka[sp].waga)) && pozycja > 2*i)
    {

        sl = 2*i + 1;
        sp = 2*i + 2;
        if(pozycja  == sl){

            if(kolejka[sl].waga < kolejka[i].waga){
                k = kolejka[i];
			    kolejka[i] = kolejka[j];
			    kolejka[j] = k;
            }
            break;
        }
        else{
            if(min(kolejka[sl].waga, kolejka[sp].waga) < kolejka[i].waga){
                if(kolejka[sl].waga <= kolejka[sp].waga)
                    j = sl;
                else
                    j = sp;

                k = kolejka[i];
			    kolejka[i] = kolejka[j];
			    kolejka[j] = k;
			    i = j;
            }
        }
    }

}
void MST::usun_pierwszy_z_kolejki_Kruskal(Krawedz kolejka[]){
    int sl, sp;
    Krawedz k;

    pozycja--;
    kolejka[0] = kolejka[pozycja];

    int i, j;
    i = 0;
    sl = 1;
    sp = 2;

    while((kolejka[i].waga > min(kolejka[sl].waga, kolejka[sp].waga)) && pozycja >= 2*i)
    {

        sl = 2*i + 1;
        sp = 2*i + 2;
        if(pozycja  == sl){

            if(kolejka[sl].waga < kolejka[i].waga){
                k = kolejka[i];
			    kolejka[i] = kolejka[j];
			    kolejka[j] = k;
            }
            break;
        }
        else{
            if(min(kolejka[sl].waga, kolejka[sp].waga) < kolejka[i].waga){
                if(kolejka[sl].waga <= kolejka[sp].waga)
                    j = sl;
                else
                    j = sp;

                k = kolejka[i];
			    kolejka[i] = kolejka[j];
			    kolejka[j] = k;
			    i = j;
            }
        }
    }

}
void MST::stworz_zbior ( int v ){
    Z [ v ].korzen   = v;
    Z [ v ].moc = 0;
}
int MST::znajdz_zbior ( int v ){
    if( Z [ v ].korzen != v )
        Z [ v ].korzen = znajdz_zbior ( Z [ v ].korzen );
    return Z [ v ].korzen;
}
void MST::polacz_zbiory ( Krawedz k ){
    int ru, rv;

    ru = znajdz_zbior ( k.v1 );   // Wyznaczamy korzeń drzewa z węzłem u
    rv = znajdz_zbior ( k.v2 );   // Wyznaczamy korzeń drzewa z węzłem v
    if( ru != rv )           // Korzenie muszą być różne
    {
        if( Z [ ru ].moc > Z [ rv ].moc ) // Porównujemy rangi drzew
            Z [ rv ].korzen = ru;    // ru większe, dołączamy rv
        else
        {
            Z [ ru ].korzen = rv;    // równe lub rv większe, dołączamy ru
            if( Z [ ru ].moc == Z [ rv ].moc )
                Z [ rv ].moc++;
        }
    }
}
void MST::pomiar_czasu(){

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
        nazwa = "MST_PrimLista_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;                                                 //stworzenie nazwy pliku

        ofstream fout;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            auto begin = std::chrono::steady_clock::now();
            Prim_lista();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        nazwa = "MST_PrimMacierz_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            auto begin = std::chrono::steady_clock::now();
            Prim_macierzowo();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        nazwa = "MST_KruskalLista_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            auto begin = std::chrono::steady_clock::now();
            Kruskal_lista();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        nazwa = "MST_KruskalMacierz_";
        nazwa = nazwa + rozmiar + podkreslnik + gest + txt;
        fout.open(nazwa);
        srand(time(NULL));

        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            wygeneruj_graf();
            auto begin = std::chrono::steady_clock::now();
            Kruskal_macierzowo();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();
    }
}
