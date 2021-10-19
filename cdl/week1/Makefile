CC=clang

all: count merge_line rev

count: count.c
	$(CC) count.c -ggdb -o count

rev: rev.c
	$(CC) rev.c -ggdb -o rev

merge_line: merge_line.c
	$(CC) merge_line.c -ggdb -o merge_line

clean:
	rm -rf count merge_line rev