#include<stdlib.h>

using namespace std;

class Flow{
public:
    struct Queue{
        int v;
        Queue *next;
        Queue *previous;
    };

    struct List_of_neighbours{
        List_of_neighbours *next;
        int neighbour;
        int wage;
    };

    List_of_neighbours ** neighbours;
    List_of_neighbours *p;

    int ** graph;
    int ** r_graf;
    int number_of_edges, number_of_nodes, source, destination;
    int wage;
    int density;
    int *predecessor;
    const int inf = 2147483647;
    int list_length;

    Queue *beginning, *end;

    void flow_menu();
    void create_graph_from_file();
    void generate_graph();

    void print_matrix();
    void print_neighbours_list();

    void Fulkerson_matrix();
    void Fulkerson_list();

    bool BFS();
    void add_to_queue(int v);
    void delete_from_queue();

    void measure_time();
};