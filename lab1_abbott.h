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
FILE *file;
char line[64], user_command[32], pathname[32], drname[32], bsename[32];
char *cmd[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm","reload","save","quit",0};

int initialize();
int find_commad(char *user_command);
NODE* makeNode(char type);
void breakupPathName(int result, char *pathname);
void mkdir(NODE *temp);
void rmdir(NODE *temp);
int checkExist(NODE** prevnode, NODE** curnode, char file_type);
void pwd();
void pwd_helper(NODE *node);
void ls();
void cd();
NODE *cd_helper(NODE *pcur, char file_type);
void creat(NODE *temp);
void rm(NODE *temp);
void save_helper(NODE *currentnode, char *path);

#endif
