#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

class Queue
{
    struct Edge
    {
        int v1, v2, wage;
    };

private:
    Edge *heap;
    int position;

public:
    void create_heap(int n);
    void delete_queue();
    Edge root();
    void insert_into_queue(Edge k);
    void delete_first_from_queue();
};
