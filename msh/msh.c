#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define MAXSIZE 120

char * getMonth(char * token)
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


int main(int argc, char *argv[])
{

	if(argc > 0)
	{
		FILE *fp;
		fp = fopen(argv[0], "r");
		if(!fp)
		{
			perror("Error opening file");
		}

		char* line = fgets(str, MAXSIZE, fp);


	}

	// printf("%d\n",size_argv);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// int main(int argc, char *argv[])
// {

	

// 	while(1)
// 	{	
// 		char str[MAXSIZE+2];



// 		printf("msh> ");

// 		printf("String  = %s\n", str);
// 		//checking ig the fgets returns null if it does means its ctrl-d
// 		if(line == NULL)
// 			exit(1);
// 		//checking if string is longer then 120 characters
					
// 		fclose(fp);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	

	while(1)
	{	
		char str[MAXSIZE+2];
		printf("msh> ");
		char* line = fgets(str, MAXSIZE, stdin);
		//checking ig the fgets returns null if it does means its ctrl-d
		if(line == NULL)
			exit(1);
		//checking if string is longer then 120 characters
					

		if(str[strlen(str)-1] != '\n')
		{
			printf("%s\n", "error:input too long");
			while((getchar()) != '\n') {

			};
			continue;
		}
		
		char *token;
		// ** Allocating memory for args size 5
		char **args = (char**) calloc(5, sizeof(char*));
		token  = strtok(str, " \n\t");

		// ** Using loop to tokenize the string grabbed by fgets
		// ** also storeing the string tokens into args array  
		int i = 0; 
		while(token != NULL)
		{

			args[i] = strdup(token);
			if(i == 5)
				break;
			i++;
			token  = strtok(NULL, " \n\t");
		}
		args[i] = NULL;

		// printf("%s\n", "Hello" );
		//checkig if the string equals exit 
		if(!strcmp(str , "exit"))
		{
			exit(1);
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
			// char* token2 = strtok(str , " ");
			// printf("%s\n", strdup(args[1]) );

			if(chdir(strdup(args[1])) != 0)
			{
				perror("msh: cd");
			}
		}
		else
		{

			// ** Forking to excevp to do linux commands entered 
			int rc = fork();
			if (rc < 0) { // fork failed; exit
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (rc == 0) { // child (new process)
				// printf("hello, I am child (pid:%d)\n", (int) getpid());
				int check = execvp(args[0], args);
				// printf("Check =  %d\n", check);
				if(check < 0)
					printf("msh: %s: No such file or directory\n", args[0]);
				break;

			} else { // parent goes down this path (main)
				// printf("%s\n", "Parent is here" );
				int rc_wait = wait(NULL);
			}
		}

	}

	return 0;
}

