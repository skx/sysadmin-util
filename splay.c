/*
 *  splay.c - Sleep for a random amount, no more than the stated max.
 *
 *  Name inspired by the splay-time of CFAgent.
 *
 */

#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void
show_usage (char *program)
{
  fprintf (stderr, "Usage: %s [-v] [-m MAX]\n", program);
  exit (2);
}


int
main (int argc, char *argv[])
{
  char c;
  int delay;
  int max = 60 * 5;
  int verbose = 0;

  while ((c = getopt (argc, argv, "vm:")) != -1)
    {
      switch (c)
	{
	case 'm':
	  max = atoi (optarg);
	  break;
	case 'v':
	  verbose = 1;
	  break;
	default:
	  show_usage (argv[0]);
	}
    }

  srand (time (NULL));
  delay = rand () % max;

  if (verbose)
    fprintf (stderr, "Sleeping for %d seconds from max splay-time of %d seconds\n", 
             delay, max);

  sleep (delay);
  exit (EXIT_SUCCESS);
}
