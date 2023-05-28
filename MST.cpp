#include "MST.h"

using namespace std;

void MST::MST_menu()
{

    int option = -1;
    //

    while (option != 0)
    {
        cout << "\nEnter option?" <<    endl;
        cout << "1. Load graph from file" <<    endl;
        cout << "2. Generate graph" <<  endl;
        cout << "3. Find the minimum right_spanning tree using Prim's algorithm from the list" <<  endl;
        cout << "4. Find the minimum right_spanning tree using Prim's algorithm from the matrix" <<    endl;
        cout << "5. Find the minimum right_spanning tree using Krusral's algorithm from the list" <<   endl;
        cout << "6. Find the minimum right_spanning tree using Krusral's algorithm from the matrix" << endl;
        cout << "7. Print graph" << endl;
        cout << "0. Exit" <<    endl;

        cin >> option;

        switch (option) // wybór opcji oraz wywolanie odpowiedniego menu
        {
            case 0:
                return;
            case 1:
                graph = NULL;
                neighbours = NULL;
                number_of_vertexes = 0;
                number_of_edges = 0;
                create_graph_from_file();
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
                break;
            case 3:
                prim_list();
                break;
            case 4:
                prim_matrix();
                break;
            case 5:
                kruskal_list();
                break;
            case 6:
                kruskal_matrix();
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
        print_list_of_neighbours();
        print_matrix();
    }
}

void MST::create_graph_from_file()
{
    string filename;
    int v1, v2, weight;

    cout << "Enter the name of the file: " <<   endl;
    //pobieranie nazwy pliku
    cin >> filename;
    fstream file;
    //otwieranie pliku
    file.open(filename, ios::in);
    //wstawiamy liczbe krawedzi i wierzcholkow
    file >> number_of_edges >> number_of_vertexes;

    //tworzymy liste sasiadow
    neighbours = new Neighbour *[number_of_vertexes];

    //tworzymy graf(macierz)
    graph = new int *[number_of_vertexes];

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

    //ustawiamy listy sasiedztwa
    for (int i = 0; i < number_of_edges; i++)
    {
        file >> v1 >> v2 >> weight;
        p = new Neighbour;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->weight = weight;
        neighbours[v1] = p;

        p = new Neighbour;
        p->neighbour = v1;
        p->next = neighbours[v2];
        p->weight = weight;
        neighbours[v2] = p;

        graph[v1][v2] = weight;
        graph[v2][v1] = weight;
    }
}

void MST::generate_graph()
{
    srand(time(NULL));
    neighbours = new Neighbour *[number_of_vertexes];
    int v1, v2, weight;
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
    //poza grafem sa elementy od 1 do konca
    int *inside_graph = new int[number_of_vertexes];
    int *outside_graph = new int[number_of_vertexes];

    inside_graph[0] = 0;
    //dajemy indeksy wierzcholkom
    for (int i = 0; i < number_of_vertexes; i++)
    {
        outside_graph[i] = i+1;
    }

    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        //losujemy dwa indexy z wierzcholkow ktore sa w grafie i z tych ktore nie 
        index_from_graph = rand() % (i + 1);
        index_out_graph = rand() % (number_of_vertexes - i - 1);

        //przypisujemy je odpowiednio do v1 i v2
        v1 = inside_graph[index_from_graph];
        v2 = outside_graph[index_out_graph];

        //ustawiamy weight
        weight = rand() % 1000000 + 1;

        //przypisujemy wartosc 0
        outside_graph[index_out_graph] = 0;

        //ustawiamy wierzcholek
        inside_graph[i + 1] = v2;

        //sortujemy żeby zera były na koncu tablicy
        sort(outside_graph, outside_graph + number_of_vertexes - i - 1, greater<int>());

        //ustawiamy weight
        graph[v1][v2] = weight;
        graph[v2][v1] = weight;

        //stworzenie nowej listy sasiadow
        p = new Neighbour;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->weight = weight;
        neighbours[v1] = p;

        //stworzenie nowej listy sasiadow
        p = new Neighbour;
        p->neighbour = v1;
        p->next = neighbours[v2];
        p->weight = weight;
        neighbours[v2] = p;
    }
    
    //losujemy ilosc krawedzi
    number_of_edges = density * number_of_vertexes * (number_of_vertexes - 1) / 2 / 100;

    //dopasowywujemy krawedzie
    for (int i = number_of_vertexes - 1; i < number_of_edges; i++)
    {
        //losujemy wierzcholki
        v1 = rand() % number_of_vertexes;
        v2 = rand() % number_of_vertexes;

        //dopoki wylosowal te same wierzcholki lub juz istnieje krawedz pomiedzy nimi
        //to losuje jeszcze raz
        while (v1 == v2 || graph[v1][v2] != 0)
        {
            v1 = rand() % number_of_vertexes;
            v2 = rand() % number_of_vertexes;
        }

        //losujemy wage
        weight = rand() % 100 + 1;

        //ustawiamy wage
        graph[v1][v2] = weight;
        graph[v2][v1] = weight;

        //tworzymy liste sasiadow
        p = new Neighbour;
        p->neighbour = v2;
        p->next = neighbours[v1];
        p->weight = weight;
        neighbours[v1] = p;

        p = new Neighbour;
        p->neighbour = v1;
        p->next = neighbours[v2];
        p->weight = weight;
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
            cout << setw(3) << p->neighbour << ":" << p->weight;
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
    cout << "Minimal right spnanning tree with weight " << weight << ":\n";
    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        cout << mst[i].v1 << "-" << mst[i].v2 << ":" << mst[i].weight << "\n";
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
    weight = 0;

    //deklarujemy kolejke
    Edge *queue = new Edge[number_of_edges];
    //deklarujemy drzewo
    Edge *mst = new Edge[number_of_vertexes - 1];
    //deklarujemy tablice booli sprawdzających czy wierzcholek jest wolny
    bool *vertexes = new bool[number_of_vertexes];

    //ustawiamy poczatkowe wartosci czy zostaly odwiedzone
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
            //jezeli sasiad nie jest odwiedzony
            //to ustawiamy wartosci i dodajemy do kolejki krawedzi
            if (!vertexes[p->neighbour])
            {
                edge.v1 = v;
                edge.v2 = p->neighbour;
                edge.weight = p->weight;
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
            //ustawie nowy na ten ktory bedzie sprawdzany w nastepnej iteracji
            v = edge.v2;
            vertexes[edge.v2] = true;
        }
        else
        {
            //ustawianie v1 jako v w nastepnej iteracji
            v = edge.v1;
            vertexes[edge.v1] = true;
        }
        mst[i] = edge;
        weight += edge.weight;
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
    weight = 0;

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

        //dla kazdego wierzcholka
        for (int j = 0; j < number_of_vertexes; j++)
        {
            //jezeli wierzcholek nie jest odwiedzony
            //i krawedz ma wartosc
            //to ustawiamy krawedz
            if (!vertexes[j] && graph[v][j] != 0)
            {
                edge.v1 = v;
                edge.v2 = j;
                edge.weight = graph[v][j];
                add_to_the_queue(edge, queue);
            }
        }
        //bierzemy krawedz ktora nie zostala dodana do drzewa czyli jeden z wierzcholkow znajduje sie w drzewie
        do
        {
            edge = root(queue);
            delete_first_from_queue(queue);
        } while (vertexes[edge.v1] && vertexes[edge.v2]);
        
        //jezeli wierzcholek v1 znajduje sie w drzewie
        //to ustawiamy v jako v2 i oznaczamy wierzcholek v2 jako odwiedzony
        if (vertexes[edge.v1])
        {
            v = edge.v2;
            vertexes[edge.v2] = true;
        }
        //w przeciwnym przypadku ustawiamy v jako v1 i wierzcholek v1 jako odwiedzony
        else
        {
            v = edge.v1;
            vertexes[edge.v1] = true;
        }
        //ustawiamy krawedz
        mst[i] = edge;
        //dodajemy ogolna weight
        weight += edge.weight;
    }
    //wyswietlamy na ekranie
    print_mst(mst);
}

