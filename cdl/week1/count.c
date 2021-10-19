#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() { printf("USAGE: count [name_of_file]"); }

int get_line(FILE *fd, int *size) {
  char *line;

  line = (char *)malloc(2);
  line[0] = '\0';
  char ch = fgetc(fd);
  *size = 0;

  while (ch != '\n' && ch != '\r') {
    if (ch == EOF) {
      line[*size] = '\0';
      *size = strlen(line);
      return -1;
    }
    line = (char *)realloc(line, *size + 2);
    line[*size] = ch;
    *size = *size + 1;
    ch = fgetc(fd);
  }
  line[*size] = '\0';
  *size = strlen(line);

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    help();
    exit(EXIT_FAILURE);
  }

  FILE *fd;
  fd = fopen(argv[1], "r");
  char *line = NULL;
  int no_of_lines = 0;
  int no_of_characters = 0;
  int r_val = 0;
  int size = 0;
  while (r_val == 0) {
    r_val = get_line(fd, &size);
    no_of_characters = no_of_characters + size;
    no_of_lines++;
  }
  printf("Number of lines: %d\n", no_of_lines);
  printf("Number of characters: %d\n", no_of_characters);

  fclose(fd);
}