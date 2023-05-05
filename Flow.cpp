#include "Flow.h"

using namespace std;

void Flow::flow_menu()
{

    int option = -1;

    while (option != 0)
    {
        cout << "\nEnter option" << endl;
        cout << "1. Load grph from file" << endl;
        cout << "2. Generate graph with density" << endl;
        cout << "3. Determine the maximum flow using the Ford-Fulkerson algorithm from the list" << endl;
        cout << "4. Determine the maximum flow using the Ford-Fulkerson algorithm from the matrix" << endl;
        cout << "5. Print graph" << endl;
        cout << "6. Exit" << endl;

        cin >> option;

        switch (option) // wybór opcji oraz wywo³anie odpowiedniego menu
        {
        case 1:
            graph = NULL;
            neighbours = NULL;
            number_of_nodes = 0;
            number_of_edges = 0;
            create_graph_from_file();
            print_neighbours_list();
            print_matrix();
            break;
        case 2:
            graph = NULL;
            neighbours = NULL;
            number_of_nodes = 0;
            number_of_edges = 0;
            number_of_edges = 0;
            cout << "Podaj ilosc wierzcholkow w grafie, ktory chcesz wygenerowac: " << endl;
            cin >> number_of_nodes;
            cout << "Podaj w procentach density grafu, ktory chcesz wygenerowac: " << endl;
            cin >> density;
            generate_graph();
            print_neighbours_list();
            print_matrix();
            break;
        case 3:
            Fulkerson_list();
            print_neighbours_list();
            print_matrix();
            break;
        case 4:
            Fulkerson_matrix();
            print_neighbours_list();
            print_matrix();
            break;
        case 5:
            print_neighbours_list();
            print_matrix();
            break;
        case 6:
            return;
        default:
            cout << "Enter correct option" << endl;
            Sleep(2000);
            break;
        }
    }
}
void Flow::create_graph_from_file()
{

    string filename;
    int v1, v2, wage;

    cout << "Enter filename: " << endl;
    cin >> filename;
    fstream file; // wczytanie pliku oraz sizeu kopca z niego
    file.open(filename.c_str(), ios::in);
    file >> number_of_edges >> number_of_nodes >> source >> destination;

    neighbours = new List_of_neighbours *[number_of_edges];

    graph = new int *[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++)
    {
        graph[i] = new int[number_of_nodes];
    }

    for (int i = 0; i < number_of_nodes; i++)
    {
        neighbours[i] = NULL;
    }
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int j = 0; j < number_of_nodes; j++)
        {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < number_of_edges; i++)
    {
        file >> v1 >> v2 >> wage;
        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;

        graph[v1][v2] = wage;
    }
}
void Flow::print_neighbours_list()
{
    for (int i = 0; i < number_of_nodes; i++)
    {
        cout << "\n"
             << i << " = ";
        p = neighbours[i];
        while (p)
        {
            cout << setw(3) << p->neighbour << ":" << p->wage;
            p = p->next;
        }
    }
}
void Flow::print_matrix()
{
    cout << "\n\n   ";
    for (int i = 0; i < number_of_nodes; i++)
        cout << setw(6) << i;
    cout << "\n";
    for (int i = 0; i < number_of_nodes; i++)
    {
        cout << setw(6) << i;
        for (int j = 0; j < number_of_nodes; j++)
            cout << setw(6) << graph[i][j];
        cout << "\n";
    }
}
void Flow::generate_graph()
{

    srand(time(NULL));
    neighbours = new List_of_neighbours *[number_of_nodes * (number_of_nodes - 1) / 2];
    int v1, v2, wage;
    int index_z_grafu, index_out_of_bounds;

    graph = new int *[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++)
    {
        graph[i] = new int[number_of_nodes];
    }

    for (int i = 0; i < number_of_nodes; i++)
    {
        neighbours[i] = NULL;
    }
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int j = 0; j < number_of_nodes; j++)
        {
            graph[i][j] = 0;
        }
    }

    // bylo
    /*
        int in_graph[number_of_nodes + 1];
        int out_of_graph[number_of_nodes];
        */

    int *in_graph = new int[number_of_nodes + 1];
    int *out_of_graph = new int[number_of_nodes];

    in_graph[0] = 0;

    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        out_of_graph[i] = i + 1;
    }

    index_out_of_bounds = rand() % (number_of_nodes - 1);
    v2 = 0;
    v1 = out_of_graph[index_out_of_bounds];
    wage = rand() % 100 + 1;
    p = new List_of_neighbours;
    p->neighbour = v2;
    p->next = neighbours[v1];
    p->wage = wage;
    neighbours[v1] = p;
    graph[v1][v2] = wage;

    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        index_z_grafu = rand() % (i + 1);
        index_out_of_bounds = rand() % (number_of_nodes - i - 1);
        v1 = in_graph[index_z_grafu];
        v2 = out_of_graph[index_out_of_bounds];
        wage = rand() % 100 + 1;
        out_of_graph[index_out_of_bounds] = 0;
        in_graph[i + 1] = v2;
        sort(out_of_graph, out_of_graph + number_of_nodes - i - 1, greater<int>());

        graph[v1][v2] = wage;

        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;
    }

    number_of_edges = density * number_of_nodes * (number_of_nodes - 1) / 2 / 100;

    for (int i = number_of_nodes - 1; i < number_of_edges; i++)
    {
        v1 = rand() % number_of_nodes;
        v2 = rand() % number_of_nodes;

        while (v1 == v2 || graph[v1][v2] != 0)
        {
            v1 = rand() % number_of_nodes;
            v2 = rand() % number_of_nodes;
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
void Flow::Fulkerson_list()
{
    predecessor = new int[number_of_nodes];

    int u, v;

    r_graf = new int *[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++)
        r_graf[i] = new int[number_of_nodes];

    for (u = 0; u < number_of_nodes; u++)
        for (v = 0; v < number_of_nodes; v++)
            r_graf[u][v] = 0;

    for (u = 0; u < number_of_nodes; u++)
        for (p = neighbours[u]; p; p = p->next)
            r_graf[u][p->neighbour] = p->wage;

    int max_flow = 0;

    while (BFS())
    {
        int flow = inf;
        for (v = destination; v != source; v = predecessor[v])
        {
            u = predecessor[v];
            flow = min(flow, r_graf[u][v]);
        }

        for (v = destination; v != source; v = predecessor[v])
        {
            u = predecessor[v];
            r_graf[u][v] -= flow;
            r_graf[v][u] += flow;
        }
        max_flow += flow;
    }
    cout << "Max flow: " << max_flow << "\n";
}
void Flow::Fulkerson_matrix()
{
    predecessor = new int[number_of_nodes];

    int u, v;

    r_graf = new int *[number_of_nodes];

    for (int i = 0; i < number_of_nodes; i++)
    {
        r_graf[i] = new int[number_of_nodes];
    }

    for (u = 0; u < number_of_nodes; u++)
        for (v = 0; v < number_of_nodes; v++)
            r_graf[u][v] = graph[u][v];

    int max_flow = 0;

    while (BFS())
    {
        int flow = inf;
        for (v = destination; v != source; v = predecessor[v])
        {
            u = predecessor[v];
            flow = min(flow, r_graf[u][v]);
        }

        for (v = destination; v != source; v = predecessor[v])
        {
            u = predecessor[v];
            r_graf[u][v] -= flow;
            r_graf[v][u] += flow;
        }
        max_flow += flow;
    }
    cout << "Max flow: " << max_flow << "\n";
}
bool Flow::BFS()
{

    bool *visited = new bool[number_of_nodes];

    for (int i = 0; i < number_of_nodes; i++)
    {
        visited[i] = false;
    }

    beginning = NULL;
    end = NULL;
    beginning = (Queue *)malloc(sizeof(Queue));
    end = (Queue *)malloc(sizeof(Queue));
    beginning->v = source;
    beginning->next = end;
    beginning->previous = NULL;
    end->v = 0;
    end->next = nullptr;
    end->previous = beginning;
    list_length = 1;

    visited[source] = true;
    predecessor[source] = -1;
    while (list_length > 0)
    {
        int u = beginning->v;
        delete_from_queue();
        for (int v = 0; v < number_of_nodes; v++)
            if (visited[v] == false && r_graf[u][v] > 0)
            {
                add_to_queue(v);
                predecessor[v] = u;
                visited[v] = true;
            }
    }
    return visited[destination];
}
void Flow::add_to_queue(int v)
{

    Queue *new_queue;
    new_queue = (Queue *)malloc(sizeof(Queue));
    if (list_length == 0)
    {
        beginning->v = v;
    }
    else
    {
        new_queue->v = v;
        new_queue->next = end;
        end->previous = new_queue;

        if (end->previous = beginning)
        {
            beginning->next = new_queue;
            new_queue->previous = beginning;
        }
        else
        {
            new_queue->previous = end->previous->previous;
            end->previous->next = new_queue;
        }
    }
    list_length++;
}
void Flow::delete_from_queue()
{
    Queue *queue_to_delete;
    queue_to_delete = (Queue *)malloc(sizeof(Queue));
    queue_to_delete = beginning->next;
    if (queue_to_delete != end)
    {
        beginning->next = queue_to_delete->next;
        beginning->v = queue_to_delete->v;
        queue_to_delete->next->previous = beginning;
        free(queue_to_delete);
    }
    list_length--;
}
void Flow::measure_time()
{

    int size_to_test[21][2] = {{10, 20}, {10, 60}, {10, 99}, {25, 20}, {25, 60}, {25, 99}, {50, 20}, {50, 60}, {50, 99}, {75, 20}, {75, 60}, {75, 99}, {100, 20}, {100, 60}, {100, 99}, {150, 20}, {150, 60}, {150, 99}, {200, 20}, {200, 60}, {200, 99}};

    for (int i = 0; i < 21; i++)
    {

        number_of_nodes = size_to_test[i][0];
        density = size_to_test[i][1];

        string name = "Flow_FulkersonList_";
        string txt = ".txt";
        string floor = "_";
        string size, density_string;
        size = to_string(number_of_nodes);
        density_string = to_string(density);
        name = name + size + floor + density_string + txt; // stworzenie nazwy pliku

        ofstream fout;
        fout.open(name);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
            generate_graph();
            source = rand() % number_of_nodes;
            destination = rand() % number_of_nodes;
            auto begin = chrono::steady_clock::now();
            Fulkerson_list();
            auto end = chrono::steady_clock::now();
            fout << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        name = "Flow_FulkersonMatrix_";
        name = name + size + floor + density_string + txt;
        fout.open(name);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
            generate_graph();
            source = rand() % number_of_nodes;
            destination = rand() % number_of_nodes;
            auto begin = chrono::steady_clock::now();
            Fulkerson_matrix();
            auto end = chrono::steady_clock::now();
            fout << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();
    }
}
