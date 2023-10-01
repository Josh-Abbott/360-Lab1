#include "lab1_abbott.h"

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