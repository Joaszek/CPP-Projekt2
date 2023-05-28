#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;

class Path{
public:
    struct Neighbour{
        Neighbour *next;
        int neighbour;
        int wage;
    };
    const int inf = 2147483647;

    Neighbour ** neighbours;
    Neighbour *p, *r;

    int ** graph;
    int number_of_edges, number_of_vertexes, beginning_vertex;
    int wage;
    int density;
    int *previous;
    long long *cost_to_reach;

    void path_menu();
    void create_graph_from_file();
    void generate_graph();

    void print_matrix();
    void print_neighbours_list();

    void dijkstra_matrix();
    void dijkstra_list();


    void print_paths();

    void measure_time();
};
