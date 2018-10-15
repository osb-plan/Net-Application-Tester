
// System Header
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include <stdlib.h>
#include <signal.h>

#include <stdio.h>
#include <ctype.h>


// Application Specific Header
#include "data_defs.h"
#include "bsp.h"


static pthread_mutex_t log_mutex;


extern FILE *fptr_log;
extern int global_verbose_level;
/* timestamp support */

char* timestamp()
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    char *t = asctime( localtime(&ltime) ); 
    if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
    return t;
}

/* Function to log on file */
void plog(char *str, int verbose_level, int whocall)
{
    if(whocall == 0)
    {
        
    }
    
    if(verbose_level <= global_verbose_level && verbose_level >= 0)
    {
    pthread_mutex_lock(&log_mutex);
        fprintf(fptr_log, "%s: %s %d\n"
                , timestamp()
                , str
                , whocall);
        fflush(fptr_log);
    pthread_mutex_unlock(&log_mutex);         
    }    else{printf("mo stampo\n");}
}

void  SIGINThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
     {
        fclose(fptr_log);
        exit(EXIT_SUCCESS);         
     }
     else
          signal(SIGINT, SIGINThandler);

     getchar(); // Get new line character
}
