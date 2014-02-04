#!/bin/sh
#
# About
# -----
# Identify the shell we're running under.
#
#
# License
# -------
#
# Copyright (c) 2013 by Steve Kemp.  All rights reserved.
#
# This script is free software; you can redistribute it and/or modify it under
# the same terms as Perl itself.
#
# The LICENSE file contains the full text of the license.
#
#



#
#  Easy cases first
#
if test -n "$ZSH_VERSION"; then
    s=zsh
elif test -n "$BASH_VERSION"; then
    s=bash
elif test -n "$KSH_VERSION"; then
    s=ksh
elif test -n "$FCEDIT"; then
    s=ksh
fi


#
#  If we found a result then we're done.
#
if [ ! -z "$s" ]; then
    echo $s
    exit 0
fi


#
#  If we have readlink, and /proc/$$/exe then use that
#
if [ -e /proc/$$/exe ]; then
    if ( which readlink >/dev/null 2>/dev/null ); then
        basename $(readlink /proc/$$/exe)
        exit 0
    fi
fi


#
#  Fallback
#
echo "unknown"
exit 0
