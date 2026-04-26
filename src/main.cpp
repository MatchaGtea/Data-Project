#include "menu.h"
#include "data_structures/graph.h"
#include "data_structures/hash.h"

int main() {
    Graph* g = createGraph();
    HashTable* ht = createHashTable();

    showMenu(g, ht);

    freeGraph(g);
    freeHashTable(ht);
    return 0;
}
