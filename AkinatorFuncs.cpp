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

    printf("Hello! It's an Akinator game. Look what I can do:\n"
    "1) Show the tree with objects and their characteristics; \n"
    "2) Guess an object; \n"
    "3) Make a description of an object; \n"
    "4) Show the difference between tho objects. \n\n"
    "Enter the number of the mode (without bracket) to start: ");

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
            make_description(tree);
            break;
        }

        case DIFF_MODE: {
            compare_objects(tree);
            break;
        }

        default:
            printf("Incorrect mode:(\n\n");
    }

    printf("Do you want to save changes?\n"
    "Enter yes/no: ");

    char changes[MAX_LINE_LEN] = "";
    scanf("%s", changes);

    if (strcmp(changes, "yes") == 0) {
        FILE* output = fopen(filename, "w");
        print_node_pre(tree->root, output);
        fclose(output);
    }

    return 0;
}

int guess_character(Node* node) {

    printf("%s?\n"
    "Enter yes/no: ", node->data);

    char answer[MAX_LINE_LEN] = "";
    scanf("%s", answer);
    int res = 0;

    if (strcmp(answer, "yes") == 0)
        res = 1;
    else if (strcmp(answer, "yes") == 0)
        res = 0;

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
    printf("Who is it?\n"
    "Please enter word in <>\n");
    get_line(stdin, new_character);
    Node* new_char = node_ctor(new_character, 0, 0);

    Node* old_char = node_ctor(node->data, 0, 0);

    printf("How does %s differ from %s?\n"
    "Please enter word in <> and don't use \"not\" or \"don't\"/\"doesn't\"\n"
    "It/he/she ", new_char->data, node->data);
    get_line(stdin, node->data);

    printf("Okay! I got it and I will win next time hehehe\n\n");

    node->left = new_char;
    node->right = old_char;

    return 0;
}


int make_description(const Tree* tree) {

    printf("Enter the object name in <>: ");
    char object[MAX_LINE_LEN] = "";
    get_line(stdin, object);

    STACK_CONSTRUCT(stk, StackDefaultCapacity);

    int res = find_way(object, tree->root, &stk);

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

        if (is_found == 0) {
            elem_t old = 0;
            stack_pop(stack, &old);
        }
    }

    if (is_found == 0) {

        stack_push(stack, 0);
        is_found = find_way(object, node->right, stack);

        if (is_found == 0) {
            elem_t old = 0;
            stack_pop(stack, &old);
        }
    }

    return is_found;
}



void print_description(char* object, Node* node, Stack* stack) {

    printf("%s is ", object);

    printh_characteristic(stack, node, 0, stack->size);

    printf("\n\n");
}


int compare_objects(const Tree* tree) {

    printf("Enter the first object name in <>: ");
    char object1[MAX_LINE_LEN] = "";
    get_line(stdin, object1);

    STACK_CONSTRUCT(stk1, StackDefaultCapacity);

    int res1 = find_way(object1, tree->root, &stk1);
    if (res1 == 0) {
        printf("Sorry! There's character %s in my database\n\n", object1);
        return 1;       //по-хорошему какая-то ошибка или дать ввести ещё раз
    }


    printf("Enter the second object name in <>: ");
    char object2[MAX_LINE_LEN] = "";
    get_line(stdin, object2);

    STACK_CONSTRUCT(stk2, StackDefaultCapacity);

    int res2 = find_way(object2, tree->root, &stk2);
    if (res2 == 0) {
        printf("Sorry! There's character %s in my database\n\n", object2);
        return 1;      //то же самое что и несколькими строчками выше
    }

    print_difference(object1, object2, tree->root, &stk1, &stk2);

    printf("\n\n");

    stack_dtor(&stk1);
    stack_dtor(&stk2);
    return 0;
}



int print_difference(char* object1, char* object2, Node* node, Stack* stk1, Stack* stk2) {

    printf("%s and %s are both ", object1, object2);

    int position = 0;

    while (stk1->data[position] == stk2->data[position]) //считаем количество совпадений
        position++;

    int last_similar = position;

    Node* last_node = printh_characteristic(stk1, node, 0, last_similar);  //последний совпадающий признак

    printf("But %s is ", object1);
    printh_characteristic(stk1, last_node, last_similar, stk1->size);

    printf("And %s is ", object2);
    printh_characteristic(stk2, last_node, last_similar, stk2->size);

    return 0;
}



Node* printh_characteristic(Stack* stk, Node* node, int beg_position, int end_position) {

    int position = beg_position;

    while(position < end_position) {

        if (stk->data[position] == 0)
            printf("not ");

        if (position == end_position - 1)
            printf("%s. ", node->data);

        else
            printf("%s, ", node->data);

        if (stk->data[position] == 0)
            node = node->right;

        else
            node = node->left;

        position++;
    }
    return node;
}














