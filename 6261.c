#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<stdbool.h>
#include<signal.h>

#define CommandList 64

//function to handle signal and write to the log file
void signal_handler()
{
 FILE * fPtr;
 fPtr = fopen("logfile.txt", "a");

//if error occured during opening the file the system will exit
    if(fPtr == NULL)
    {
        printf("\n\t\tUnable to create file!!\n");
        exit(0);
    }

 //writing data into the file
    fputs("Child process was terminated\n", fPtr);

//closing file
fclose(fPtr);
}

//function to print the current directory
void PrintDirectory()
{
    char Directory[1024];
    getcwd(Directory, sizeof(Directory));
    printf("\nCurrent working directory: %s", Directory);
}

//function to get the input from the user
int UserInput(char* string)
{
	char*token;
	token = readline("\n>> ");

// if the user enter any string it will be copied to the string array
	if (strlen(token) != 0) {
		strcpy(string,token);
		return 0;
	} else {
		return 1;
	}
}

//function to remove space from the string and put every word in a place in a new array
int Space(char* str, char** UserCommands)
{
	int i;

//for loop to take the string and divide it
	for (i = 0; i < CommandList; i++)
	{
	UserCommands[i] = strsep(&str, " ");
		if (UserCommands[i] == NULL)
			break;
		if (strlen(UserCommands[i]) == 0)
			i--;
	}
	return i;
}

//function to process the string, execute it if is built-in function
int processString(char* string, char** UserCommands)
{
// i is to know number of words entered by the user
	int i =Space(string, UserCommands);

//if the user enter exit the sheell will be closed
	if (strcasecmp(UserCommands[0],"exit")==0)
	{
		printf("\n\t\tShell Closed\n");
		exit(0);
	}

//if the user enter cd it will take the word after it and will change directory
	else if(strcasecmp(UserCommands[0],"cd")==0)
	{
		chdir(UserCommands[1]);
		return 0;
	}

//if the user enter hello it will print the username
	else if(strcasecmp(UserCommands[0],"hello")==0)
	{
		char* username = getenv("USER");
		printf("\n\t\tHello %s.\n",username);
			return 0;
	}

//will search if the last word in the array is &  or not
	else if(strcmp(UserCommands[i-1],"&")==0)
	{
		UserCommands[i-1]=NULL;
		return 2;
	}
	else
		return 1;
}

//function to execute if the command entered is not one of the built-in functions
void execute(char** UserCommands,bool and)
{

// Forking a child
	pid_t pid = fork();

//if fork() returned -ve value this means that child forking has failed
	if (pid < 0) {
		printf("\n\tchild forking process Failed!!");
		return;
	}

//if fork() returned 0 this means that child forking has done correctly
	else if (pid == 0) {
		if (execvp(UserCommands[0], UserCommands) < 0) {
			printf("\n\terror executing this command!!");
		}
		exit(0);
	}
	else
	{
	signal(SIGCHLD,signal_handler);

//if there is no & the parent wait until child process is done
		if (and == 0)
		{
			wait(NULL);
			return;
		}

//if there is  & the parent will not wait until child process is done
		else if (and == 1)
		{
			return;
		}
	}
}

int main()
{
 	char inputString[1024];
 	char* UserCommands[CommandList];
	int flag = 0;
	bool and=0;

	while (1) {
		PrintDirectory();
		if (UserInput(inputString)!=0)
			continue;

		flag = processString(inputString,UserCommands);
		if (flag == 1)
			execute(UserCommands,0);

		if (flag == 2)
			execute(UserCommands,1);
	}
	return 0;
}
