CC=clang

all: more grep copy conv_spec

more: more.c
	$(CC) more.c -ggdb -o more

grep: grep.c
	$(CC) grep.c -ggdb -o grep

copy: copy.c
	$(CC) copy.c -ggdb -o copy

conv_spec: conv_spec.c
	$(CC) conv_spec.c -ggdb -o conv_spec

clean:
	rm -rf more grep copy conv_spec