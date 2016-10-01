#include "proj4.h"
/*
 * author: Jefferson Vivanco 
 * Note: Additions and changes are documented in proj4.c, only comments are here. 
 * */
// execute a command with optional wait

int runcommand(char **cline, int where) {
    pid_t pid;
    int status;

    if(strcmp(*cline, "exit")==0)//Bug 3 Fix (lines 12-15) If user enters exit, it exits the shell
    {
		exit(1);
	}
	if(strcmp(*cline, "cd") == 0)//If user enters cd, then there are a few more cases (bug 2 fix ,lines 16 - 51)
	{
		if(cline[1]==NULL){//If its only cd
			int ret; 
			const char *name = "HOME";
			char *value = getenv(name); //Getting path of home directory 
			
			if((ret = chdir(value)) == -1)//Passing it to chdir, which takes us to that directory. If it equals -1, then there was an error and the 
			{							  //it returns back to the shell 
				perror("ERROR"); 
				return;
			}		
		}
		else{
			char *direct; 
			if(*cline[1] == '/')//If the first char of what the user entered starts with a "/", then its a path, and we can just pass this whole path
			{					//to the chdir function 
				direct = cline[1];
			}
			else{//Its a folder name 
				getcwd(direct, MAXBUF);//Get current directory and added to the empty string "direct"
				strcat(direct, "/"); //adding a "/" to direct which contains the current directory path
				strcat(direct, cline[1]); //adding folder name to direct, therefore we have a complete path name and we can just pass this to chdir 
			}

			int ret;

			if((ret = chdir(direct)) == -1)//Calling chdir, if it equals -1, it means there was an error, and it returns back to the regular shell
			{
				perror("ERROR"); 
				return;
			}	
			
		}	
			
	}		
	else{
		switch(pid=fork()) {
			
			case -1:
				perror(SHELL_NAME);
				return (-1);
			case 0:
				execvp(*cline,cline);
				//we should never get to this code, since execve does not return
				perror(*cline);
				exit(1);
					
			}
			// code for parent
			// if background process print pid and exit
			// program is running in the background
		}

    if(where == BACKGROUND) {
        printf("[Process id %d]\n",pid);
		return (0);
    }
    wait(NULL);//Fix for bug 5, this waits for any child processes (even background) to terminate 
    
    // wait until process pid exits 
    if (waitpid(pid,&status,0) ==-1){//wait for child to terminate 
        return (-1);
	}
    else
        return (status);
	
}
