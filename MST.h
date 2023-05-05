#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono> 
#include <algorithm>
#include <windows.h>

using namespace std;

class MST{
public:
    struct Edge{
        int v1, v2, wage;
    };
    struct List_of_neighbours{
        List_of_neighbours *next;
        int neighbour;
        int wage;
    };
    struct Datasets{
        int root, power;
    };

    List_of_neighbours ** neighbours;
    List_of_neighbours *p;

    Datasets *datasets;
    int ** graph;
    int number_of_edges, number_of_vertexes, position;
    int wage;
    int density;

    void MST_menu();
    void create_graph_from_file();
    void generate_graph();

    void print_matrix();
    void print_list_of_neighbours();
    void print_mst(Edge mst[]);

    void prim_matrix();
    void prim_list();

    void kruskal_matrix();
    void kruskal_list();

    Edge root(Edge queue[]);
    void add_to_the_queue( Edge k, Edge queue[]);
    void delete_first_from_queue(Edge queue[]);
    void delete_first_from_queue_Kruskal(Edge queue[]);

    void create_dataset(int v);
    int find_dataset(int v);
    void connect_datasets(Edge k);

    void measure_time();
};