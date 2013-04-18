sysadmin-utils
==============

A small collection of scripts that might be useful to sysadmins.



empty-dir
---------

Indicate, via return code, whether a given directory is empty or not.

Example:

    if empty-dir /etc; then echo "We're broken" ; fi



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
slave replication is still working.

Replication is regarded as being OK if the following three conditions
are true:

* The output of "SHOW SLAVE STATUS" includes: Slave_IO_Running: Yes
* The output of "SHOW SLAVE STATUS" includes: Slave_SQL_Runing: Yes
* The slave is less than 24 hours behind the master.

Example:

     # ./mysql-slave-check
     The replication appears to show an error:
     ..
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
     Replication lag: 0 seconds


Requirements:

 * There must be a file /etc/mysql/debian.cnf with valid "user=" and "password=" lines.



randpass
--------

Generate a single random password via `/dev/urandom`.

Example:

      $ ./randpass
      cT3j7Zp6
      $ ./randpass -n 10
      ulHrNvYLaa
      $ ./randpass -n 20 -f
      oe[d7+e.{Uw=L'RO~[]{

(Adding "-f" uses the full alphabet of possible symbols, otherwise only
alpha-numeric values are shown.  "-n" sets the length of the generated
password.)

Existing alternatives:

* apg
* gpw
* pwgen
* ...



splay
-----

Sleep for a random amount of time, limited by the given max value.  (Default
is 5 minutes).

Example:

      $ ./splay -v
      Sleeping for 77 seconds from max splay-time of 300 seconds

      $ ./splay -v -m 20
      Sleeping for 7 seconds from max splay-time of 20 seconds

Existing alternatives:

* [desync](https://debathena.mit.edu/trac/browser/trunk/athena/bin/desync/)



ssl-expiry-date
----------------

Report the date, and number of days, until the given SSL certificate expires.

Example:

        ./ssl-expiry-date bbc.co.uk
        Certificate presented at : bbc.co.uk
        Expires: Jun 18 13:50:58 2013 GMT  [63 days in the future]



timeout
-------

Timeout allows you to run a command which will be killed after the
given number of seconds.

Example:

        # Kill the command after 63 seconds.
        ./timeout -t 63 top

        # Kill the command after two minutes, five seconds.
        ./timeout -t 2:5 top

        # Kill the command after three hours, five minutes, and seven seconds
        ./timeout -t 3:5:7 top



until-success
-------------

Repeat the specific command until it succeeds - run at least once
always.

Example:

         ./until-success ssh example.com -l root -i ~/.ssh/example.com.key

Trivial (ba)sh alternatives:

* while true ; do $cmd; done
* watch -n 2 $cmd



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
