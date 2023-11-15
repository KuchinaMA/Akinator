#include <stdio.h>
#include <strings.h>

#include "Tree.h"
#include "TreeDump.h"
#include "Types.h"
#include "Stack.h"
#include "AkinatorFuncs.h"


int choose_mode(char* filename) {

    FILE* database = fopen(filename, "r");
    Tree* tree = read_data(database);
    fclose(database);

    printf("Hello! It's an Akinator game. Look what I can do:\n");
    printf("1) Show the tree with objects and their characteristics; \n");
    printf("2) Guess an object; \n");
    printf("3) Make a description of an object; \n");
    printf("4) Show the difference between tho objects. \n\n");
    printf("Enter the number of the mode (without bracket) to start: ");

    int mode = 0;
    scanf("%d", &mode);

    switch (mode) {

        case DUMP_MODE: {
            graph_dump(tree);
            printf("Ready! You can see the picture in the corresponding folder\n\n");
            break;
        }

        case GUESS_MODE: {
            guess_character(tree->root);
            break;
        }

        case DESCR_MODE: {
            printf("Enter the object name in <>: ");
            char object[MAX_LINE_LEN] = "";
            get_line(stdin, object);
            make_description(object, tree);
            break;
        }


    }

    int changes = 0;
    printf("Do you want to save changes?\n");
    printf("Enter 1 for yes, 0 for no\n");
    scanf("%d", &changes);

    if (changes == 1) {
        FILE* output = fopen(filename, "w");
        print_node_pre(tree->root, output);
        fclose(output);
    }

    return 0;
}

int guess_character(Node* node) {

    printf("%s?\n", node->data);
    printf("Enter 1 for yes, 0 for no\n");
    int res = 0;
    scanf("%d", &res);

    if (node->left == 0 || node->right == 0) {

        if (res == 1)
            printf("Oh, just as I thought!\n\n");

        else
            add_new_character(node);

    }

    else {

        if (res == 1) {
            guess_character(node->left);
        }

        else if (res == 0) {
            guess_character(node->right);
        }
    }

    return 0;
}


int add_new_character(Node* node) {

    char new_character[MAX_LINE_LEN] = "";
    printf("Who is it?\n");
    printf("Please enter word in <>\n");
    get_line(stdin, new_character);
    Node* new_char = node_ctor(new_character, 0, 0);

    Node* old_char = node_ctor(node->data, 0, 0);

    printf("How does %s differ from %s?\n", new_char->data, node->data);
    printf("Please enter word in <> and don't use \"not\" or \"don't\"/\"doesn't\"\n");
    printf("It/he/she ");
    get_line(stdin, node->data);

    printf("Okay! I got it and I will win next time\n\n");

    node->left = new_char;
    node->right = old_char;

    return 0;
}


int make_description(char* object, const Tree* tree) {

    STACK_CONSTRUCT(stk, StackDefaultCapacity);
    //printf("%s\n", object);                       //отладка

    int res = find_way(object, tree->root, &stk);
    //printf("%d\n", res);                          //отладка
    //PRINT_STACK(&stk);                            //отладка

    if (res == 0)
        printf("Sorry! There's no such a character in my database\n\n");

    else
        print_description(object, tree->root, &stk);

    stack_dtor(&stk);
    return 0;
}

int find_way(char* object, Node* node, Stack* stack) {

    int is_found = 0;

        if (node == 0)
            return 0;

        if (strcmp(object, node->data) == 0)
            is_found = 1;

    if (is_found == 0) {

        stack_push(stack, 1);
        is_found = find_way(object, node->left, stack);
        //printf("FOUND %d\n", is_found);
        if (is_found == 0) {
            elem_t old = 0;
            stack_pop(stack, &old);
        }
    }

    if (is_found == 0) {

        stack_push(stack, 0);
        is_found = find_way(object, node->right, stack);
        //printf("FOUND %d\n", is_found);
        if (is_found == 0) {
            elem_t old = 0;
            stack_pop(stack, &old);
        }
    }

    return is_found;
}



void print_description(char* object, Node* node, Stack* stack) {

    printf("%s is ", object);

    for (int i = 0; i < stack->size; i++) {

        if (stack->data[i] == 0)
            printf("not ");

        if (i != stack->size - 1)
            printf("%s, ", node->data);
        else
            printf("%s. ", node->data);


        if (stack->data[i] == 0) {
            node = node->right;
            //printf("CURRENT %s\n", node->data);
        }
        else {
            node = node->left;
            //printf("CURRENT %s\n", node->data);
        }
    }



    printf("\n\n");
}







