#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __unix__
#include <unistd.h>
#endif
#include <assert.h>
#include <errno.h>
#include <stdint.h>
   
typedef uint16_t uint16;
typedef uint8_t uint8;

struct Node {
    struct Node *north;
    struct Node *west;
    struct Leaf *east;
    uint8 path[256];
};

#endif // TREE_H
