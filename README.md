sysadmin-utils
==============

A small collection of scripts that might be useful to sysadmins.


empty-dir
---------

Indicate, via return code, whether a given directory is empty or not.

Example:

    if ( empty-dir /etc ); then echo "We're broken" ; fi


multi-ping
----------

Ping a host, regardless of whether it is an IPv6 or IPv4 host.

Example:

     multi-ping steve.org.uk
     Host steve.org.uk - 80.68.85.46 alive
     Host steve.org.uk - 2001:41c8:125:46:0:0:0:10 alive

Requirements:

 * The `Net::DNS` perl module.
 * The `ping` + `ping6` binaries.


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
