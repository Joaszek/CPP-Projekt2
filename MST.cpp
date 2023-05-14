#include "MST.h"

using namespace std;

void MST::MST_menu()
{

    int option = -1;

    while (option != 0)
    {
        cout << "\nEnter option?" << endl;
        cout << "1. Load graph from file" << endl;
        cout << "2. Generate graph" << endl;
        cout << "3. Find the minimum right_sonanning tree using Prim's algorithm from the list" << endl;
        cout << "4. Find the minimum right_sonanning tree using Prim's algorithm from the matrix" << endl;
        cout << "5. Find the minimum right_sonanning tree using Krusral's algorithm from the list" << endl;
        cout << "6. Find the minimum right_sonanning tree using Krusral's algorithm from the matrix" << endl;
        cout << "7. Print graph" << endl;
        cout << "0. Exit" << endl;

        cin >> option;

        switch (option) // wybór opcji oraz wywo³anie odpowiedniego menu
        {
        case 0:
            return;
        case 1:
            graph = NULL;
            neighbours = NULL;
            number_of_vertexes = 0;
            number_of_edges = 0;
            create_graph_from_file();
            print_list_of_neighbours();
            print_matrix();
            break;
        case 2:
            graph = NULL;
            neighbours = NULL;
            number_of_vertexes = 0;
            number_of_edges = 0;
            cout << "Enter the number of vertices in the graph you want to generate: " << endl;
            cin >> number_of_vertexes;
            cout << "Enter the density(in percent) of the graph you want to generate: " << endl;
            cin >> density;
            generate_graph();
            print_list_of_neighbours();
            print_matrix();
            break;
        case 3:
            prim_list();
            print_list_of_neighbours();
            print_matrix();
            break;
        case 4:
            prim_matrix();
            print_list_of_neighbours();
            print_matrix();
            break;
        case 5:
            kruskal_list();
            print_list_of_neighbours();
            print_matrix();
            break;
        case 6:
            kruskal_matrix();
            print_list_of_neighbours();
            print_matrix();
            break;
        case 7:
            print_list_of_neighbours();
            print_matrix();
            break;
        default:
            cout << "Enter correct option" << endl;
            Sleep(2000);
            break;
        }
    }
}
void MST::create_graph_from_file()
{

    string filename;
    int v1, v2, wage;

    cout << "Enter the name of the file: " << endl;
    //pobieranie nazwy pliku
    cin >> filename;
    ifstream file;
    //otwieranie pliku
    file.open(filename.c_str(), ios::in);
    //wstawiamy numer krawedzi i wierzcholkow
    file >> number_of_edges >> number_of_vertexes;

    //tworzymy liste sasiadow
    neighbours = new List_of_neighbours *[number_of_edges];

    //tworzymy graf
    graph = new int *[number_of_vertexes];
    //dla kazdego wierzcholka ustawiamy tablice krawedzi 
    for (int i = 0; i < number_of_vertexes; i++)
    {
        graph[i] = new int[number_of_vertexes];
    }
    //ustawiamy każdą wartość na null
    for (int i = 0; i < number_of_vertexes; i++)
    {
        neighbours[i] = NULL;
    }
    //zerujemy każdą krawędź
    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (int j = 0; j < number_of_vertexes; j++){
            graph[i][j] = 0;
        }
    }

    //ustawiamy krawędźie
    for (int i = 0; i < number_of_edges; i++)
    {
        file >> v1 >> v2 >> wage;
        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;

        p = new List_of_neighbours;
        p->neighbour = v1;
        p->next = neighbours[v2];
        p->wage = wage;
        neighbours[v2] = p;

        graph[v1][v2] = wage;
        graph[v2][v1] = wage;
    }
}
void MST::generate_graph()
{
    srand(time(NULL));
    neighbours = new List_of_neighbours *[number_of_vertexes * (number_of_vertexes - 1) / 2];
    int v1, v2, wage;
    int index_from_graph, index_out_graph;

    //deklarujemy graf
    graph = new int *[number_of_vertexes];

    //ustawiamy liste
    for (int i = 0; i < number_of_vertexes; i++)
    {
        graph[i] = new int[number_of_vertexes];
    }
    //ustawiamy nulle
    for (int i = 0; i < number_of_vertexes; i++)
    {
        neighbours[i] = NULL;
    }

    //ustawiamy wartosc zero dla wszystkich krawedzi
    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (int j = 0; j < number_of_vertexes; j++){
            graph[i][j] = 0;
        }
            
    }
    //deklarujemy pomocnicze zmienne
    int *inside_graph = new int[number_of_vertexes + 1];
    int *outside_graph = new int[number_of_vertexes];

    inside_graph[0] = 0;
    //????
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        outside_graph[i] = i + 1;
    }

    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        index_from_graph = rand() % (i + 1);
        index_out_graph = rand() % (number_of_vertexes - i - 1);
        v1 = inside_graph[index_from_graph];
        v2 = outside_graph[index_out_graph];
        wage = rand() % 1000000 + 1;
        outside_graph[index_out_graph] = 0;
        inside_graph[i + 1] = v2;
        sort(outside_graph, outside_graph + number_of_vertexes - i - 1, greater<int>());

        graph[v1][v2] = wage;
        graph[v2][v1] = wage;

        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;

        p = new List_of_neighbours;
        p->neighbour = v1;
        p->next = neighbours[v2];
        p->wage = wage;
        neighbours[v2] = p;
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
        wage = rand() % 100 + 1;

        graph[v1][v2] = wage;
        graph[v2][v1] = wage;

        p = new List_of_neighbours;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->wage = wage;
        neighbours[v1] = p;

        p = new List_of_neighbours;
        p->neighbour = v1;
        p->next = neighbours[v2];
        p->wage = wage;
        neighbours[v2] = p;
    }
}
void MST::print_list_of_neighbours()
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
void MST::print_matrix()
{
    cout << "\n\n   ";
    for (int i = 0; i < number_of_vertexes; i++){
        cout << setw(6) << i;
    }
        
    cout << endl;
    for (int i = 0; i < number_of_vertexes; i++)
    {
        cout << setw(6) << i;
        for (int j = 0; j < number_of_vertexes; j++){
            cout << setw(6) << graph[i][j];
        }
        cout << endl;
    }
}
void MST::print_mst(Edge mst[])
{
    cout << "Minimal right_sonanning tree with weight " << wage << ":\n";
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        cout << mst[i].v1 << "-" << mst[i].v2 << ":" << mst[i].wage << "\n";
    }
}
void MST::prim_list()
{
    //tworzymy pomocnicze zmienne
    //krawedz
    Edge edge;
    //indeks wierzcholka
    int v = 0;
    //pozycja
    position = 0;
    //waga
    wage = 0;

    //deklarujemy kolejke
    Edge *queue = new Edge[number_of_edges];
    //deklarujemy drzewo
    Edge *mst = new Edge[number_of_vertexes - 1];
    //deklarujemy tablice booli sprawdzających czy wierzcholek jest wolny
    bool *vertexes = new bool[number_of_vertexes];

    //ustawiamy poczatkowe wartosci
    for (int i = 0; i < number_of_vertexes; i++){
        vertexes[i] = false;
    }
        
    //dla każdego wierzcholka poza ostatnim poniewaz
    //poniewaz ilosc wierzcholkow = ilosc krawedzi - 1 w mst 
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        //ustawiamy na true, poniewaz jestesmy w nim obecnie
        vertexes[v] = true;
        //ustawiamy liste sasiadow
        p = neighbours[v];

        while (p)
        {
            //jezeli nie jest sasiadem
            //to ustawiamy wartosci i dodajemy do kolejki krawedzi
            if (!vertexes[p->neighbour])
            {
                edge.v1 = v;
                edge.v2 = p->neighbour;
                edge.wage = p->wage;
                add_to_the_queue(edge, queue);
            }
            //przechodzimy do nastepnego
            p = p->next;
        }

        //szuka krawędzi której przynajmniej jeden koniec nie należy do dzrewa
        do
        {
            edge = root(queue);
            delete_first_from_queue(queue);
        } while (vertexes[edge.v1] && vertexes[edge.v2]);

        //jak znalazlo to ustawia wartosci
        if (vertexes[edge.v1])
        {
            v = edge.v2;
            vertexes[edge.v2] = true;
        }
        else
        {
            v = edge.v1;
            vertexes[edge.v1] = true;
        }
        mst[i] = edge;
        wage += edge.wage;
    }
    //wyswietlanie drzewa
    print_mst(mst);
}
void MST::prim_matrix()
{
    //Tworzymy krawedz
    Edge edge;
    //index wierzcholka
    int v = 0;
    //pozycja
    position = 0;
    //waga
    wage = 0;

    //tworzymy kolejke
    Edge *queue = new Edge[number_of_edges];
    //tworzymy drzewo
    Edge *mst = new Edge[number_of_vertexes - 1];
    //tworzymy tablice ktora bedzie mowic czy wierzcholek zawiera sie juz w drzewie
    bool *vertexes = new bool[number_of_vertexes];

    //ustawiamy tablice
    for (int i = 0; i < number_of_vertexes; i++){
        vertexes[i] = false;
    }
    
    //przechodzimy po kazdym wierzcholku poza ostatnim
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        //ustawiamy na odwiedzony
        vertexes[v] = true;

        
        for (int j = 0; j < number_of_vertexes; j++)
        {
            if (!vertexes[j] && graph[v][j] != 0)
            {
                edge.v1 = v;
                edge.v2 = j;
                edge.wage = graph[v][j];
                add_to_the_queue(edge, queue);
            }
        }
        do
        {
            edge = root(queue);
            delete_first_from_queue(queue);
        } while (vertexes[edge.v1] && vertexes[edge.v2]);

        if (vertexes[edge.v1])
        {
            v = edge.v2;
            vertexes[edge.v2] = true;
        }
        else
        {
            v = edge.v1;
            vertexes[edge.v1] = true;
        }
        mst[i] = edge;
        wage += edge.wage;
    }
    print_mst(mst);
}
void MST::kruskal_list()
{
    Edge edge;

    Datasets *datasets = new Datasets[number_of_vertexes];
    Edge *queue = new Edge[number_of_edges];
    Edge *mst = new Edge[number_of_vertexes - 1];
    wage = 0;
    position = 0;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        create_dataset(i);
    }

    for (int i = 0; i < number_of_vertexes; i++)
    {
        p = neighbours[i];
        while (p)
        {
            if (p->neighbour >= i)
            {
                edge.v1 = i;
                edge.v2 = p->neighbour;
                edge.wage = p->wage;
                add_to_the_queue(edge, queue);
            }
            p = p->next;
        }
    }
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        do
        {
            edge = root(queue);
            delete_first_from_queue(queue);
        } while (find_dataset(edge.v1) == find_dataset(edge.v2));

        mst[i] = edge;
        connect_datasets(edge);
        wage += edge.wage;
    }
    print_mst(mst); // nienaiwna implementacja ziorów rozlacznych
}
void MST::kruskal_matrix()
{
    Edge edge;
    Datasets *datasets = new Datasets[number_of_vertexes];
    Edge *queue = new Edge[number_of_edges];
    Edge *mst = new Edge[number_of_vertexes - 1];
    wage = 0;
    position = 0;

    for (int i = 0; i < number_of_vertexes; i++)
    {
        create_dataset(i);
    }

    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (int j = i; j < number_of_vertexes; j++)
        {
            if (graph[i][j] != 0)
            {
                edge.v1 = i;
                edge.v2 = j;
                edge.wage = graph[i][j];
                add_to_the_queue(edge, queue);
            }
        }
    }

    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        do
        {
            edge = root(queue);
            delete_first_from_queue_Kruskal(queue);
        } while (find_dataset(edge.v1) == find_dataset(edge.v2));

        mst[i] = edge;
        connect_datasets(edge);
        wage += edge.wage;
    }
    print_mst(mst);
}
MST::Edge MST::root(Edge queue[])
{
    return queue[0];
}
void MST::add_to_the_queue(Edge r, Edge queue[])
{
    int i, j;
    i = position++;
    j = (i - 1) / 2;

    while (i > 0 && queue[j].wage > r.wage)
    {
        queue[i] = queue[j];
        i = j;
        j = (i - 1) / 2;
    }

    queue[i] = r;
}
void MST::delete_first_from_queue(Edge queue[])
{
    int left_son, right_son;
    Edge r;

    position--;
    queue[0] = queue[position];

    int i, j;
    i = 0;
    left_son = 1;
    right_son = 2;

    while ((queue[i].wage > min(queue[left_son].wage, queue[right_son].wage)) && position > 2 * i)
    {

        left_son = 2 * i + 1;
        right_son = 2 * i + 2;
        if (position == left_son)
        {

            if (queue[left_son].wage < queue[i].wage)
            {
                r = queue[i];
                queue[i] = queue[j];
                queue[j] = r;
            }
            break;
        }
        else
        {
            if (min(queue[left_son].wage, queue[right_son].wage) < queue[i].wage)
            {
                if (queue[left_son].wage <= queue[right_son].wage)
                    j = left_son;
                else
                    j = right_son;

                r = queue[i];
                queue[i] = queue[j];
                queue[j] = r;
                i = j;
            }
        }
    }
}
void MST::delete_first_from_queue_Kruskal(Edge queue[])
{
    int left_son, right_son;
    Edge r;

    position--;
    queue[0] = queue[position];

    int i, j;
    i = 0;
    left_son = 1;
    right_son = 2;

    while ((queue[i].wage > min(queue[left_son].wage, queue[right_son].wage)) && position >= 2 * i)
    {

        left_son = 2 * i + 1;
        right_son = 2 * i + 2;
        if (position == left_son)
        {

            if (queue[left_son].wage < queue[i].wage)
            {
                r = queue[i];
                queue[i] = queue[j];
                queue[j] = r;
            }
            break;
        }
        else
        {
            if (min(queue[left_son].wage, queue[right_son].wage) < queue[i].wage)
            {
                if (queue[left_son].wage <= queue[right_son].wage)
                    j = left_son;
                else
                    j = right_son;

                r = queue[i];
                queue[i] = queue[j];
                queue[j] = r;
                i = j;
            }
        }
    }
}
void MST::create_dataset(int v)
{
    datasets[v].root = v;
    datasets[v].power = 0;
}
int MST::find_dataset(int v)
{
    if (datasets[v].root != v)
        datasets[v].root = find_dataset(datasets[v].root);
    return datasets[v].root;
}
void MST::connect_datasets(Edge r)
{
    int ru, rv;

    ru = find_dataset(r.v1); // Wyznaczamy korzeń drzewa z węzłem u
    rv = find_dataset(r.v2); // Wyznaczamy korzeń drzewa z węzłem v
    if (ru != rv)            // rootie muszą być różne
    {
        if (datasets[ru].power > datasets[rv].power) // Porównujemy rangi drzew
            datasets[rv].root = ru;                  // ru więrsze, dołączamy rv
        else
        {
            datasets[ru].root = rv; // równe lub rv więrsze, dołączamy ru
            if (datasets[ru].power == datasets[rv].power)
                datasets[rv].power++;
        }
    }
}
void MST::measure_time()
{

    int wielkosc[21][2] = {{10, 20}, {10, 60}, {10, 99}, {25, 20}, {25, 60}, {25, 99}, {50, 20}, {50, 60}, {50, 99}, {75, 20}, {75, 60}, {75, 99}, {100, 20}, {100, 60}, {100, 99}, {150, 20}, {150, 60}, {150, 99}, {200, 20}, {200, 60}, {200, 99}};

    for (int i = 0; i < 21; i++)
    {

        number_of_vertexes = wielkosc[i][0];
        density = wielkosc[i][1];

        string filename;
        string txt = ".txt";
        string floor = "_";
        string size, density_to_string;
        size = to_string(number_of_vertexes);
        density_to_string = to_string(density);
        filename = "MST_PrimList_";
        filename = filename + size + floor + density_to_string + txt; // stworzenie nazwy pliru

        ofstream fout;
        fout.open(filename);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
            generate_graph();
            auto begin = chrono::steady_clock::now();
            prim_list();
            auto end = chrono::steady_clock::now();
            fout << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        filename = "MST_PrimMatrix_";
        filename = filename + size + floor + density_to_string + txt;
        fout.open(filename);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
            generate_graph();
            auto begin = std::chrono::steady_clock::now();
            prim_matrix();
            auto end = std::chrono::steady_clock::now();
            fout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        filename = "MST_rrusralLista_";
        filename = filename + size + floor + density_to_string + txt;
        fout.open(filename);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
            generate_graph();
            auto begin = chrono::steady_clock::now();
            kruskal_list();
            auto end = chrono::steady_clock::now();
            fout << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();

        filename = "MST_KruskalMatrix_";
        filename = filename + size + floor + density_to_string + txt;
        fout.open(filename);
        srand(time(NULL));

        for (int i = 0; i < 50; i++) // pomiar czasu operacji
        {
            generate_graph();
            auto begin = chrono::steady_clock::now();
            kruskal_matrix();
            auto end = chrono::steady_clock::now();
            fout << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        fout.close();
    }
}
