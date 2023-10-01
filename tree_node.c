#include "lab1_abbott.h"

void initialize() {
	root = (NODE *)malloc(sizeof(NODE));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = 0;
	root->child = 0;
	root->type = 'D';
	cwd = root;
	printf("Filesystem initialized!\n");
}

NODE* makeNode(char type)
{
   NODE* pTemp = malloc(sizeof(NODE));
   if (pTemp != NULL)
   {
        strcpy(pTemp->name, bsename);
        pTemp->type = type;
        pTemp->parent = NULL;
        pTemp->sibling = NULL;
        pTemp->child = NULL;
        return pTemp;
   }
   else
   {
        return NULL;
   }
}

int checkExist(NODE** prevnode, NODE** curnode, char file_type)
{
	while(*curnode)
	{
		if((*curnode)->type == file_type && !strcmp((*curnode)->name, bsename))
		{
			return 1;
		}
		*prevnode = *curnode;
		*curnode = (*curnode)->sibling;
	}
	return 0;
}