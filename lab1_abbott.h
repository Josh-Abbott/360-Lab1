#ifndef LAB1_H
#define LAB1_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>            
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "tree_node.h"
#include "mod_dir.h"
#include "read_dir.h"

FILE *file;
char *cmd[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm","reload","save","quit",0};

int find_commad(char *user_command);
void breakupPathName(int result, char *pathname);

#endif
