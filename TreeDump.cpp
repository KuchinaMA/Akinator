#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "Tree.h"
#include "TreeDump.h"

int graph_dump(const Tree* tree) {

    FILE* dotfile = fopen("TreePicture.dot", "w");

    fprintf(dotfile, "digraph {\n");
    fprintf(dotfile, "  rankdir = HR;\n");
    fprintf(dotfile, "  node [shape = Mrecord, color = \"#000066\", style = filled, fillcolor = \"#D5EAFF\"];\n");

    node_graph_dump(tree->root, dotfile);
    edge_graph_dump(tree->root, dotfile);

    fprintf(dotfile, "}");

    fclose(dotfile);

    system("dot TreePicture.dot -T png -o TreePicture.png");

    return 0;
}


void node_graph_dump(Node* node, FILE* dotfile) {

    if (node == 0)
        return;
    fprintf(dotfile, "  node_%p[label = \" %s \"]; \n", node, node->data);
    node_graph_dump(node->left, dotfile);
    node_graph_dump(node->right, dotfile);

}

void edge_graph_dump(Node* node, FILE* dotfile) {

    if (node->left != 0) {
        fprintf(dotfile, "  node_%p -> node_%p [label = \"yes\", weight = 1, color = \"#006400\"];\n", node, node->left);
        edge_graph_dump(node->left, dotfile);
    }

    if (node->right != 0) {
        fprintf(dotfile, "  node_%p -> node_%p [label = \"no\", weight = 1, color = \"#800000\"];\n", node, node->right);
        edge_graph_dump(node->right, dotfile);
    }
}
