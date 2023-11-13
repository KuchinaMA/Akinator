#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>

#include "Tree.h"

Node* node_ctor(char* data, Node* left, Node* right) {

    Node* node = (Node*)calloc(1, sizeof(Node));

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
    fprintf(output, "%s\n", node->data);
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
    fprintf(output, "%s\n", node->data);
    fprintf(output, ")\n");
}

void print_node_in(Node* node, FILE* output) {

    if (node == 0) {
        fprintf(output, "nil\n");
        return;
    }
    fprintf(output, "(\n");
    print_node_in(node->left, output);
    fprintf(output, "%s\n", node->data);
    print_node_in(node->right, output);
    fprintf(output, ")\n");
}


Tree* tree_ctor(Node* root, size_t size) {

    assert(root);

    Tree* tree = (Tree*)calloc(1, sizeof(Tree));

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

    //getline(&data, &MAX_LINE_LEN, file);
    //fgets(data, MAX_LINE_LEN, file);

    get_data(file, node);

    //fscanf(file, "%s", data);
    //printf("new %s\n", data);            //отладка
    //strcpy(node->data, data);

    int n = fscanf(file, "%s", current);
    //printf("%d\n", n);
    if (strcmp("(", current) == 0) {

        printf("open %s\n", current);    //отладка
        node->left = read_node(file);
    }

    else if (strcmp("nil", current) == 0) {

        printf("nils %s\n", current);    //отладка
        node->left = 0;
    }

    else {
        printf("Syntax error!\n");
        printf("current %s\n", current);
    }


    fscanf(file, "%s", current);
    if (strcmp("(", current) == 0) {

        printf("open %s\n", current);    //отладка
        node->right = read_node(file);
    }

    else if (strcmp("nil", current) == 0) {

        printf("nil %s\n", current);     //отладка
        node->right = 0;
    }

    else {
        printf("Syntax error!\n");
        printf("current %s\n", current);
    }


    fscanf(file, "%s", current); //закрывающая скобка
    printf("data: %s\n", node->data);

    return node;
}

Node* read_data(FILE* file) {

    char current[MAX_LINE_LEN] = "";
    char smth[1] = "";

    //fgets(current, MAX_LINE_LEN, file);
    //getline(&current, &MAX_LINE_LEN, file);

    fscanf(file, "%s", current); //открывающая скобка
    printf("open %s\n", current);

    //fgetc(file); //лишний /n

    Node* new_node = read_node(file);

    return new_node;
}





int get_data(FILE* file, Node* node) {

    char data[MAX_LINE_LEN] = "";
    char symb = '0';
    int i = 0;

    while ((symb = fgetc(file)) != EOF && symb != '>') {
        data[i] = symb;
        i++;
    }
    data[i] = '\0';
    strcpy(node->data, data);
    return 0;
}






















/*NodeAkinator* buildTree(FILE* file)
{
    char token[MAX_LEN];
    int i = 0;
    fscanf(file, "%s", token);
    if (strcmp(token, "(") == 0) {
        char c;
        token[MAX_LEN];
        while ((c = fgetc(file)) != EOF && c != '>') {
            if (c == '<') {
                i--;
                continue; // Пропускаем символ '<' в начале строки
            }
            if (i < MAX_LEN - 1) {
                token[i] = c;
                i++;
            }
        }
        token[i] = '\0';
        if (strcmp(token, "<null") == 0) {
            return NULL;
        }
        NodeAkinator* newNode = (NodeAkinator*)malloc(sizeof(NodeAkinator));
        strcpy(newNode->value, token);
        newNode->left = buildTree(file);
        newNode->right = buildTree(file);
        fscanf(file, "%s", token); // Пропускаем закрывающую скобку
        return newNode;
    } else {
        if (strcmp(token, "<null>") == 0) {
            return NULL;
        }
        NodeAkinator* newNode = (NodeAkinator*)malloc(sizeof(NodeAkinator));
        strcpy(newNode->value, token);
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
}*/
