#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "Tree.h"
#include "TreeDump.h"

int graph_dump(const Tree* tree) {

    FILE* dotfile = fopen("TreePicture.dot", "w");

    fprintf(dotfile, "digraph {\n");
    //fprintf(dotfile, "  charset = \"UTF-8\";\n");
    fprintf(dotfile, "  rankdir = HR;\n");
    fprintf(dotfile, "  node [shape = Mrecord, color = \"#800000\", style = filled, fillcolor = \"#FFD5D5\"];\n");

    node_graph_dump(tree->root, dotfile);
    edge_graph_dump(tree->root, dotfile);

    fprintf(dotfile, "}");

    system("dot TreePicture.dot -T png -o TreePicture.png");

    fclose(dotfile);

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
        fprintf(dotfile, "  node_%p -> node_%p [weight = 1, color = \"#800000\"];\n", node, node->left);
        edge_graph_dump(node->left, dotfile);
    }

    if (node->right != 0) {
        fprintf(dotfile, "  node_%p -> node_%p [weight = 1, color = \"#800000\"];\n", node, node->right);
        edge_graph_dump(node->right, dotfile);
    }
}
