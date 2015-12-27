#!/bin/sh
#
# About
# -----
# Check the expiry date of the SSL certificate on the given host.
#
#
# License
# -------
#
# Copyright (c) 2013-2015 by Steve Kemp.  All rights reserved.
#
# This script is free software; you can redistribute it and/or modify it under
# the same terms as Perl itself.
#
# The LICENSE file contains the full text of the license.
#
#


#
#  Simple function to show usage information, and exit.
#
usage () {
    echo "Usage: $0 [-d] [-p 443] domain1.org domain2.com .. domainN"
    exit 0
}


#
#  Default settings for flags set by the command-line arguments
#
days=0
port=443

#
#  Parse the argument(s) - i.e. look for "-d" / "-p 443".
#
while getopts "h?dp:" opt; do
    case $opt in
        h)
            usage
            ;;
        \?)
            usage
            ;;
        d)
            days=1
            ;;
        p)
            port=$OPTARG
            ;;
    esac
done
shift $((OPTIND-1))


#
#  Ensure we have some arguments
#
if [ "$#" = "0" ]; then
    usage
fi


#
# For each domain-name on the command-line.
#
for name in "$@" ; do


    #
    #  Make a temporary file
    #
    # Test if we have BSD or GNU version of mktemp
    if ( strings $(which mktemp) | grep -q GNU); then
        # We have the GNU version
        tmp=$(mktemp)
    else
        # We have the BSD version
        tmp=$(mktemp -t tmp)
    fi


    #
    #  Download the certificate
    #
    if ( ! echo "" | openssl s_client -connect $name:$port > $tmp 2>/dev/null ); then
        echo "Failed to get cert from https://$name:$port/"
        exit 3
    fi


    #
    #  Get the expiry date
    #
    date=$(openssl x509 -in "$tmp" -noout -enddate | awk -F= '{print $2}')

    #
    #  Remove the temporary file
    #
    rm -f "$tmp"


    #
    #  Convert the expiry date + todays date to seconds-past epoch
    #
    # Check if we have the BSD or the GNU version of date
    if (strings $(which date) | grep -q GNU); then
        # We have GNU this is easy
        then=$(date --date "$date" +%s)
    else
        # We have BSD now it is getting complicated
        year=$(echo $date | awk '{print $4}')
        month=$(echo $date | awk '{print $1}')
        day=$(echo $date | awk '{print $2}')
        hour=$(echo $date | awk '{print $3}' | awk -F: '{print $1}')
        minute=$(echo $date | awk '{print $3}' | awk -F: '{print $2}')
        second=$(echo $date | awk '{print $3}' | awk -F: '{print $3}')
        then=$(date -v${year}y -v${month} -v${day}d -v${hour}H -v${minute}M -v${second}S -u +%s)
    fi

    now=$(date +%s)

    #
    #  Day diff
    #
    diff=$(expr "$then" - "$now" )
    diff=$(expr $diff / 86400 )

    #
    #  All done
    #
    if [ "$days" = "1" ]; then
        echo "${name}: ${diff}"
    else
        echo "$name"
        echo "    Expires: ${date}"
        echo "    Days: ${diff}"
    fi
done
