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

int choose_mode(char* filename);

int guess_character(Node* node);
int add_new_character(Node* node);

int make_description(const Tree* tree);
int find_way(char* object, Node* node, Stack* stack);
void print_description(char* object, Node* node, Stack* stack);

int compare_objects(const Tree* tree);
int print_difference(char* object1, char* object2, Node* node, Stack* stk1, Stack* stk2);


Node* printh_characteristic(Stack* stk, Node* node, int beg_position, int end_position);


#endif // AKINATORFUNCS_H_INCLUDED
