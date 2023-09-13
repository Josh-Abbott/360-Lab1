#ifndef LAB1_H
#define LAB1_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>            
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

typedef struct node {
	char  name[64];       // node's name string
	char  type;
	struct node *child, *sibling, *parent;
} NODE;

NODE *root; 
NODE *cwd;
char line[64], user_command[32], pathname[32], drname[32], bsename[32];
char *cmd[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm","reload","save","quit",0};

int initialize();
int find_commad(char *user_command);
NODE* makeNode(NODE* parentPtr, char type);
void breakupPathName(char *user_command, char *pathname);
NODE* searchdName(char *drname);
int checkName(NODE* curnode);
void mkdir(NODE *curnode);
NODE *find_node(NODE *pcur, char *pathname);
NODE *find_helper(NODE *pcur, char *target, char file_type);

#endif
