#
#  Simple makefile, mostly to format and test the perl-code.
#
#  The perltidy command uses the configuration file ~/.perltidyrc
# which you can find in my dotfiles repository:
#
#   https://github.com/skx/dotfiles
#
# Steve
#


nop:
	@echo ""
	@echo "make clean  - Remove backup files."
	@echo "make critic - Run the perl code through perlcritic."
	@echo "make tidy   - Run the perl code through perltidy."
	@echo ""

build: ipaddr.c
	gcc -o ipaddr ipaddr.c -Wall -Werror

clean:
	rm ipaddr *.bak *~ || true

critic:
	perlcritic $$(grep -l '^#!/usr/bin/env perl' *)

tidy:
	perltidy $$(grep -l '^#!/usr/bin/env perl' *)

