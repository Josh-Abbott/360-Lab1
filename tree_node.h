#ifndef TREENODE_H
#define TREENODE_H

typedef struct node {
	char  name[64];       // node's name string
	char  type;
	struct node *child, *sibling, *parent;
} NODE;

NODE *root; 
NODE *cwd;

void initialize();
NODE* makeNode(char type);
int checkExist(NODE** prevnode, NODE** curnode, char file_type);

#endif