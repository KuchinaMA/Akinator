#ifndef AKINATORFUNCS_H_INCLUDED
#define AKINATORFUNCS_H_INCLUDED

enum Modes {

    DUMP_MODE  = 1,
    GUESS_MODE = 2,
    DESCR_MODE = 3,
    DIFF_MODE  = 4,
};

int choose_mode();
int guess_character(Node* node);
int add_new_character(Node* node);
int print_description();


#endif // AKINATORFUNCS_H_INCLUDED
