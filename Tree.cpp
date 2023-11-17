#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>

#include "Tree.h"

Node* node_ctor(char* data, Node* left, Node* right) {

    Node* node = (Node*)calloc(1, sizeof(Node));
           //?
    strcpy(node->data, data);
    node->left = left;
    node->right = right;

    return node;
}

int node_dtor(Node* node) {

    if (node->left != 0 && node->right != 0) {
        node_dtor(node->left);
        node_dtor(node->right);
    }

    node->left = 0;
    node->right = 0;
    strcpy(node->data, DATA_POISON);

    free(node);

    return 0;
}


void print_node_pre(Node* node, FILE* output) {

    if (node == 0) {
        fprintf(output, "nil\n");
        return;
    }
    fprintf(output, "(\n");
    fprintf(output, "<%s>\n", node->data);
    print_node_pre(node->left, output);
    print_node_pre(node->right, output);
    fprintf(output, ")\n");
}


void print_node_post(Node* node, FILE* output) {

    if (node == 0) {
        fprintf(output, "nil\n");
        return;
    }
    fprintf(output, "(\n");
    print_node_post(node->left, output);
    print_node_post(node->right, output);
    fprintf(output, "<%s>\n", node->data);
    fprintf(output, ")\n");
}


void print_node_in(Node* node, FILE* output) {

    if (node == 0) {
        fprintf(output, "nil\n");
        return;
    }
    fprintf(output, "(\n");
    print_node_in(node->left, output);
    fprintf(output, "<%s>\n", node->data);
    print_node_in(node->right, output);
    fprintf(output, ")\n");
}


Tree* tree_ctor(Node* root, size_t size) {

    assert(root);

    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
                    //?
    tree->root = root;
    tree->size = size;

    return tree;
}


int tree_dtor(Tree* tree) {

    node_dtor(tree->root);
    tree->root = 0;
    tree->size = 0;

    free(tree);

    return 0;
}


Node* read_node(FILE* file) {

    char current[MAX_LINE_LEN] = "";

    Node* node = (Node*)calloc(1, sizeof(Node));
                   //?
    get_line(file, node->data);

    fscanf(file, "%s", current);

    if (strcmp("(", current) == 0)
        node->left = read_node(file);

    else if (strcmp("nil", current) == 0)
        node->left = 0;

    else {
        printf("Syntax error!\n");
        printf("current %s\n", current);
    }


    fscanf(file, "%s", current);
    if (strcmp("(", current) == 0)
        node->right = read_node(file);

    else if (strcmp("nil", current) == 0)
        node->right = 0;

    else {
        printf("Syntax error!\n");
        printf("current %s\n", current);
    }


    fscanf(file, "%s", current); //закрывающая скобка

    return node;
}


Tree* read_data(FILE* file) {

    int size = count_nodes(file);

    char current[MAX_LINE_LEN] = "";

    fscanf(file, "%s", current);          //открывающая скобка

    Node* new_node = read_node(file);
    Tree* new_tree = tree_ctor(new_node, size);

    return new_tree;
}

int count_nodes(FILE* file) {

    int nodes_num = 0;
    int pos = ftell(file);

    char brackets[MAX_LINE_LEN] = "";
    while (fscanf(file, "%s", brackets) > 0) {
        if (strcmp(brackets, "(") == 0)
            nodes_num++;
    }

    fseek(file, pos, SEEK_SET);

    return nodes_num;
}


int get_line(FILE* file, char* line) {

    char symb = '0';
    int i = 0;

    while ((symb = fgetc(file)) != EOF && symb != '>') {
        if (symb == '<') {
            i--;
            continue;
        }
        line[i] = symb;
        i++;
    }

    line[i] = '\0';
    return 0;
}


