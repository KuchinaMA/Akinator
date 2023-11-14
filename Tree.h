#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

const size_t MAX_LINE_LEN = 100;
const char DATA_POISON[] = "";

struct Node {
    char data[MAX_LINE_LEN];
    Node* left;
    Node* right;
};

struct Tree {
    Node* root;
    size_t size;
};

Node* node_ctor(char* data, Node* left, Node* right);
int node_dtor(Node* node);

Tree* tree_ctor(Node* root, size_t size);
int tree_dtor(Tree* tree);

void print_node_pre(Node* node, FILE* output);
void print_node_post(Node* node, FILE* output);
void print_node_in(Node* node, FILE* output);

Node* read_node(FILE* file);
Tree* read_data(FILE* file);
int get_line(FILE* file, Node* node);
int count_nodes(FILE* file);


#endif // TREE_H_INCLUDED

