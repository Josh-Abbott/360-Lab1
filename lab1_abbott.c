#include "tree.h"
#include "mkdir.h"

char *cmd[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm","reload","save","quit"};

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
	// other initialization as needed
	char user_command[15];

	while(1) {
		printf("Enter command: ");
		scanf("%s", user_command);

		int result = find_commad(user_command);
		if (result != -1)
		{
			if (result == 0) breakupPathName();
			if (result == 9) break;
		}
		else
		{
			printf("Command not found!\n");
		}
	}
}

