#ifndef TREE_H
#define TREE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>            
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char  name[64];       // node's name string
	char  type;
	struct node *child, *sibling, *parent;
} NODE;

NODE *root; 
NODE *cwd;

int initialize();

#endif
