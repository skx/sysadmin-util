sysadmin-utils
==============

A small collection of scripts that might be useful to sysadmins.

Contributions of new scripts are very welcome, as are suggestions for
things to install.

I have a preference for Perl, but that does not rule out code that
needs to be compiled, or code in other scripting languages (Python,
Ruby, etc).



ago
---

Show how long ago a file/directory was modified in a  human-readable fashion.

Example:

     $ ./ago /etc/passwd
     /etc/passwd 15 weeks ago

Alternatives:

* `stat` and `ls` both show ages, but not in a human-readable fashion.



cidr2ip
-------

Given a set of CIDR ranges output the individual IPs in the range(s).

Example:

     $ ./cidr2ip 192.168.0.0/24
     192.168.0.0
     192.168.0.1
     192.168.0.2
     192.168.0.3
     192.168.0.4
     ..




dupes
-----

Report on duplicate files, via a SHA1 hash of the contents, recursively.

Example:

    $ dupes
    ./.git/logs/HEAD
	./.git/logs/refs/heads/master
    ./.git/refs/heads/master
	./.git/refs/remotes/origin/master

Alternatives:

* [fdupes](http://packages.debian.org/fdupes)
* [fslint](http://packages.debian.org/fslint)
* [duff](http://packages.debian.org/duff)
* [rdfind](http://packages.debian.org/rdfind)



empty-dir
---------

Indicate, via return code, whether a given directory is empty or not.

Example:

    if empty-dir /etc; then echo "We're broken" ; fi



maybe
-----

In a similar vain to `true` and `false` the `maybe` command exits with
a status code of zero or one, depending on a random number.

It can be useful in scripts which need to test-failures, or which benefit
from randomness:

Example:

     maybe && echo "I pass"

     maybe || echo "I fail"



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



pyhttpd
-------

A simple Python HTTP server, which has been updated to allow it to bind
to arbitrary IP addresses, specifically to allow you to bind to localhost.

Example:

     $ ./pyhttpd 127.0.0.1:8080
     Serving HTTP on 0.0.0.0 port 8080 ...

or

     $ ./pyhttpd 8080
     Serving HTTP on 127.0.0.1 port 8080 ...



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



since
-----

Show the new output since previously reading a file.  This is useful for
keeping track of logfile updates.

Example:

       $ ./since /var/log/messages >/dev/null
       $ logger "testing the log"
       $ ./since /var/log/messages
       Apr 20 11:24:37 precious skx: testing the log



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



when-up
----------

Waits until a given host is online (determined by ping until executing a given command

Example:

     $ ./when-up 1.2.3.4 ssh user@1.2.3.4
     Waiting for 1.2.3.4 to come online...
     Last login: Sat Dec 28 23:25:01 2013 from 5.6.7.8
     user@1.2.3.4:~#

Alternatives:

* `until-success ping -c 1 1.2.3.4; ssh user@1.2.3.4`



which-shell
-----------

Identify the shell we're running under.

For example:

     $ which-shell
     dash

Existing alternatives:

* `ls -l /bin/sh`



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
