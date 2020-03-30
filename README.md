sysadmin-utils
============

This repository contains a small collection of scripts that might be
useful to sysadmins.  I put it together myself to centralise the small
tools that I find useful, and it seems to be popular.

I used to solicit the inclusion of new tools, but have slowly come
to realize that "less is more".  I __love__ the idea of sysadmins,
developers, and other people building up their own toolkits, but also
find that people submit things that I just don't understand the appeal of.

It makes sense that personal-tools are very personal, but it does mean
rejection is almost always the default behaviour and that makes me feel
bad.

Instead of adding things here consider this repository a small collection of things that I use, and if you want to take some/all of utilities into your own use then please do so.  If not then I would __strongly__ encourage you to consider what tools would make your daily-life more useful and then collect them, __document__ them, and publish them yourself.


In short the value here is the __idea__ of collecting your commonmost utilities and making them easy to install and update from one central-source.  Not the specific tools themselves.

There is a replacement repository which is still open, and which new additions can be made more freely:

* https://github.com/skx/sysbox



ago
---

Show how long ago a file/directory was modified in a  human-readable fashion.

Example:

     $ ./ago /etc/passwd
     /etc/passwd 15 weeks ago

Alternatives:

* `stat` and `ls` both show ages, but not in a human-readable fashion.



chronic
-------

Run a command, hiding STDOUT and STDERR if it completes successfully.

Example:

     ./chronic cp /etc/passwd /tmp/not/found

This is designed to be used for cron-jobs, where output is generally
ignored in the case of success.

This was written by Joey Hess and is part of [moreutils](https://joeyh.name/code/moreutils/).



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




collapse
--------

Remove extraneous whitespace from lines, and remove empty-lines entirely.

Example:

     $ echo -e "Test1\n    f  \n\nTest2\n\n\n\n" | ./collapse
     Test1
     f
     Test2

Alternatives:

* `tr`
* ...



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



expand-ipv6
-----------

Expand an abbreviated/compressed IPv6 address to the full-form.

Example:

     ./expand-ipv6 fe80::1 2001:41c8:10b:103::111
     fe80:0000:0000:0000:0000:0000:0001
     2001:41c8:010b:0103:0000:0000:0111

Alternatives:

* `sipcalc`
* ...



graphite_send
-------------

A simple script to send a consistent set of metrics & values to a remote
graphite instance.

The metrics may be extended via small "plugins", which are nothing more
than shell/perl/ruby/python scripts in a particular directory.

Example:

     graphite_send -v

**NOTE** Some metrics will only be sent if the invoking user is root.

Alternatives

* [collectd](http://collectd.org/)
* [diamond](https://github.com/BrightcoveOS/Diamond)
* ..


ipaddr
------

Get IP addresses easily, either all IPs, all those which are IPv4/IPv6, or
those for a device.  Designed primarily for scripting.

Example:

      $ ./ips -4
      lo 127.0.0.1
      eth0 80.68.84.102
      eth0 80.68.84.104

Or to see all IPv6 addreses on eth0:

      $ ipaddr -6 -d eth0
      eth0 2001:41c8:10b:102::10
      eth0 fe80::216:3eff:fe08:16a4

**NOTE** Requires compilation via `make build`.

Alternatives:

* `ip -[46] addr  show`
* `ifconfig -a`


maybe
-----

In a similar vein to `true` and `false` the `maybe` command exits with
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

As a convenience you may also specify URIs as arguments, for example:

     $ multi-ping http://steve.org.uk/foo/bar
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
     Serving HTTP on 127.0.0.1 port 8080 ...

or

     $ ./pyhttpd 8080
     Serving HTTP on 0.0.0.0 port 8080 ...



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

Existing alternatives:

* logtail



ssh-auth-types
--------------

Show the authentication types presented by a remote SSH server.

Example:

     $ ./ssh-auth-types precious
     publickey password

     $ ./ssh-auth-types ssh.example.com
     publickey



ssh-test
--------

Test whether `ssh` connections to a list of hosts will succeed, by testing
each in order.

Example:

     $ ./ssh-test host.list.txt
     ssh.steve.org.uk    ... OK
     www.steve.org.uk    ... OK
     foo.example.com:222 ... OK

     $ cat host.list.txt
     ssh.steve.org.uk
     www.steve.org.uk
     foo.example.com:222

The format of the input-file is:

    [user@]hostname1[:port]
    [user@]hostname2[:port]
    ..


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

Report the date, and number of days, until the given SSL certificate
expires.  Multiple domain-names may be accepted and each is tested
in turn.

The default output is "noisy", but you may add "-d" to simplify this
to the domain-name and the number of days remaining on the certificate.


Example:

      ./ssl-expiry-date  bbc.co.uk
      bbc.co.uk
          Expires: Sep 18 13:50:57 2016 GMT
          Days: 266

      ./ssl-expiry-date -d bbc.co.uk steve.org.uk
      bbc.co.uk: 266
      steve.org.uk: 82




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
-------

Waits until a given host is online, determined by ping, until executing a given command.

Example:

     $ ./when-up 1.2.3.4 ssh user@1.2.3.4
     Waiting for 1.2.3.4 to come online...
     Last login: Sat Dec 28 23:25:01 2013 from 5.6.7.8
     user@1.2.3.4:~#

Alternatives:

* `until-success ping -c 1 1.2.3.4; ssh user@1.2.3.4`



until-error
-------------

Repeat the specific command until it fails - run at least once
always.

Example:

         ./until-error ssh example.com -l root -i ~/.ssh/example.com.key

Trivial (ba)sh alternatives:

* while true ; do $cmd; done
* watch -n 2 $cmd



when-down
-------

Waits until a given host is down

Example:

     $ ./when-down 1.2.3.4 echo "down"
     Waiting for 1.2.3.4 to get down...
     down

Alternatives:

* `until-error ping -c 1 -W 1 1.2.3.4; echo "down"`



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

 * lckdo - Requires you to build your own lockfile name.
 * flock - Requires you to build your own lockfile name.



Problems
--------

Please report any issue/suggestions via the github repository:

* https://github.com/skx/sysadmin-util



Author
------

Steve Kemp <steve@steve.org.uk>
