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

     $ multi-ping steve.org.uk
     Host steve.org.uk - 80.68.85.46 alive
     Host steve.org.uk - 2001:41c8:125:46:0:0:0:10 alive

Requirements:

 * The `Net::DNS` perl module.
 * The `ping` + `ping6` binaries.



mysql-slave-check
-----------------

If the current host is a MySQL slave this script will test that the
slave replication is still working.  It does this by looking for
the following two lines from the "SHOW SLAVE STATUS" output:

     Slave_IO_Running: Yes
     Slave_SQL_Runing: Yes

Example:

     # ./mysql-slave-check
The replication appears to show an error:

*************************** 1. row ***************************
                  Master_Host: da-db1
                  Master_User: slave
                  Master_Port: 3306
                Connect_Retry: 60
              Master_Log_File: mysql-bin.000124
          Read_Master_Log_Pos: 65667
               Relay_Log_File: relay-log.001139
                Relay_Log_Pos: 27251
        Relay_Master_Log_File: mysql-bin.000124
             Slave_IO_Running: No
            Slave_SQL_Running: No
            ..

The script exits silently if all is well, unless you add "`--verbose`":

     # ./mysql-slave-check -v
The slave is running, successfully.

Requirements:

 * There must be a file /etc/mysql/debian.cnf with valid "user=" and "password=" lines.



splay
-----

Sleep for a random amount of time, limited by the given max value.  (Default
is 5 minutes).

Example:

      $ ./splay -v
      Sleeping for 77 seconds from max splay-time of 300 seconds

      $ ./splay -v -m 20
      Sleeping for 7 seconds from max splay-time of 20 seconds



ssl-expiry-date
----------------

Report the date, and number of days, until the given SSL certificate expires.

Example:

        ./ssl-expiry-date bbc.co.uk
        Certificate presented at : bbc.co.uk
        Expires: Jun 18 13:50:58 2013 GMT  [63 days in the future]



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



Problems
--------

Please report any issue/suggestions via the github repository:

* https://github.com/skx/sysadmin-util



Author
------

Steve Kemp <steve@steve.org.uk>
