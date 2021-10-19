#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() { printf("USAGE: rev [src_file] [destination_file]"); }

long file_size(FILE *f) {
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);
  return size;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    help();
    exit(EXIT_FAILURE);
  }

  FILE *src = fopen(argv[1], "r");
  FILE *dest = fopen(argv[2], "w");
  long size = file_size(src);
  printf("File size of %s is %ld\n", argv[1], size);

  fseek(src, -1, SEEK_END);
  for (int i = size; i > 0; i--) {
    char ch = fgetc(src);
    fputc(ch, dest);
    fseek(src, -2, SEEK_CUR);
  }

  fclose(src);
  fclose(dest);
}