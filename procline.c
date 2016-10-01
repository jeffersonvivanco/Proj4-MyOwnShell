
#include "proj4.h"

/*
 * author: Jefferson Vivanco
 * Note: Additions and changes are documented in proj4.c, only comments are here. 
 * */
/* shell input line */
int procline(void)
{
	
    char *arg[MAXARG + 1];  //pointer array for runcommand
    int toktype;        // type of token in command
    int narg ;          // number of arguments so far
    int type;           //type =  FOREGROUND or BACKGROUND


    while ( 1 ) // loop forever
    {
		
        // take action according to token type
        switch(toktype = gettok(&arg[narg]))   
        {
        case ARG:
            if(narg<MAXARG){
                narg++;
			}
            break;

        case EOL:
        case SEMICOLON:
        case AMPERSAND:
            if(toktype == AMPERSAND)
                type = BACKGROUND;
            else
                type = FOREGROUND;
			
			
            if(narg != 0)
            {
                arg[narg] = 0;
                runcommand(arg,type);
            }
			narg = 0;//Moved narg=0 to here (Fixing Bug 1) So it can reset narg=0, so we can set new args in the arg array so it can pass each
					//argument that user entered individually to runcommand
            if( toktype == EOL ){
                return;
			}
			
            break;
            
        }
               
    }
    
}
