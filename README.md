sysadmin-utils
==============

A small collection of scripts that might be useful to sysadmins.


with-lock
---------

Run a command, unless an existing copy of that command is already running,
via the creation of a temporary lockfile.

For example:

     with-lock rsync ...

The lockfile-name is based upon the SHA1 hash of the command to
be executed and the current User-ID.

Existing alternatives:

 * lckdo - Requires you to build your own lockfile name
 * flock - Requires you to build your own lockfile name

Issues:

 * The lockfile is orphaned.



Problems
--------

Please report any issue/suggestions via the github repository:

* https://github.com/skx/sysadmin-util


Author
------

Steve Kemp <steve@steve.org.uk>
