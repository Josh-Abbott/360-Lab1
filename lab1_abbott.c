#include "lab1_abbott.h"

int initialize() {
	root = (NODE *)malloc(sizeof(NODE));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = 0;
	root->child = 0;
	root->type = 'D';
	cwd = root;
	printf("Filesystem initialized!\n");
}

int find_commad(char *user_command)
{
	int i = 0;
	while(cmd[i]){
		if (strcmp(user_command, cmd[i])==0)
		return i;
		i++;
	}
	return -1;
}

int main() {
	initialize();
	
	while(1) {
		printf("Enter command: ");
		scanf(" %[^\n]", line);
		sscanf(line, "%s %s", user_command, pathname);

		int result = find_commad(user_command);
		if (result != -1)
		{
			if (result == 0) breakupPathName(user_command, pathname);
			if (result == 1) break;
			if (result == 2) break;
			if (result == 3) break;
			if (result == 4) break;
			if (result == 5) break;
			if (result == 6) break;
			if (result == 7) break;
			if (result == 8) break;
			if (result == 9) break;
		}
		else
		{
			printf("Command not found!\n");
		}
	}
}

NODE* makeNode(NODE* parentPtr, char type)
{
   NODE* pTemp = malloc(sizeof(NODE));
   if (pTemp != NULL)
   {
        strcpy(pTemp->name, bsename);
        pTemp->type = type;
        pTemp->parent = parentPtr;
        pTemp->sibling = NULL;
        pTemp->child = NULL;
        return pTemp;
   }
   else
   {
        return NULL;
   }
}

void breakupPathName(char *user_command, char *pathname)
{
    if (strcmp(pathname, "") != 0)
    {
		NODE *curnode = NULL;
        char newpath[64];        
        strcpy(newpath, pathname);
        
        strcpy(drname, dirname(newpath));
        strcpy(newpath, pathname);
        strcpy(bsename, basename(newpath));        

		curnode = searchdName(drname);
		if (curnode == NULL)
		{
			printf("uh oh");
		}
		if (curnode && curnode->type != 'D')
		{
			printf("THROUGH P1");
			if (checkName(curnode) != 0)
			{
				mkdir(curnode);
			}
		}
    }
    else
    {
        printf("ERROR: Did not define a pathname!\n");
    }
}

void mkdir(NODE *curnode)
{
	NODE *temp = NULL;
	temp = makeNode(curnode, 'D');
   	if (temp)
	{
		if(curnode->child)
   		{
      	curnode = curnode->child;
      	while(curnode->sibling)
      	{
        	curnode = curnode->sibling;
      	}
      	curnode->sibling = temp;
   		}
   		else
   		{
      		curnode->child = temp;
   		}
	}
}

int checkName(NODE* curnode)
{
	curnode = curnode->child;
   	while(curnode)
   	{
     	 if(strcmp(curnode->name, bsename) == 0)
      	{
        	 printf("ERROR: This directory already exists!\n");
        	 return 0;
      	}
      	curnode = curnode->sibling;
   }
}

NODE* searchdName(char *drname)
{
    NODE *temp;
	char *string;
    if (drname[0]== '/') // abs path, start at root
    {
		if (root->child)
		{
			printf("ueaahds");
		}
        temp = root;
    }
    else // relative path
    {
		printf(cwd->name);
        temp = cwd;
    }

	int j, found;
	string = strtok(drname, "/");

	while(string)
   	{
		printf("while");
		j = 0;
	   	found = 0;
      	temp = temp->child;
		if(!temp)
		{
			printf("No temp");
			return NULL;
		} 
		do{
			if(strcmp(temp->name, string) == 0)
			{
				found = 1;
				printf("yay we found it\n");
			}
			else
			{
				temp = temp->sibling;
			}
		}
		while(!found && temp != NULL);
		if(!found)
		{
			printf("no found");
			return NULL;
		}   
		string = NULL;
		string = strtok(NULL, "/");
		//printf("str = %s\n", str); // For testing
	}
   	return temp;
}
