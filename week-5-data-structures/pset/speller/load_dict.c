#include "dictionary.h"

int main(int argc, char *argv[])
{
    load(argv[1]);
    benchmark();
    unload();
}
