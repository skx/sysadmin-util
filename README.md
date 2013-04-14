
sysadmin-utils
--------------

A small collection of scripts that might be useful to sysadmins.


with-lock
---------

Run a command, unless an existing copy of that command is already present.
For example:

     with-lock rsync ...

A file is created as a lockfile, based upon the SHA1 hash of the command to
be executed and the current User-ID.

Existing alternatives:

 * lckdo - Requires you to build your own lockfile name
 * flock - Requires you to build your own lockfile name



Steve
-- 