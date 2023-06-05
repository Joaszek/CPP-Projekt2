//
// Created by Joachim on 03.06.2023.
//

#ifndef DIJKSTRA_CLION_PATH_H
#define DIJKSTRA_CLION_PATH_H


#include <iostream>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <fstream>
#include <chrono>

class Path{
public:
    struct Neighbour{
        Neighbour* next;
        int vertex;
        int wage;
    };

    int number_of_vertexes;
    int number_of_edges;
    int density;
    int beginning_vertex;
    long long *cost_to_reach;
    int *previous;
    const int MAX_INT = 2147483647;

    Neighbour** list_of_the_neighbours;
    Neighbour* p;
    int **adjency_matrix;
    int wage;

    void menu();
    void generate_graph();
    void print_neighbours_list_list();
    void print_neighbours_list_matrix();
    void create_graph_from_file();
    void dijkstra_list();
    void dijkstra_matrix();
    void print_paths();
    void measure_time();
};

#endif //DIJKSTRA_CLION_PATH_H
