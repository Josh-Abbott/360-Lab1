#ifndef MODDIR_H
#define MODDIR_H

char line[64], user_command[32], pathname[32], drname[32], bsename[32];

void mkdir(NODE *temp);
void rmdir(NODE *temp);
void creat(NODE *temp);
void rm(NODE *temp);
void save();
void save_helper(NODE *currentnode, char *path);

#endif