void MST::kruskal_list()
{
    //tworzymy pomocnicza krawedz
    Edge edge;
    //tworzymy zbiory
    datasets = new Datasets[number_of_vertexes];
    //tworzymy kolejke
    Edge *queue = new Edge[number_of_edges];
    //tworzymy drzewo. które będzie tablicą krawedzi
    Edge *mst = new Edge[number_of_vertexes - 1];
    //ustawiamy weight na 0
    weight = 0;
    //ustawiamy pozycje na 0
    position = 0;

    //tworzymy zbiory rozlaczne ktore nie sa polaczone
    for (int i = 0; i < number_of_vertexes; i++)
    {
        create_dataset(i);
    }

    //iterujemy po kazdym wierzcholku
    for (int i = 0; i < number_of_vertexes; i++)
    {
        //ustawiamy p jako pierwszego sasiada wierzcholka i
        p = neighbours[i];

        //dopoki istnieje sasiad
        while (p)
        {
            //nie bedzie powtorzen poniewaz sprawdzamy obecny indeks z indeksem sasiada
            //sasiedzi ida w dol wiec dlatego dajemy warunek w gore
            if (p->neighbour >= i)
            {
                //nastepnie ustawiamy krawedz i dodajemy do kolejki
                edge.v1 = i;
                edge.v2 = p->neighbour;
                edge.weight = p->weight;
                add_to_the_queue(edge, queue);
            }
            //idziemy do sasiada
            p = p->next;
        }
    }

    for (int i = 0; i < number_of_vertexes - 1; i++)
    {
        
        do
        {   //bierzemy korzen do momentu w ktorym krawedz ma wierzcholki w dwoch roznych zbiorach
            edge = root(queue);
            delete_first_from_queue(queue);
        } while (find_dataset(edge.v1) == find_dataset(edge.v2));

        mst[i] = edge;
        connect_datasets(edge);
        weight += edge.weight;
    }
    print_mst(mst); 
}
void MST::kruskal_matrix()
{
    //tworzymy pomocnicza krawedz
    Edge edge;
    //tworzymy zbiory
    Datasets *datasets = new Datasets[number_of_vertexes];
    //tworzymy kolejke
    Edge *queue = new Edge[number_of_edges];
    //tworzymy drzewo
    Edge *mst = new Edge[number_of_vertexes - 1];
    //ustawiamy weight na 0
    weight = 0;
    //ustawiamy pozycje na 0
    position = 0;
    //dla kazdego wierzcholka tworzymy zbior
    for (int i = 0; i < number_of_vertexes; i++)
    {
        create_dataset(i);
    }

    //dla kazdego wierzcholka
    for (int i = 0; i < number_of_vertexes; i++)
    {
        for (int j = i; j < number_of_vertexes; j++)
        {
            //jezeli istnieje krawedz
            //to ustawiamy wartosci i dodajemy do kolejki
            if (graph[i][j] != 0)
            {
                edge.v1 = i;
                edge.v2 = j;
                edge.weight = graph[i][j];
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
        weight += edge.weight;
    }
    print_mst(mst);
}

//zwraca najmnniejsza wartosc
MST::Edge MST::root(Edge queue[])
{
    return queue[0];
}
//dodawanie do kolejki i ustawienie na odpowiedniej pozycji
void MST::add_to_the_queue(Edge edge, Edge queue[])
{
    int i, j;
    i = position++;
    j = (i - 1) / 2;

    while (i > 0 && queue[j].weight > edge.weight)
    {
        queue[i] = queue[j];
        i = j;
        j = (i - 1) / 2;
    }

    queue[i] = edge;
}

void MST::delete_first_from_queue(Edge queue[])
{
    //tworzymy pomocnicze zmienne
    //indkesy lewego i prawgo syna
    int left_son, right_son;
    //tworzymy pomocnicza krawedz
    Edge edge;

    //zmniejszamy pozycje poniewaz chcemy ustawic ostatni element jako pierwszy
    position--;
    queue[0] = queue[position];

    int i, j;
    i = 0;
    left_son = 1;
    right_son = 2;

    //ponownie ustawiamy kolejnosc
    while ((queue[i].weight > min(queue[left_son].weight, queue[right_son].weight)) && position > 2 * i)
    {

        //przypisujemy indeksy
        left_son = 2 * i + 1;
        right_son = 2 * i + 2;

        //sprawdzamy czy jest na pozycji lewego syna
        if (position == left_son)
        {
            //jezeli waga lewego syna jest mniejsza to zamieniamy
            if (queue[left_son].weight < queue[i].weight)
            {
                edge = queue[i];
                queue[i] = queue[j];
                queue[j] = edge;
            }
            break;
        }
        else
        {
            //jezeli weight jest wiekszy niz lewy i prawy syn
            if (min(queue[left_son].weight, queue[right_son].weight) < queue[i].weight)
            {
                //jezeli lewy syn jest mniejszy rowny prawemu
                if (queue[left_son].weight <= queue[right_son].weight){
                    j = left_son;
                }
                    
                else{
                    j = right_son;
                }
                
                //ustawiamy wartosci
                edge = queue[i];
                queue[i] = queue[j];
                queue[j] = edge;
                i = j;
            }
        }
    }
}

void MST::delete_first_from_queue_Kruskal(Edge queue[])
{
    //deklarujemy pomocnicze zmienne
    int left_son, right_son;
    //deklarujemy krawedz
    Edge edge;
    //odejmujemy 1 od pozycji
    position--;
    //ustawiamy ostatni element jako pierwszy
    queue[0] = queue[position];

    //deklarujemy indeksy
    int i, j;
    i = 0;
    //przypisujemy wartosci
    left_son = 1;
    right_son = 2;

    //ponownie ustawiamy kolejnosc
    //dopoki waga obecna jest wieksza niz synow i pozycja jest wieksza niz 2i
    while ((queue[i].weight > min(queue[left_son].weight, queue[right_son].weight)) && position >= 2 * i)
    {

        //ustawiamy pozycje
        left_son = 2 * i + 1;
        right_son = 2 * i + 2;
        //jezeli jest na pozycji lewego syna
        if (position == left_son)
        {
            //jezeli waga lewego syna jest mniejsza niz waga krawedzi
            if (queue[left_son].weight < queue[i].weight)
            {
                edge = queue[i];
                queue[i] = queue[j];
                queue[j] = edge;
            }
            break;
        }
        else
        {
            //jezeli waga krawedzi jest wieksza niz obaj synowie
            if (min(queue[left_son].weight, queue[right_son].weight) < queue[i].weight)
            {
                //jezeli lewy syn jest mniejszy rowny niz prawy
                if (queue[left_son].weight <= queue[right_son].weight){
                    j = left_son;
                }
                //jezeli prawy jest wiekszy
                else{
                    j = right_son;
                }
                //przypisujemy wartosci
                edge = queue[i];
                queue[i] = queue[j];
                queue[j] = edge;
                i = j;
            }
        }
    }
}
//deklaruje liste zbiorow rozlacznych
void MST::create_dataset(int v)
{
    datasets[v].root = v;
    datasets[v].power = 0;
}
int MST::find_dataset(int v)
{
    if (datasets[v].root != v){
        datasets[v].root = find_dataset(datasets[v].root);
    }
    return datasets[v].root;
}
void MST::connect_datasets(Edge edge)
{
    int edge_u, edge_v;

    edge_u = find_dataset(edge.v1); // Wyznaczamy korzeń drzewa z węzłem u
    edge_v = find_dataset(edge.v2); // Wyznaczamy korzeń drzewa z węzłem v
    if (edge_u != edge_v)            // korzenie muszą być różne bo inaczej bylyby w tym samym zbiorze
        {
            // Porównujemy moce drzew (do wiekszej mocy dodajemy)
            // edge_u większe, dołączamy edge_v
        if (datasets[edge_u].power > datasets[edge_v].power){
            datasets[edge_v].root = edge_u;
        }
        else
        {
            datasets[edge_u].root = edge_v; // równe lub edge_v więrsze, dołączamy edge_u
            if (datasets[edge_u].power == datasets[edge_v].power){
                datasets[edge_v].power++;
            }
        }
    }
}

void MST::measure_time() {
    int data[21][2] = { {10, 20}, {10, 60}, {10, 99}, {25, 20}, {25, 60}, {25, 99}, {50, 20}, {50, 60}, {50, 99},
                        {75, 20}, {75, 60}, {75, 99}, {100, 20}, {100, 60}, {100, 99}, {150, 20}, {150, 60}, {150, 99}, {200, 20}, {200, 60}, {200, 99}};
    for(int i=0;i<21;i++){
        number_of_vertexes = data[i][0];
        density = data[i][1];

        string filename = "Prim_List_"+to_string(number_of_vertexes)+"_"+ to_string(density)+".txt";
        ofstream file_out;
        file_out.open(filename);
        srand(time(NULL));
        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            generate_graph();
            auto begin = std::chrono::steady_clock::now();
            prim_list();
            auto end = std::chrono::steady_clock::now();
            file_out << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        file_out.close();
        /////////////////////////////////
        filename = "Prim_Matrix_"+to_string(number_of_vertexes)+"_"+ to_string(density)+".txt";
        file_out.open(filename);
        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            generate_graph();
            auto begin = std::chrono::steady_clock::now();
            prim_matrix();
            auto end = std::chrono::steady_clock::now();
            file_out << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        file_out.close();
        ///////////////////////////////////
        filename = "Kruskal_List_"+to_string(number_of_vertexes)+"_"+ to_string(density)+".txt";
        file_out.open(filename);
        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            generate_graph();
            auto begin = std::chrono::steady_clock::now();
            kruskal_list();
            auto end = std::chrono::steady_clock::now();
            file_out << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        file_out.close();
        ////////////////////////////////////
        filename = "Kruskal_Matrix_"+to_string(number_of_vertexes)+"_"+ to_string(density)+".txt";
        file_out.open(filename);
        for(int i = 0; i < 50; i++)                                                                //pomiar czasu operacji
        {
            generate_graph();
            auto begin = std::chrono::steady_clock::now();
            kruskal_matrix();
            auto end = std::chrono::steady_clock::now();
            file_out << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ";
        }
        file_out.close();
    }
}