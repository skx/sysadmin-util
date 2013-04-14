/**
 * Run a program only if an exclusive lock may be obtained.
 *
 * The name of the lockfile is dynamically determined via
 * the user running the tool, and the command to be executed.
 *
 * NOTE: There will be an orphaned lockfile.  Is this a problem?
 *
 * Steve
 * --
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <fcntl.h>
#include <errno.h>
#include <openssl/sha.h>
#include <unistd.h>

/**
 * Build a fully-qualified filename for a suitable lockfile.
 *
 * The lockfile name must be based upon both the command to be executed
 * and the current user.  The latter is required so that two users could
 * both run "with-lock top".
 *
 */

char *
build_lock (int argc, char *argv[])
{
  char name[1024];
  char prefix[40];
  unsigned char hash[20];
  char hex_digest[50] = { '\0' };
  int i;
  SHA_CTX ctx;

  /**
   * Root and users will use different directory prefix.
   */
  if (getuid () == 0)
    sprintf (prefix, "/var/lock");
  else
    sprintf (prefix, "/var/tmp");


  /**
   * sum up the arguments.
   */
  SHA1_Init (&ctx);
  for (i = 0; i < argc; i++)
    SHA1_Update (&ctx, argv[i], strlen (argv[i]));


  /**
   * Make a hex-digest of the result.
   */
  SHA1_Final (hash, &ctx);
  for (i = 0; i < 20; i++)
    sprintf (hex_digest + strlen (hex_digest), "%02X", hash[i]);


  /**
   * Return the :  prefix + uid + hex-digest
   */
  snprintf (name, (sizeof name) - 1, "%s/%d.%s",
	    prefix, getuid (), hex_digest);
  return ((char *) strdup (name));
}



/**
 * Pretend we have flock, even though we're using fcntl.
 */
int
my_flock (int fd, int op)
{
  int rc = 0;

#if defined(F_SETLK) && defined(F_SETLKW)
  struct flock fl = { 0 };

  switch (op & (LOCK_EX | LOCK_SH | LOCK_UN))
    {
    case LOCK_EX:
      fl.l_type = F_WRLCK;
      break;

    case LOCK_SH:
      fl.l_type = F_RDLCK;
      break;

    case LOCK_UN:
      fl.l_type = F_UNLCK;
      break;

    default:
      errno = EINVAL;
      return -1;
    }

  fl.l_whence = SEEK_SET;
  rc = fcntl (fd, op & LOCK_NB ? F_SETLK : F_SETLKW, &fl);

  if (rc && (errno == EAGAIN))
    errno = EWOULDBLOCK;
#endif

  return rc;
}


/**
 * Try to get an exclusive lock on the given filename.
 *
 * If we succed return >0, otherwise return -1.
 */
int
get_lock (char *filename)
{
  int lockfd;

  if ((lockfd = open (filename, O_WRONLY | O_CREAT, 0600)) == -1)
    {
      fprintf (stderr, "open failed");
      return -1;
    }

  if (my_flock (lockfd, LOCK_EX | LOCK_NB) == -1 && errno == EWOULDBLOCK)
    {
      close (lockfd);
      return (-1);
    }

  return (lockfd);
}




/**
 * Entry point to the code.
 */
int
main (int argc, char *argv[])
{
  char *filename = NULL;

  if (argc <= 1)
    {
      fprintf (stderr, "Usage: %s program to execute\n", argv[0]);
      exit (-1);
    }

  /**
   * Build the lockfile.
   */
  filename = build_lock (argc, argv);

  /**
   * Try to get the lock.
   */
  int result = get_lock (filename);
  free (filename);

  /**
   * If we didn't get the lock abort.
   */
  if (result <= 0)
    {
      fprintf (stderr, "Failed to acquire the lockfile (%s).\n", filename);
      exit (1);
    }

  return (execvp (argv[1], argv + 1));
}
