#include "MST.h"
#include "Path.h"

using namespace std;

int main()
{
    bool loop = true;
    int choice;
    MST *mst = new MST;
    Path *path = new Path;
    while(loop){
        cout << "1. Minimum Spanning Tree" << endl;
        cout << "2. Dijkstra" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                mst->MST_menu();
                break;
            case 2:
                path->menu();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }   
    }

    delete mst;
    delete path;

    return 0;
}
