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

int make_description(char* object, const Tree* tree);
int find_way(char* object, Node* node, Stack* stack);
void print_description(char* object, Node* node, Stack* stack);


#endif // AKINATORFUNCS_H_INCLUDED
