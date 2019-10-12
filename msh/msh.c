//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rudy Cruz 
// update: 10/2/2019
// Command Line msh

// Creating my own command line inspired by bash
// I will use the forking to create new process just expirmenting learning how 
// to use fork(). I will also use excevp() function to call a Linux command. I
// implamented a few new build in bash commannd for example the "cd" command. 
//  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define MAXSIZE 120

char* getMonth(char * token)
{
	if(!strcmp(token, "Jan"))
		return "01";
	else if(!strcmp(token, "Feb"))
		return "02";
	else if(!strcmp(token, "Mar"))
		return "03";
	else if(!strcmp(token, "Apr"))
		return "04";
	else if(!strcmp(token, "May"))
		return "05";
	else if(!strcmp(token, "Jun"))
		return "06";
	else if(!strcmp(token, "Jul"))
		return "07";
	else if(!strcmp(token, "Aug"))
		return "08";
	else if(!strcmp(token, "Sep"))
		return "09";
	else if(!strcmp(token, "Oct"))
		return "10";
	else if(!strcmp(token, "Nov"))
		return "11";
	else if(!strcmp(token, "Dec"))
		return "12";
}

void diffCases(char str[])
{


	// ** Checking for Input redirection (>) and output redirection (>) 
	char* outputRedi = strchr(str, '>');
	char* inputRedi = strchr(str, '<');
	char* inputFile = NULL;
	char* outputFile = NULL;

	int i = 0;
	char **args = (char**) calloc(10, sizeof(char*));

	if(!inputRedi && outputRedi) {
		char* token1  = strtok(str, " \n\t");
		int flagg = 0;
		int t = 0;
		char* temppp[100];
		// printf("Enter 3\n");
		while(token1 != NULL)
		{
			if(strcmp(strdup(token1), ">") == 0)
				flagg = 1;

			if(flagg == 0){
				args[t] = strdup(token1);
				t++;
			}
			temppp[i] = strdup(token1);
			i++;
			token1 = strtok(NULL, " \n\t");
		}
		
		temppp[i] = NULL;
		args[t] = NULL;
		outputFile = strdup(temppp[i-1]);
	}
	else if(outputRedi && inputRedi) {

		char* token1  = strtok(str, " \n\t");
		char* temppp[100];
		int flagg = 0;
		int t = 0;
		while(token1 != NULL)
		{
			if(strcmp(strdup(token1), "<") == 0){
				token1 = strtok(NULL, " \n\t");
				inputFile = strdup(token1);
				flagg = 1;
			}
			if(flagg == 0)
			{
				args[t] = strdup(token1);
				t++;
			}
			temppp[i] = strdup(token1);
			i++;
			token1 = strtok(NULL, " \n\t");
		}
		temppp[i] = NULL;
		args[t] = NULL;
		outputFile = strdup(temppp[i-1]);
	}
	else {
		char *token;
		// ** Allocating memory for args size 5
		token  = strtok(str, " \n\t");
		// ** Using loop to tokenize the string grabbed by fgets
		// ** also storeing the string tokens into args array   
		while(token != NULL)
		{

			args[i] = strdup(token);
			// printf("%s\n", args[i]);
			if(i == 10)
				break;
			i++;
			token  = strtok(NULL, " \n\t");
		}
		args[i] = NULL;
	}

	// printf("Input File: %s\n", inputFile);
	// printf("Output File: %s\n", outputFile);



	if(!strcmp(str , "exit"))
	{
		// printf("\n");
		exit(EXIT_SUCCESS);
	}
	else if(!strcmp(str , "help")) // checking if  word 'help' entered
	{
		printf("%s\n", "enter Linux commands, or 'exit' to exit" );
	} 
	else if(!strcmp(str , "today")) // if word equals 'today' print dd/mm/yyyy
	{
		time_t t = time(NULL);
		char * timePtr;
		timePtr = ctime(&t);

		if(timePtr == NULL)
		{
			printf( "Failed to convert the current time.\n" );
		}

		// printf("%s\n", timePtr);
		char *str[4];
		str[4] = NULL;

		char *token = strtok(timePtr, " \t\n");
		int k = 0;
		while(token != NULL)
		{

			// printf("Word = %s\n", token);
			if(k == 1)
			{
				str[0] = getMonth(token);
			}
			if(k  == 2)
			{
				str[1] = token;
			}
			if(k == 4)
			{
				str[2] = token;
			}
			k++;
			token  = strtok(NULL, " \t\n");
		}
		
		printf("%s/%s/%s\n",str[0], str[1],str[2] );
	}
	else if (!strcmp(str , "pwd"))
	{
		char s[100];
		printf("%s\n" , getcwd(s, 100));
	}
	else if(!strcmp(args[0] , "cd"))
	{
		// printf("%d\n", i);

		if(i == 1)
		{
			const char* home = getenv("HOME");
			if(chdir(home))
			{
				printf("msh: cd: No such file or directory\n");
			}
		}
		else if(chdir(strdup(args[1])) != 0)
		{
			printf("msh: cd: No such file or directory\n");
		}
	}
	else
	{	
		// print("%s", str);
		// ** Forking to excevp to do linux commands entered 
		int rc = fork();
		if (rc < 0) { // fork failed; exit
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) { // child (new process)
			// printf("hello, I am child (pid:%d)\n", (int) getpid());
			// printf("Input File: %s\n", inputFile);
			// printf("Output File: %s\n", outputFile);

			if(!inputRedi && outputRedi){
				// printf("Enter 1\n");
				FILE *fp1;
				fp1 = fopen(outputFile, "w");
				int out;
				out = fileno(fp1);
				dup2(out, 1);
				
			}
			if(outputRedi && inputRedi) {
				// printf("Enter 2\n");
				FILE *fp2, *fp1;
				fp2 = fopen(inputFile, "r");
				fp1 = fopen(outputFile, "w");

				int out, out2;
				out = fileno(fp2);
				out2 = fileno(fp1);
				dup2(out, 0);
				dup2(out2, 1);
			}

			int check = execvp(args[0], args);
			// printf("Check =  %d\n", check);
			if(check < 0)
				printf("msh: %s: No such file or directory\n", args[0]);
			return;

		} else { // parent goes down this path (main)
			// printf("%s\n", "Parent is here" );
			int rc_wait = wait(NULL);
		}
	}
}

int main(int argc, char *argv[])
{

	char str[MAXSIZE+2];
	static const char prompt[] = "msh> ";

	if(argc > 1)
	{
		FILE *fp;
		// printf("%s\n", argv[0]);
		fp = fopen(argv[1], "r");

		if(!fp)
		{
			perror("Error opening file");
		}

		while(fgets(str, MAXSIZE, fp) != NULL)
		{
			diffCases(str);
		}
	}
	else
	{
		while(1)
		{	
			if(isatty(fileno(stdin)))
			{
				printf(prompt);
			}
			
			// printf("msh> ");
			char *status  = fgets(str, MAXSIZE, stdin);
			if(status == NULL )
			{
				printf("\n");
				exit(EXIT_SUCCESS);
			}
			diffCases(str);
		}
	}


	return 0;
}
