#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 1024

int main(void) {
    FILE * fd;
    fd = fopen("./text/a.txt", "r");
    char formatstr [] = "%s\n%d\n%c\n%s";
    char first_string[MAX_STR_SIZE], last_string[MAX_STR_SIZE], third_character;
    int second_int = 0;
    fscanf(fd, formatstr, first_string, &second_int, &third_character, last_string);
    printf("First string: %s\n", first_string);
    printf("Second integer: %d\n", second_int);
    printf("Third character: %c\n", third_character);
    printf("Last string: %s\n", last_string);
    fclose(fd);
}