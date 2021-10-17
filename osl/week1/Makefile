CC=clang

all: more grep

more: more.c
	$(CC) more.c -ggdb -o more

grep: grep.c
	$(CC) grep.c -ggdb -o grep

copy: copy.c
	$(CC) copy.c -ggdb -o copy

clean:
	rm -rf more grep copy