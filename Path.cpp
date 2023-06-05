//
// Created by Joachim on 03.06.2023.
//

#include "Path.h"

using namespace std;

void Path::menu()
{

    int option = -1;

    while (option != 0)
    {
        cout << "\nEnter option" << endl;
        cout << "1. Load a graph from a file" << endl;
        cout << "2. Generate a random edges_weight with a given density" << endl;
        cout << "3. Find the shortest paths using Dijkstra's algorithm from the list" << endl;
        cout << "4. Find the shortest paths using Dijkstra's algorithm from the matrix" << endl;
        cout << "5. Print graph" << endl;
        cout << "6. Exit" << endl;

        cin >> option;

        switch (option) // wybór opcji oraz wywolanie odpowiedniego menu
        {
        case 1:
            create_graph_from_file();
            break;
        case 2:
            list_of_the_neighbours = NULL;
            number_of_vertexes = 0;
            number_of_edges = 0;
            number_of_edges = 0;
            cout << "Enter the number of vertexes in the edges_weight you want to generate: " << endl;
            cin >> number_of_vertexes;
            cout << "Enter the density of the edges_weight you want to generate in percent: " << endl;
            cin >> density;
            generate_graph();
            break;
        case 3:
            dijkstra_list();
            break;
        case 4:
            dijkstra_matrix();
            break;
        case 5:
            print_neighbours_list_list();
            print_neighbours_list_matrix();
            break;
        case 6:
            return;
        default:
            cout << "Enter correct option" << endl;
            Sleep(2000);
            break;
        }
        print_neighbours_list_list();
        print_neighbours_list_matrix();
    }
}

void Path::print_neighbours_list_matrix()
{
    cout << "\n\n   ";
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << setw(6) << i;
    }
    cout << "\n";
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << setw(6) << i;
        for (int j = 0; j < number_of_vertexes; j++)
            cout << setw(6) << adjency_matrix[i][j];
        cout << "\n";
    }
}

void Path::print_neighbours_list_list()
{
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << "\n"
             << i << " = ";
        p = list_of_the_neighbours[i];
        while (p)
        {
            cout << setw(3) << p->vertex << ":" << p->wage;
            p = p->next;
        }
    }
}

void Path::generate_graph()
{

    srand(time(NULL));

    number_of_edges = (number_of_vertexes * density * (number_of_vertexes - 1)) / 100;

    while (number_of_edges < number_of_vertexes - 1)
    {
        cout << "Enter bigger density: " << endl;
        cin >> density;
        number_of_edges = (number_of_vertexes * density) / 100;
    }

    // tworzymy macierz sasiedztwa
    adjency_matrix = new int *[number_of_vertexes];
    for (int i = 0; i < number_of_vertexes; i++)
    {
        adjency_matrix[i] = new int[number_of_vertexes];
    }

    // ustawiamy kazda krawedz
    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (int j = 0; j < number_of_vertexes; j++)
        {
            adjency_matrix[i][j] = 0;
        }
    }

    // pomocnicze tablice do przechowywania wierzcholkow
    int *inside_graph = new int[number_of_vertexes];
    int *outside_graph = new int[number_of_vertexes - 1];

    // ustawiamy pierwszy wierzcholek w grafie
    inside_graph[0] = 0;

    // ustawiamy wierzcholki spoza grafu
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        outside_graph[i] = i + 1;
    }

    // tworzymy liste sasiedztwa
    list_of_the_neighbours = new Neighbour *[number_of_vertexes];
    for (int i = 0; i < number_of_vertexes; i++)
    {
        list_of_the_neighbours[i] = NULL;
    }

    // pomocnicze zmienne do indeksowania tablic z ktorych bedziemy brali wierzcholki
    int index_inside;
    int index_outside;

    // pomocnicze zmienne do indeksowania wierzcholkow
    int vertex_1;
    int vertex_2;

    // laczymy wszystkie wierzcholki tak aby powstal graf
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {

        // losujemy indeksy wierzcholkow
        index_inside = rand() % (i + 1);
        index_outside = rand() % (number_of_vertexes - i - 1);

        // wybieramy wierzcholki do polaczenia
        vertex_1 = inside_graph[index_inside];
        vertex_2 = outside_graph[index_outside];

        // losujemy wage krawedzi
        wage = rand() % 10 + 1;

        // ustawiamy wierzcholki w tablicach
        outside_graph[index_outside] = 0;
        inside_graph[i + 1] = vertex_2;

        // sortujemy tablice wierzcholkow spoza grafu, zeby nie wybrane wierzcholki byly na przodzie
        sort(outside_graph, outside_graph + number_of_vertexes - i - 1, greater<int>());

        // ustawiamy macierz sasiedztwa
        adjency_matrix[vertex_1][vertex_2] = wage;

        // ustawiamy liste sasiedztwa
        p = new Neighbour;
        p->vertex = vertex_2;
        p->next = list_of_the_neighbours[vertex_1];
        p->wage = wage;
        list_of_the_neighbours[vertex_1] = p;
    }

    for (int i = number_of_vertexes - 1; i < number_of_edges; i++)
    {
        // losujemy wierzcholki
        vertex_1 = rand() % number_of_vertexes;
        vertex_2 = rand() % number_of_vertexes;

        // jezeli to te same wierzcholki lub maja juz krawedz to losujemy dalej
        while (vertex_1 == vertex_2 || adjency_matrix[vertex_1][vertex_2] != 0)
        {
            vertex_1 = rand() % number_of_vertexes;
            vertex_2 = rand() % number_of_vertexes;
        }
        // losujemy wage
        wage = rand() % 10 + 1;

        // ustawiamy macierz sasiedztwa
        adjency_matrix[vertex_1][vertex_2] = wage;

        // ustawiamy liste sasiedztwa
        p = new Neighbour;
        p->vertex = vertex_2;
        p->next = list_of_the_neighbours[vertex_1];
        p->wage = wage;
        list_of_the_neighbours[vertex_1] = p;
    }
}

