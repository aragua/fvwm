/*
** System.c: code for dealing with various OS system call variants
*/

#include "config.h"
#include "System.h"

/*
** just in case...
*/
#ifndef FD_SETSIZE
#define FD_SETSIZE 2048
#endif

int GetFdWidth(void)
{
#if HAVE_SYSCONF
  return min(sysconf(_SC_OPEN_MAX),FD_SETSIZE);
#else
  return min(getdtablesize(),FD_SETSIZE);
#endif
}

#if HAVE_UNAME
/* define mygethostname() by using uname() */
int mygethostname(char *client, int length)
{
  struct utsname sysname;
  
  uname(&sysname);
  strncpy(client,sysname.nodename,length);
}
/* return a string indicating the OS type (i.e. "Linux", "SINIX-D", ... ) */
int mygetostype(char *buf, int max)
{
  struct utsname sysname;
  int ret;
  
  if ((ret = uname(&sysname)) == -1)
    strcpy (buf,"");
  else
    strncat (strcpy(buf,""), sysname.sysname, max);
  return ret;
}
#else 
#if HAVE_GETHOSTNAME
/* define mygethostname() by using gethostname() :-) */

int mygethostname(char *client, int length)
{
  gethostname(client, length);
}
#else
int mygethostname(char *client, int length)
{
  *client = 0;
}
#endif
int mygetostype(char *buf, int max)
{
  strcpy (buf,"");
  return -1;
}
#endif

