#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdbool.h>
#include <termios.h>

void help() {
    printf(" USAGE: more [name_of_file]\n");
}

void print_name_of_file( char * name_of_file ) {
    printf("::::::::::::::\n");
    printf("%s\n", name_of_file);
    printf("::::::::::::::\n");
}

int read_char(int fd, char * ch) {
    char * trash_buf = (char *)calloc(sizeof(char), 1);
    int r_val = read(fd, trash_buf, 1);
    if ( r_val < 0 ) {
        perror("read");
        return -1;
    }
    *ch = trash_buf[0];
    free(trash_buf);
    return 0;
}

int get_line(int fd) {
    char * line = (char *)malloc(2);
    line[0] = '\0';
    char ch;
    int r_val = read_char(fd, &ch);
    int size = 0;

    while( ch != '\n' && ch != '\r' ) {
        if ( r_val < 0 || ch == 0 ) {
            line[size] = '\0';
            printf("%s\n", line);
            fflush(stdin);
            fflush(stdout);
            free(line);
            return -1; 
        }
        line = (char *)realloc(line, size + 2);
        line[size] = ch;
        size = size + 1;
        r_val = read_char(fd, &ch);
    }
    line[size] = '\0';

    printf("%s\n", line);
    fflush(stdin);
    fflush(stdout);
    if ( strlen(line) ) {
        free(line);
    }
    return 0;
}

void implement_wait_for_input() {
    fflush(stdin);
    fflush(stdout);
    printf("\n\n\e[7m--More--");
    struct termios old, new;

    /* Turn echoing off and fail if we can't. */
    if (tcgetattr (fileno (stdin), &old) != 0)
        exit(-1);
    new = old;
    new.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stdin), TCSAFLUSH, &new) != 0)
        exit(-1);
    char ch = getchar();
    (void) tcsetattr (fileno (stdin), TCSAFLUSH, &old);
    printf("\b\b\r");
    printf("\e[0m");
    fflush(stdin);
    fflush(stdout);
}

void buffer_file(char * name_of_file) {
    int fd;
    int r_val;
    
    fd = open(name_of_file, O_RDONLY);
    
    if ( fd < 0 ) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while( true ) {
        for (int i = 0; i < 20; i++) {
            r_val = get_line(fd);
            if (r_val < 0) {
                goto cleanup;
            }
        }

        implement_wait_for_input();
    }
    
    cleanup: 
    r_val = close(fd);
    if ( r_val < 0 ) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[]) {
    if ( argc < 2 ) {
        help();
        exit(EXIT_FAILURE);
    }

    int i;
    char * name_of_file = NULL;
    for (i = 1; i < argc; i++) {
        name_of_file = (char *)malloc(strlen(argv[i]));
        strncpy(name_of_file, argv[i], strlen(argv[i]));
        print_name_of_file(name_of_file);
        buffer_file(name_of_file);
        free(name_of_file);
        name_of_file = NULL;
    }
}
