#include <stdio.h>
#include <strings.h>

#include "Tree.h"
#include "TreeDump.h"
#include "AkinatorFuncs.h"

int choose_mode() {

    FILE* database = fopen("HPData.txt", "r");
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
            printf("Ready! You can see the picture in the corresponding folder\n");
            break;
        }

        case GUESS_MODE: {
            guess_character(tree->root);
        }

    }

    int changes = 0;
    printf("Do you want to save changes?\n");
    printf("Enter 1 for yes, 0 for no\n");
    scanf("%d", &changes);

    if (changes == 1) {
        FILE* output = fopen("HPData.txt", "w");
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
            printf("Oh, just as I thought!\n");

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
    Node* new_char = node_ctor(new_character, 0, 0);
    printf("Who is it?\n");
    printf("Please enter word in <>\n");
    get_line(stdin, new_char);

    Node* old_char = node_ctor(node->data, 0, 0);

    printf("How does %s differ from %s?\n", new_char->data, node->data);
    printf("Please enter word in <> and don't use \"not\" or \"don't\"/\"doesn't\"\n");
    printf("It/he/she ");
    get_line(stdin, node);

    printf("Okay! I got it and I will win next time\n");

    node->left = new_char;
    node->right = old_char;

    return 0;
}




