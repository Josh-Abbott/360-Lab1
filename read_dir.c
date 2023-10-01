#include "lab1_abbott.h"

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