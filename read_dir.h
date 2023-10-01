#ifndef READDIR_H
#define READDIR_H

void pwd();
void pwd_helper(NODE *node);
void ls();
void reload();
void cd();
NODE *cd_helper(NODE *pcur, char file_type);

#endif