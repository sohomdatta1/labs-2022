#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
  printf(
      "USAGE: merge_line [name_of_file1] [name_of_file2] [destination_file]");
}

int get_and_write_line(FILE *fd_rd, FILE *fd_wr) {
  char *line;

  line = (char *)malloc(2);
  line[0] = '\0';
  char ch = fgetc(fd_rd);
  int size = 0;

  while (ch != '\n' && ch != '\r') {
    if (ch == EOF) {
      line[size] = '\0';
      fputs(line, fd_wr);
      fputs("\n", fd_wr);
      return -1;
    }
    line = (char *)realloc(line, size + 2);
    line[size] = ch;
    size = size + 1;
    ch = fgetc(fd_rd);
  }
  line[size] = '\0';
  fputs(line, fd_wr);
  fputs("\n", fd_wr);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    help();
    exit(EXIT_FAILURE);
  }

  FILE *src1 = fopen(argv[1], "r");
  FILE *src2 = fopen(argv[2], "r");
  FILE *dest = fopen(argv[3], "w");
  int r_val1, r_val2;
  while (r_val1 == 0 || r_val2 == 0) {
    if (r_val1 == 0) {
      r_val1 = get_and_write_line(src1, dest);
    }

    if (r_val2 == 0) {
      r_val2 = get_and_write_line(src2, dest);
    }
  }
  fclose(src1);
  fclose(src2);
  fclose(dest);
}