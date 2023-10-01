#include "lab1_abbott.h"

void mkdir(NODE *temp)
{
	NODE *prevnode = NULL, *curnode = temp->child;
	int result = checkExist(&prevnode, &curnode, 'D');
	if (result == 0)
	{
		NODE *newDir = makeNode('D');
		newDir->parent = temp;
		if (prevnode) 
		{
			prevnode->sibling = newDir;
		}
		else 
		{
			temp->child = newDir;
		}
	}
	else
	{
		printf("ERROR: DIR %s already exists!\n", bsename);
	}
}

void rmdir(NODE *temp)
{
	NODE *prevnode = NULL, *curnode = temp->child;
	int result = checkExist(&prevnode, &curnode, 'D');
	if (result == 1)
	{
		if(curnode->type == 'D' && !strcmp(curnode->name, bsename))
		{
			if(curnode->child){
				printf("ERROR: Cannot remove DIR %s (not empty)\n", bsename);
				return;
			}
			else if (curnode == temp->child)
			{ 
				temp->child = curnode->sibling; 
			}
			else if(prevnode)
			{ 
				prevnode->sibling = curnode->sibling; 
			}
			free(curnode);
			return;
		}
		prevnode = curnode;
		curnode = curnode->sibling;
	}
	else
	{
		printf("ERROR: DIR %s does not exist!\n", bsename);
	}
}

void creat(NODE *temp)
{

	NODE *prevnode = NULL, *curnode = temp->child;
	int result = checkExist(&prevnode, &curnode, 'F');
	if (result == 0)
	{
		NODE *newDir = makeNode('F');
		newDir->parent = temp;
		if (prevnode) 
		{
			prevnode->sibling = newDir;
		}
		else 
		{
			temp->child = newDir;
		}
	}
	else
	{
		printf("ERROR: FILE %s already exists!\n", bsename);
	}
}

void rm(NODE *temp)
{
	NODE *prevnode = NULL, *curnode = temp->child;
	int result = checkExist(&prevnode, &curnode, 'F');
	if (result == 1)
	{
		if(curnode->type == 'F' && !strcmp(curnode->name, bsename))
		{
			if (curnode == temp->child)
			{ 
				temp->child = curnode->sibling; 
			}
			else if(prevnode)
			{ 
				prevnode->sibling = curnode->sibling; 
			}
			free(curnode);
			return;
		}
		prevnode = curnode;
		curnode = curnode->sibling;
	}
	else
	{
		printf("ERROR: FILE %s does not exist!\n", bsename);
	}
}

void save()
{
	file = fopen("treefile.txt", "w+");   

	if(file)
	{
		save_helper(root->child, "");
	}
	
	fclose(file);
}

void save_helper(NODE *currentnode, char *path)
{
	if (currentnode)
	{
		char currP[64];
		strcpy(currP, path);
		strcat(currP, "/"); 
		strcat(currP, currentnode->name);
		fprintf(file, "%c %s\n", currentnode->type, currP);
		if(currentnode->child)
		{ 
			save_helper(currentnode->child, currP); 
		}
		if(currentnode->sibling)
		{ 
			save_helper(currentnode->sibling, path);
		}
	}
}