

all: with-lock


clean:
	rm with-lock


with-lock: with-lock.c
	gcc -Wall -Werror with-lock.c -o with-lock -lssl
