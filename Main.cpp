#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"
#include "TreeDump.h"
#include "AkinatorFuncs.h"

const char *DEFAULT_FILE = "TestData1.txt";

int main (int argc, const char *argv[]) {

    if (argc == 1)
        run_akinator(DEFAULT_FILE);

    else
        run_akinator(argv[1]);

    return 0;
}
