#include <stdio.h>
#include <stdlib.h>

#include "global.h"

void assert(int expr, char* msg)
{
    if (!expr) {
        perror(msg);
        fprintf(stderr, "File: %s\nFunc: %s\nLine: %d\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }    
}