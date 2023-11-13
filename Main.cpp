#include <stdio.h>

#include "Tree.h"
#include "TreeDump.h"

int main () {

    FILE* output = fopen("TreeDump.txt", "w");

    /*Node* node_cat = node_ctor("cat", 0, 0);
    Node* node_none = node_ctor("God knows who", 0, 0);
    Node* node_purr = node_ctor("can purr", node_cat, node_none);
    Node* node_bird = node_ctor("bird", 0, 0);
    Node* node_animal = node_ctor("animal", node_purr, node_bird);

    Tree* tree0 = tree_ctor(node_animal, 5);
    print_node_pre(tree0->root, output);
    graph_dump(tree0); */

    FILE* input1 = fopen("TestData1.txt", "r");
    Node* node2 = read_data(input1);
    Tree* tree2 = tree_ctor(node2, 5);
    print_node_pre(tree2->root, output);
    graph_dump(tree2);
    tree_dtor(tree2);

    fclose(input1);

    fclose(output);

    return 0;
}
