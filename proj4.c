
#include "proj4.h"
/*
 * author: Jefferson Vivanco
 * 
 * Note: Original shell code, was not written by me, it was written by Professor Klukowska 
 * 
 * FIXES FOR BUGS 1,2,3,4,5
 * 
 * 	BUG 1:  Fix Location: procline.c line 44
 * 			We changed the location of narg=0, from the bottom of the if statement (toktype==EOL) to the top of that if statement. We changed
 * 			it to the top because when it was on the botton, if toktype = EOL, narg would not get reset back to 0, so by putting it on top of 
 * 			the (toktype == EOL) if statement, we are resetting narg=0, whether (toktype = EOL) or not. We needed to reset narg back to zero after 
 * 			each complete argument because that is what the runcommand function takes in, if we didn't reset it back, we would always be passing the
 * 			arg array with the old arguments.
 * 
 *  BUG 2:  Fix Location: runcommand.c lines 16 - 51
 * 			The if statement (line 20) checks if the user the first arg the user entered is "cd". If it is equal to "cd" then inside that if statement, 
 * 			we have an if and else statement. The if statement checks if the user entered any other argument other than cd, if they didn't, using the
 * 			getenv function, we get the home directory and pass this to the chdir function. If they did, then it goes to the else statement, where we
 * 			do two more checks. We check if the second argument starts with a "/", if it does then that means this is a path name, in that case, we can
 * 			pass this pass directly to chdir, if they didn't then that means they passed a folder name. We know that chdir only takes paths, and if the 
 * 			user put in another argument after cd that is a folder, we know this is a subfolder of the current path. So, what we did is, we got the current
 * 			working directory, and then we save this to a string. We a "/" to it and then the folder name the user entered. And Voila, we have a path, 
 * 			we pass this directly to chdir and it takes us to that directory. Note: ".." , we treated like any folder name. 
 * 
 *  BUG 3:  Fix Location: runcommand.c lines 12-15
 * 			In runcommand, we have an if statement that checks if the user entered exit, if the user did, we simply call the exit function and the shell
 * 			terminates.
 * 
 *  BUG 4:  Fix Location: proj4.c, lines 45 and (lines 56-58); proj4.h line 47
 * 			Here we called the signal function and a handler. The signal function catches SIGINT and calls the handler. The handler blocks SIGINT from
 * 			getting to the handler and it instead goes to the child. The handler is empty because our only concern was to block it from the parent.
 * 			The signal automatically goes to all the child processes. In the proj4.h file, we just initilized the function so it can be used here.
 * 
 *  BUG 5:  Fix Location: runcommand.c line 74
 * 			The line wait(null) waits for any child process to terminate. This makes sure that when a child background process terminates, it is reaped. 
 * 
 * 
 * */

int main()
{

	signal(SIGINT, handler); //Bug 4 Fix, Here we are blocking the SIGINT signal, and we are passing it to the handler
    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput(  ) != EOF ) {
		
        procline();
              
    }
    return 0;
}

//Added function 
void handler(int sig){ //Bug 4 Fix, This is where we handle the SIGNINT signal
	//Empty
}
