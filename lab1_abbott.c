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
		strcpy(user_command, "");
		strcpy(pathname, "");
		printf("Enter command: ");
		scanf(" %[^\n]", line);
		sscanf(line, "%s %s", user_command, pathname);

		int result = find_commad(user_command);
		if (result != -1)
		{
			if (result == 0) breakupPathName(result, pathname);
			if (result == 1) breakupPathName(result, pathname);
			if (result == 2) ls();
			if (result == 3) cd();
			if (result == 4) pwd();
			if (result == 5) breakupPathName(result, pathname);
			if (result == 6) breakupPathName(result, pathname);
			if (result == 7) reload();
			if (result == 8) save();
			if (result == 9)
			{
				save();
				break;
			}
		}
		else
		{
			printf("ERROR: Command %s not found!\n", user_command);
		}
	}
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

void breakupPathName(int result, char *pathname)
{
    if (strcmp(pathname, "") != 0)
    {
        char newpath[64];        
        strcpy(newpath, pathname);
        
        strcpy(drname, dirname(newpath));
        strcpy(newpath, pathname);
        strcpy(bsename, basename(newpath));     

		NODE *temp = NULL;
		if (drname[0]== '/') // abs path, start at root
		{
			temp = root;
		}
		else // relative path
		{
			temp = cwd;
		}   

		if (result == 0)
		{
			mkdir(temp);
		}
		else if (result == 1)
		{
			rmdir(temp);
		}
		else if (result == 5)
		{
			creat(temp);
		}
		else if (result == 6)
		{
			rm(temp);
		}
    }
    else
    {
        printf("ERROR: Did not define a pathname!\n");
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

void pwd()
{
	printf("   ");
  	pwd_helper(cwd);
  	printf("\n");
}

void pwd_helper(NODE *node)
{
  	if(strcmp(node->name, "/"))
  	{
    	pwd_helper(node->parent);
    	printf("%s/", node->name);
  	}
  	else printf("%s", node->name);
}

void ls(){
    NODE * temp;
    if(!strcmp(pathname, "")){
        temp = cwd;
    }
    else
	{
		if (drname[0]== '/')
		{ 
			if(!strcmp(drname, "/") )
			{
				temp = root;
			}
		}
	}

    temp = temp->child;
    while(temp)
	{
        printf("%c %s\n", temp->type, temp->name);
        temp = temp->sibling;
    }
}

NODE *cd_helper(NODE *currentnode, char file_type){
    if(currentnode == NULL)
	{
        printf("No such file or directory: %s\n", bsename);
        return currentnode;
    }
    else if(!strcmp(currentnode->name, bsename) && currentnode->type == file_type)
	{
		return currentnode;
    }
    else{
        return cd_helper(currentnode->sibling, file_type);
    }
} 

void cd()
{
	NODE * temp;
    char newpath[64];        
	strcpy(newpath, pathname);
	
	strcpy(drname, dirname(newpath));
	strcpy(newpath, pathname);
	strcpy(bsename, basename(newpath));  

    if(pathname != NULL)
	{
        if (drname[0]== '/')
		{
			if (!strcmp(drname, "/"))
			{
				temp = root;
			}
		}
		else{
			if (!strcmp(drname, "."))
			{
				temp = cwd;
			}
			else if(!strcmp(drname, ".."))
			{
				temp = cwd->parent;
			}
		}
        if (!strcmp(bsename, ".."))
		{
            if (temp->parent)
			{
                temp = temp->parent;
            }
        }
		else if ((strcmp(drname, ".") == 0 && (strcmp(bsename, ".") == 0)))
		{
			temp = root;
		}
        else
		{
            temp = cd_helper(temp->child, 'D');
        }
    }
    else
	{
        return;
    }
    cwd = temp;
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

void reload()
{
	file = fopen("treefile.txt", "r");
	if (file)
	{
		char line[128];
		initialize();
		while(fgets(line, 128, file))
		{
			line[strlen(line)-1] = 0;
			char type[2], path[64], *command;
			sscanf(line, "%s %s", type, path);
			if(type[0] == 'D')
			{ 
				breakupPathName(0, path);
			}
			else if (type[0] == 'F')
			{
				breakupPathName(5, path);
			}
			cwd = root;
		}
	}
	fclose(file);
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