void Path::create_graph_from_file()
{

    // pobieramy nazwe pliku
    string filename;
    cout << "Enter filename" << endl;
    cin >> filename;
    fstream file;
    file.open(filename, ios::in);

    // wpisujemy dane z pliku do zmiennych
    file >> number_of_edges;
    file >> number_of_vertexes;
    file >> beginning_vertex;

    // deklarujemy liste sasiedztwa
    list_of_the_neighbours = new Neighbour *[number_of_vertexes];

    // tworzymy macierz sasiedztwa
    adjency_matrix = new int *[number_of_vertexes];

    for (int i = 0; i < number_of_vertexes; i++)
    {
        adjency_matrix[i] = new int[number_of_vertexes];
    }

    // ustawiamy liste sasiadow na NULL
    for (int i = 0; i < number_of_vertexes; i++)
    {
        list_of_the_neighbours[i] = NULL;
    }

    // zerujemy krawedzie
    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (int j = 0; j < number_of_vertexes; j++)
        {
            adjency_matrix[i][j] = 0;
        }
    }

    // tworzymy sasiadow
    int vertex_1;
    int vertex_2;
    for (int i = 0; i < number_of_edges; i++)
    {
        file >> vertex_1;
        file >> vertex_2;
        file >> wage;
        p = new Neighbour;
        p->next = list_of_the_neighbours[vertex_1];
        p->vertex = vertex_2;
        p->wage = wage;
        list_of_the_neighbours[vertex_1] = p;
        adjency_matrix[vertex_1][vertex_2] = wage;
    }
}

void Path::dijkstra_list()
{
    // zmienne pomocnicze
    int u, j;

    // tablice pomocnicze do trzymania kosztow dojscia do konkretnych wierzcholkow,
    // poprzednich wierzcholkow na najkrotszej sciezce
    // i sprawdzania czy wierzcholek zostal odwiedzony
    cost_to_reach = new long long[number_of_vertexes];
    previous = new int[number_of_vertexes];
    bool *visited = new bool[number_of_vertexes];

    // ustawiamy tablice na poczatkowe wartosci
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cost_to_reach[i] = MAX_INT;
        previous[i] = -1;
        visited[i] = false;
    }

    // ustawiamy koszt dojscia do wierzcholka poczatkowego na 0
    cost_to_reach[beginning_vertex] = 0;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        // szukamy pierwszego nie odwiedzonego indeksu
        for (j = 0; visited[j]; j++)
            ;

        // szukamy wierzcholka o najmniejszym koszcie dojscia
        for (u = j++; j < number_of_vertexes; j++)
        {
            // jezeli wierzcholek nie byl odwiedzony i ma mniejszy koszt to ustawiamy go jako u
            if (!visited[j] && (cost_to_reach[j] < cost_to_reach[u]))
            {
                u = j;
            }
        }

        // ustawiamy jako odwiedzony
        visited[u] = true;

        // dla kazdego sasiada wierzcholka u
        for (p = list_of_the_neighbours[u]; p; p = p->next)
        {

            // jezeli wierzcholek nie byl odwiedzony i koszt dojscia do niego jest wiekszy od kosztu dojscia do u + wage
            // to ustawiamy koszt dojscia do niego na koszt dojscia do u + wage
            // i poprzedni wierzcholek na u
            if (!visited[p->vertex] && (cost_to_reach[p->vertex] > cost_to_reach[u] + p->wage))
            {
                // ustawiamy koszt dojscia do wierzcholka
                cost_to_reach[p->vertex] = cost_to_reach[u] + p->wage;
                // ustawiamy poprzedni wierzcholek
                previous[p->vertex] = u;
            }
        }
    }

    print_paths();
}

