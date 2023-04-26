#include "Kolejka.h"


using namespace std;

Kolejka::Kolejka(int n){
    kopiec = new Krawedz[n];
    pozycja = 0;
}
Kolejka::~Kolejka(){
    delete [] kopiec;
}
Krawedz Kolejka::korzen(){
    return kopiec[0];
}
void Kolejka::wstaw(Krawedz k){
    int i, j;

    i = pozycja++;
    j = (i - 1) / 2;

    while(i > 0 && kopiec[j].waga > k.waga){
        kopiec[i] = kopiec[j];
        i = j;
        j = (i - 1)/2;
    }

    kopiec[i] = k;
}
void Kolejka::usun(){
    int i, j;
    Krawedz k;

    if(pozycja > 0){
        pozycja--;

        k = kopiec[pozycja];

        i = 0;
        j = 1;

        while( j < pozycja){
            if( j+1 < pozycja && kopiec[j + 1].waga < kopiec[j].waga)
                j++;
            if(k.waga <= kopiec[j].waga)
                break;

            i = j;
            j = (i - 1)/2;
        }

        kopiec[i] = k;
    }
}