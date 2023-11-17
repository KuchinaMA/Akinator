#ifndef AKINATORFUNCS_H_INCLUDED
#define AKINATORFUNCS_H_INCLUDED

#include "Types.h"
#include "Stack.h"

enum Modes {

    DUMP_MODE  = 1,
    GUESS_MODE = 2,
    DESCR_MODE = 3,
    DIFF_MODE  = 4,
};

int run_akinator(const char* filename);
void choose_mode(const char* filename, Tree* tree);
void save_changes(const Tree* tree, const char* filename);
int if_continue();

void guess_character(Node* node);
int add_new_character(Node* node);

int make_description(const Tree* tree);
int find_way(const char* object, Node* node, Stack* stack);
void print_description(const char* object, Node* node, Stack* stack);

int compare_objects(const Tree* tree);
int print_difference(const char* object1, const char* object2, Node* node, Stack* stk1, Stack* stk2);

Node* printh_characteristic(Stack* stk, Node* node, int beg_position, int end_position);

int print_question(const Node* node);
int get_ans(const char* answer);
int get_mode();
void clear_line();


#endif // AKINATORFUNCS_H_INCLUDED
