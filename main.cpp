#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "Sciezka.h"
#include "MST.h"
#include "Przeplyw.h"

using namespace std;

int main()
{
    MST *mst = new MST;
    Sciezka *sciezka = new Sciezka;
    Przeplyw *przeplyw = new Przeplyw;

    int opcja=-1;

        while(opcja!=0)
        {

            system("cls");                                                             //wyczyszczenie ekranu oraz wyœwietlenie menu
            printf("\n\nDrogi uzytkowniku! Jakim probleme chcesz sie zajac?\n");
            printf("1. Wyznaczenie minimalnego drzewa rozpinajacego - MST\n");
            printf("2. Wyznaczenie najkrotszej sciezki w grafie\n");
            printf("3. Wyznaczenie maksymalnego przeplywu\n");
            printf("4. Pomiary\n");
            printf("0. Wyjdz z programu\n");

            scanf("%i", &opcja);

            switch (opcja)                                                              //wybór opcji oraz wywo³anie odpowiedniego menu
            {
            case 0:
                return 0;
                break;
            case 1:
				mst ->menu_MST();
		        break;
            case 2:
            	sciezka->menu_sciezki();
                break;
            case 3:
            	przeplyw ->menu_przeplywu();
                break;
            case 4:
                //mst -> pomiar_czasu();
                //sciezka -> pomiar_czasu();
            	przeplyw -> pomiar_czasu();
                break;
            default:
                printf("Podaj wlasciwa opcje."); Sleep(2000);
                break;
            }
		}

    delete mst;
    delete sciezka;
    delete przeplyw;

    return 0;
}
