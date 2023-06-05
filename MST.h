#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <windows.h>


class MST{
public:
    struct Edge{
        int v1, v2, weight;
    };
    struct Neighbour{
        Neighbour *next;
        int vertex;
        int wage;
    };
    struct Datasets{
        int root, power;
    };

    Neighbour ** list_of_neighbours;
    Neighbour *p;

    Datasets *datasets;
    int ** adjency_matrix;
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
    //


    Edge root(Edge queue[]);
    void add_to_the_queue( Edge edge, Edge queue[]);
    void delete_first_from_queue(Edge queue[]);
    void kruskal_list();
    void kruskal_matrix();
    void create_dataset(int v);
    int find_dataset(int v);
    void connect_datasets(Edge edge);
    void delete_first_from_queue_Kruskal(Edge queue[]);
    void measure_time();
};