#include "MST.h"
#include "Flow.h"
#include "Path.h"
using namespace std;

int main()
{
    MST *mst = new MST;
    Path *path = new Path;
    Flow *flow = new Flow;

    int option = -1;

    while (option != 0)
    {
        // wyczyszczenie ekranu oraz wyœwietlenie menu
        system("cls");
        cout << "\n\nEnter option" << endl;
        cout << "1. Determination of the minimum spanning tree - MST" << endl;
        cout << "2. Finding the shortest path in a graph" << endl;
        cout << "3. Determining the maximum flow" << endl;
        cout << "4. Tests" << endl;
        cout << "5. Exit" << endl;

        cin >> option;

        switch (option) // wybór opcji oraz wywo³anie odpowiedniego menu
        {
        case 1:
            mst->MST_menu();
            break;
        case 2:
            path->path_menu();
            break;
        case 3:
            flow->flow_menu();
            break;
        case 4:
            // mst -> pomiar_czasu();
            // sciezka -> pomiar_czasu();
            // przeplyw -> pomiar_czasu();
            break;
        case 5:
            return 0;
            break;
        default:
            cout << "Enter correct option" << endl;
            Sleep(2000);
            break;
        }
    }

    delete mst;
    delete path;
    delete flow;

    return 0;
}
