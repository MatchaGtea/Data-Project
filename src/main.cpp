#include "menu.h"
#include "data_structures/graph.h"
#include "data_structures/hash.h"

#include <fstream>

static const char* graphDataFile() {
    static const char* candidates[] = {
        "data/campus_map.txt",
        "../data/campus_map.txt"
    };

    for (const char* candidate : candidates) {
        std::ifstream file(candidate);
        if (file) return candidate;
    }
    return candidates[0];
}

static void loadHashFromGraph(Graph* g, HashTable* ht) {
    Node* curr = g->head;
    while (curr) {
        hashInsert(ht, curr->name, curr->id);
        curr = curr->next;
    }
}

int main() {    
    Graph* g = createGraph();
    HashTable* ht = createHashTable();

    if (loadGraphFromFile(g, graphDataFile())) {
        loadHashFromGraph(g, ht);
    }

    showMenu(g, ht);

    freeGraph(g);
    freeHashTable(ht);
    return 0;
}
