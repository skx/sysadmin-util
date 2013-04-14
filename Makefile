

all: splay with-lock


clean:
	rm with-lock


splay: splay.c
	gcc -Wall -Werror splay.c -o splay

with-lock: with-lock.c
	gcc -Wall -Werror with-lock.c -o with-lock -lssl