void Path::dijkstra_matrix()
{
    // tworzymy pomocnicze zmienne
    int u, j;

    // tablice pomocnicze do trzymania kosztow dojscia do konkretnych wierzcholkow,
    // poprzednich wierzcholkow na najkrotszej sciezce
    // i sprawdzania czy wierzcholek zostal odwiedzony
    cost_to_reach = new long long[number_of_vertexes];
    previous = new int[number_of_vertexes];
    bool *visited = new bool[number_of_vertexes];

    // ustawiamy początkowe wartosci
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cost_to_reach[i] = MAX_INT;
        previous[i] = -1;
        visited[i] = false;
    }

    // ustawiamy wierzchołek początkowy na 0
    cost_to_reach[beginning_vertex] = 0;

    // dla każdego wierzchołka
    for (int i = 0; i < number_of_vertexes; i++)
    {
        // szukamy pierwszego nieodwiedzonego wierzchołka
        for (j = 0; visited[j]; j++)
            ;

        // szukamy wierzchołka o najmniejszym koszcie dojscia
        for (u = j++; j < number_of_vertexes; j++)
        {
            // jeżeli wierzchołek nie był odwiedzony i ma mniejszy koszt to ustawiamy go jako u
            if (!visited[j] && (cost_to_reach[j] < cost_to_reach[u]))
            {
                u = j;
            }
        }

        // ustawiamy jako odwiedzony
        visited[u] = true;

        // dla każdego sąsiada wierzchołka u
        for (int v = 0; v < number_of_vertexes; v++)
        {
            // jeżeli wierzchołek nie był odwiedzony i koszt dojscia do niego jest wiekszy od kosztu dojscia do u + waga krawedzi
            if (adjency_matrix[u][v] != 0 && !visited[v] && (cost_to_reach[v] > cost_to_reach[u] + adjency_matrix[u][v]))
            {
                // ustawiamy koszt dojscia do niego na koszt dojscia do u + waga
                cost_to_reach[v] = cost_to_reach[u] + adjency_matrix[u][v];
                // i poprzedni wierzcholek na u
                previous[v] = u;
            }
        }
    }

    print_paths();

    delete cost_to_reach;
    delete previous;
    delete visited;
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
        for (int j = i; j > -1; j = previous[j])
        {
            S[stack++] = j;
        }

        while (stack)
        {
            cout << S[--stack] << " ";
        }
        cout << "$" << cost_to_reach[i] << "\n";
    }
}

void Path::measure_time()
{
    int data[24][2] = {{15, 20}, {15, 60}, {15, 99}, {20, 20}, {20, 60}, {20, 99}, {25, 20}, {25, 60}, {25, 99}, {50, 20}, {50, 60}, {50, 99}, {75, 20}, {75, 60}, {75, 99}, {100, 20}, {100, 60}, {100, 99}, {150, 20}, {150, 60}, {150, 99}, {200, 20}, {200, 60}, {200, 99}};

    for (int i = 0; i < 22; i++)
    {
        density = data[i][1];
        number_of_vertexes = data[i][0];

        string filename;
        filename = "data_list_" + to_string(number_of_vertexes) + "_" + to_string(density) + ".txt";
        fstream file;
        file.open(filename, ios::out);

        srand(time(NULL));
        
        // pomiar czasu operacji
        for (int i = 0; i < 50; i++) 
        {
            generate_graph();
            beginning_vertex = rand() % number_of_vertexes;
            auto begin = std::chrono::steady_clock::now();
            dijkstra_list();
            auto end = std::chrono::steady_clock::now();
            file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        file.close();

        string filename2 = "data_matrix_" + to_string(number_of_vertexes) + "_" + to_string(density) + ".txt";

        // pomiar czasu operacji
        file.open(filename2, ios::out);
        for (int i = 0; i < 50; i++)
        {
            generate_graph();
            beginning_vertex = rand() % number_of_vertexes;
            auto begin = std::chrono::steady_clock::now();
            dijkstra_matrix();
            auto end = std::chrono::steady_clock::now();
            file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        file.close();
    }
}