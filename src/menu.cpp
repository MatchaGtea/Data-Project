#include <iostream>
#include <cstring>
#include "menu.h"
#include "data_structures/algorithm.h"

static void handleAdd(Graph* g, HashTable* ht) {
    char name[50];
    std::cout << "Location name: ";
    std::cin.ignore();
    std::cin.getline(name, 50);
    addLocation(g, name);
    hashInsert(ht, name, g->nodeCount - 1);
}

static void handleAddPath(Graph* g) {
    char src[50], dest[50];
    int weight;
    std::cout << "From: ";
    std::cin.ignore();
    std::cin.getline(src, 50);
    std::cout << "To: ";
    std::cin.getline(dest, 50);
    std::cout << "Distance: ";
    std::cin >> weight;
    addPath(g, src, dest, weight);
}

static void handleDelete(Graph* g, HashTable* ht) {
    char name[50];
    std::cout << "Location to delete: ";
    std::cin.ignore();
    std::cin.getline(name, 50);
    deleteLocation(g, name);
    hashDelete(ht, name);
}

static void handleSearch(HashTable* ht) {
    char name[50];
    std::cout << "Search location: ";
    std::cin.ignore();
    std::cin.getline(name, 50);
    int id = hashSearch(ht, name);
    if (id == -1)
        std::cout << "'" << name << "' not found.\n";
    else
        std::cout << "Found: " << name << " (id: " << id << ")\n";
}

static void handleShortestPath(Graph* g) {
    char src[50], dest[50];
    std::cout << "From: ";
    std::cin.ignore();
    std::cin.getline(src, 50);
    std::cout << "To: ";
    std::cin.getline(dest, 50);

    std::cout << "\n1. Dijkstra (weighted)\n2. BFS (unweighted)\nAlgorithm: ";
    int choice;
    std::cin >> choice;
    if (choice == 1) dijkstra(g, src, dest);
    else             bfs(g, src, dest);
}

void showMenu(Graph* g, HashTable* ht) {
    int choice;
    do {
        std::cout << "\n=== Smart Campus Navigation ===\n";
        std::cout << "1. Add Location\n";
        std::cout << "2. Add Path\n";
        std::cout << "3. Delete Location\n";
        std::cout << "4. Search Location\n";
        std::cout << "5. Display Map\n";
        std::cout << "6. Find Shortest Path\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: handleAdd(g, ht);        break;
            case 2: handleAddPath(g);        break;
            case 3: handleDelete(g, ht);     break;
            case 4: handleSearch(ht);        break;
            case 5: displayGraph(g);         break;
            case 6: handleShortestPath(g);   break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
