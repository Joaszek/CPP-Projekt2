#include "Path.h"

using namespace std;

void Path::path_menu()
{

    int option = -1;

    while (option != 0)
    {
        cout << "\nEnter option" << endl;
        cout << "1. Load a graph from a file" << endl;
        cout << "2. Generate a random graph with a given density" << endl;
        cout << "3. Find the shortest paths using Dijkstra's algorithm from the list" << endl;
        cout << "4. Find the shortest paths using the Dijkstra algorithm from the matrix" << endl;
        cout << "5. Find the shortest paths using the Ford-Bellman algorithm from the list" << endl;
        cout << "6. Find the shortest paths using the Ford-Bellman algorithm from the matrix" << endl;
        cout << "7. Print graph" << endl;
        cout << "0. Exit" << endl;

        cin >> option;

        switch (option) // wybór opcji oraz wywo³anie odpowiedniego menu
        {
        case 0:
            break;
        case 1:
            graph = NULL;
            neighbours = NULL;
            number_of_vertexes = 0;
            number_of_edges = 0;
            create_graph_from_file();
            print_neighbours_list();
            print_matrix();
            break;
        case 2:
            graph = NULL;
            neighbours = NULL;
            number_of_vertexes = 0;
            number_of_edges = 0;
            number_of_edges = 0;
            cout << "Enter the number of vertices in the graph you want to generate: " << endl;
            cin >> number_of_vertexes;
            cout << "Enter the density of the graph you want to generate in percent: " << endl;
            cin >> density;
            generate_graph();
            print_neighbours_list();
            print_matrix();
            break;
        case 3:
            dijkstra_list();
            print_neighbours_list();
            print_matrix();
            break;
        case 4:
            dijkstra_matrix();
            print_neighbours_list();
            print_matrix();
            break;
        case 5:
            ford_list();
            print_neighbours_list();
            print_matrix();
            break;
        case 6:
            ford_matrix();
            print_neighbours_list();
            print_matrix();
            break;
        case 7:
            print_neighbours_list();
            print_matrix();
            break;
        default:
                cout << "Podaj wlasciwa opcje." << endl;
                Sleep(2000);
                break;
        }
    }
}
void Path::create_graph_from_file()
{

    string filename;
    int v1, v2, wage;

    cout << "Enter file name: "<<endl;
    cin >> filename;
    ifstream file;
    file.open(filename.c_str(), ios::in);
    file >> number_of_edges >> number_of_vertexes >> beginning_vertex;

    neighbours = new List_of_neighbours *[number_of_edges];

    graph = new int *[number_of_vertexes];
    for (int i = 0; i < number_of_vertexes; i++){
        graph[i] = new int[number_of_vertexes];
    }
        
    for (int i = 0; i < number_of_vertexes; i++){
        neighbours[i] = NULL;
    }
        
    for (int i = 0; i < number_of_vertexes; i++){
        for (int j = 0; j < number_of_vertexes; j++){
            graph[i][j] = 0;
        }
    }
        
                

    for (int i = 0; i < number_of_edges; i++){
        file >> v1 >> v2 >> wage;
        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;

        graph[v1][v2] = wage;
    }
}
void Path::print_neighbours_list()
{
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << "\n" << i << " = ";
        p = neighbours[i];
        while (p)
        {
                cout << setw(3) << p->neighbour << ":" << p->wage;
                p = p->next;
        }
    }
}
void Path::print_matrix()
{
    cout << "\n\n   ";
    for (int i = 0; i < number_of_vertexes; i++){
        cout << setw(6) << i;
    }
    cout << "\n";
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << setw(6) << i;
        for (int j = 0; j < number_of_vertexes; j++)
                cout << setw(6) << graph[i][j];
        cout << "\n";
    }
}
void Path::generate_graph()
{

    srand(time(NULL));
    neighbours = new List_of_neighbours *[number_of_vertexes * (number_of_vertexes - 1) / 2];
    int v1, v2, wage;
    int index_inside_graph, index_outside_graph;

    graph = new int *[number_of_vertexes];
    for (int i = 0; i < number_of_vertexes; i++){
        graph[i] = new int[number_of_vertexes];
    }

    for (int i = 0; i < number_of_vertexes; i++){
        neighbours[i] = NULL;
    }
        
    for (int i = 0; i < number_of_vertexes; i++){
        for (int j = 0; j < number_of_vertexes; j++){
            graph[i][j] = 0;
        }
    }
        
                
    int *inside_graph =  new int [number_of_vertexes + 1];
    int *outside_graph =  new int [number_of_vertexes];

    inside_graph[0] = 0;
    for (int i = 0; i < number_of_vertexes - 1; i++){
        outside_graph[i] = i + 1;
    }
        
    index_outside_graph = rand() % (number_of_vertexes - 1);
    v2 = 0;
    v1 = outside_graph[index_outside_graph];
    wage = rand() % 100 + 1;
    p = new List_of_neighbours;
    p->neighbour = v2;
    p->next = neighbours[v1];
    p->wage = wage;
    neighbours[v1] = p;
    graph[v1][v2] = wage;

    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        index_inside_graph = rand() % (i + 1);
        index_outside_graph = rand() % (number_of_vertexes - i - 1);
        v1 = inside_graph[index_inside_graph];
        v2 = outside_graph[index_outside_graph];
        wage = rand() % 100 + 1;
        outside_graph[index_outside_graph] = 0;
        inside_graph[i + 1] = v2;
        sort(outside_graph, outside_graph + number_of_vertexes - i - 1, greater<int>());

        graph[v1][v2] = wage;

        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;
    }

    number_of_edges = density * number_of_vertexes * (number_of_vertexes - 1) / 2 / 100;

    for (int i = number_of_vertexes - 1; i < number_of_edges; i++)
    {
        v1 = rand() % number_of_vertexes;
        v2 = rand() % number_of_vertexes;

        while (v1 == v2 || graph[v1][v2] != 0)
        {
                v1 = rand() % number_of_vertexes;
                v2 = rand() % number_of_vertexes;
        }
        wage = rand() % 1000000 + 1;

        graph[v1][v2] = wage;

        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;
    }
}
void Path::dijkstra_list()
{
    int u, j;
    bool *QS;

    cost_to_reach = new long long[number_of_vertexes];
    previous = new int[number_of_vertexes];
    QS = new bool[number_of_vertexes];

    for (int i = 0; i < number_of_vertexes; i++)
    {
        cost_to_reach[i] = inf;
        previous[i] = -1;
        QS[i] = false;
    }

    cost_to_reach[beginning_vertex] = 0;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (j = 0; QS[j]; j++);

        for (u = j++; j < number_of_vertexes; j++)
        {
                if (!QS[j] && (cost_to_reach[j] < cost_to_reach[u])){
                    u = j;
                }    
        }
                
        QS[u] = true;

        for (p = neighbours[u]; p; p = p->next){
            if (!QS[p->neighbour] && (cost_to_reach[p->neighbour] > cost_to_reach[u] + p->wage))
                {
                    cost_to_reach[p->neighbour] = cost_to_reach[u] + p->wage;
                    previous[p->neighbour] = u;
                }
        }
                
    }

    print_paths();
}
void Path::dijkstra_matrix()
{
    int u, j;
    bool *QS;

    cost_to_reach = new long long[number_of_vertexes];
    previous = new int[number_of_vertexes];
    QS = new bool[number_of_vertexes];

    for (int i = 0; i < number_of_vertexes; i++)
    {
        cost_to_reach[i] = inf;
        previous[i] = -1;
        QS[i] = false;
    }

    cost_to_reach[beginning_vertex] = 0;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (j = 0; QS[j]; j++)
                ;
        for (u = j++; j < number_of_vertexes; j++){
            if (!QS[j] && (cost_to_reach[j] < cost_to_reach[u])){
                u = j;
            }        
        }
                
        QS[u] = true;

        for (int v = 0; v < number_of_vertexes; v++){
            if (graph[u][v] != 0 && !QS[v] && (cost_to_reach[v] > cost_to_reach[u] + graph[u][v]))
            {
                    cost_to_reach[v] = cost_to_reach[u] + graph[u][v];
                    previous[v] = u;
            }
        }
                
    }

    print_paths();

    delete cost_to_reach;
    delete previous;
    delete QS;
}
void Path::ford_list()
{

    cost_to_reach = new long long[number_of_vertexes];
    previous = new int[number_of_vertexes];
    bool negative_cycle = false;
    bool test;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        cost_to_reach[i] = inf;
        previous[i] = -1;
    }

    cost_to_reach[beginning_vertex] = 0;

    for (int i = 1; i < number_of_vertexes; i++)
    {
        test = true;

        for (int v = 0; v < number_of_vertexes; v++){
            for (p = neighbours[v]; p; p = p->next){
                if (cost_to_reach[p->neighbour] > cost_to_reach[v] + p->wage)
                    {
                        test = false;
                        cost_to_reach[p->neighbour] = cost_to_reach[v] + p->wage;
                        previous[p->neighbour] = v;
                    }
            }    
        }
                
        if (test)
        {
                cout << "brak zmian";
                break;
        }
    }

    for (int v = 0; v < number_of_vertexes; v++){
        for (p = neighbours[v]; p; p = p->next){
            if (cost_to_reach[p->neighbour] > cost_to_reach[v] + p->wage){
                negative_cycle = true;
            }
                    
        }
                
    }
        

    if (negative_cycle){
        cout << "\nW grafie wystepuje ujemny cykl" << endl;
    }
        
    else{
        print_paths();
    }
        
}
void Path::ford_matrix()
{

    cost_to_reach = new long long[number_of_vertexes];
    previous = new int[number_of_vertexes];
    bool negative_cycle = false;
    bool test;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        cost_to_reach[i] = inf;
        previous[i] = -1;
    }

    cost_to_reach[beginning_vertex] = 0;

    for (int i = 1; i < number_of_vertexes; i++)
    {
        test = true;

        for (int u = 0; u < number_of_vertexes; u++){
            for (int v = 0; v < number_of_vertexes; v++){
                if (graph[u][v] != 0 && cost_to_reach[v] > cost_to_reach[u] + graph[u][v])
                    {
                        test = false;
                        cost_to_reach[v] = cost_to_reach[u] + graph[u][v];
                        previous[v] = u;
                    }
            }
                    
        }
                
        if (test)
        {
                cout << "no changes";
                break;
        }
    }

    for (int u = 0; u < number_of_vertexes; u++){
        for (int v = 0; v < number_of_vertexes; v++){
            if (graph[u][v] != 0 && cost_to_reach[v] > cost_to_reach[u] + graph[u][v]){
                negative_cycle = true;
            }
                    
        }
                
    }
        

    if (negative_cycle){
        cout << "\n" << endl;
    }
    else{
        print_paths();
    } 
}
void Path::print_paths()
{
    int *S, stack;

    S = new int[number_of_vertexes];
    stack = 0;

    cout << "\nShortest way from vertex " << beginning_vertex << endl;
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << i << ": ";
        for (int j = i; j > -1; j = previous[j]){
            S[stack++] = j;
        }

        while (stack){
            cout << S[--stack] << " ";
        }
        cout << "$" << cost_to_reach[i] << "\n";
    }
}
void Path::measure_time()
{

    int size[21][2] = {{10, 20}, {10, 60}, {10, 99}, {25, 20}, {25, 60}, {25, 99}, {50, 20}, {50, 60}, {50, 99}, {75, 20}, {75, 60}, {75, 99}, {100, 20}, {100, 60}, {100, 99}, {150, 20}, {150, 60}, {150, 99}, {200, 20}, {200, 60}, {200, 99}};

    for (int i = 0; i < 21; i++)
    {

        number_of_vertexes = size[i][0];
        density = size[i][1];

        string name;
        string txt = ".txt";
        string floor = "_";
        string number_of_vertexes_string, density_string;
        number_of_vertexes_string = to_string(number_of_vertexes);
        density_string = to_string(density);
        name = "Path_DijkstraList_";
        name = name + number_of_vertexes_string + floor + density_string + txt; // stworzenie nazwy pliku

        ofstream fout;
        fout.open(name);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
                generate_graph();
                beginning_vertex = rand() % number_of_vertexes;
                auto begin = chrono::steady_clock::now();
                dijkstra_list();
                auto end = chrono::steady_clock::now();
                fout << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        name = "Path_DijkstraMatrix_";
        name = name + number_of_vertexes_string + floor + density_string + txt;
        fout.open(name);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
                generate_graph();
                beginning_vertex = rand() % number_of_vertexes;
                auto begin = std::chrono::steady_clock::now();
                dijkstra_matrix();
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        name = "Path_FordList_";
        name = name + number_of_vertexes_string + floor + density_string + txt;
        fout.open(name);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
                generate_graph();
                beginning_vertex = rand() % number_of_vertexes;
                auto begin = std::chrono::steady_clock::now();
                ford_list();
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        name = "Path_FordMatrix_";
        name = name + number_of_vertexes_string + floor + density_string + txt;
        fout.open(name);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
                generate_graph();
                beginning_vertex = rand() % number_of_vertexes;
                auto begin = std::chrono::steady_clock::now();
                ford_matrix();
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();
    }
}
