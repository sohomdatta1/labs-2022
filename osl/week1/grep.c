#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdbool.h>
#include <termios.h>

static int line_number = 0;

void help() {
    printf(" USAGE: grep [name_of_file] ... [search_term]\n");
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

void find_in_text(char * text, char * search_term) {
    char * ptr_for_text = text, * ptr_for_search_term = search_term;
    bool flag = false;
    while(*ptr_for_text != '\0') {
        if ( *ptr_for_text == *ptr_for_search_term ) {
            if ( strncmp(ptr_for_text, ptr_for_search_term, strlen(ptr_for_search_term)) == 0 ) {
                flag = true;
                ptr_for_text += strlen(ptr_for_search_term);
            }
        }
        ptr_for_text++;
    }
    ptr_for_text = text;
    if ( flag ) {
        printf(" %d: ", line_number);
        while(*ptr_for_text != '\0') {
            if ( *ptr_for_text == *ptr_for_search_term ) {
                if ( strncmp(ptr_for_text, ptr_for_search_term, strlen(ptr_for_search_term)) == 0 ) {
                    printf("\033[1;31m%s\033[1;0m", ptr_for_search_term);
                    ptr_for_text += strlen(ptr_for_search_term);
                }
            }
            printf("%c", *ptr_for_text);
            ptr_for_text++;
        }
        printf("\n");
    }
}

int find_in_line(int fd, char * search_term) {
    char * line = (char *)malloc(2);
    line[0] = '\0';
    char ch;
    int r_val = read_char(fd, &ch);
    int size = 0;

    while( ch != '\n' && ch != '\r' ) {
        if ( r_val < 0 || ch == 0 ) {
            line[size] = '\0';
            find_in_text(line, search_term);
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

    find_in_text(line, search_term);
    fflush(stdin);
    fflush(stdout);
    if ( strlen(line) ) {
        free(line);
    }
    return 0;
}

void find_in_file(char * name_of_file, char * search_term) {
    int fd;
    int r_val;
    
    fd = open(name_of_file, O_RDONLY);
    
    if ( fd < 0 ) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    line_number = 1;

    while( true ) {
        r_val = find_in_line(fd, search_term);
        line_number++;
        if (r_val < 0) {
            goto cleanup;
        }
    }
    
    cleanup: 
    r_val = close(fd);
    if ( r_val < 0 ) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[]) {
    if ( argc < 3 ) {
        help();
        exit(EXIT_FAILURE);
    }

    char * search_term = malloc(strlen(argv[argc-1]));
    strncpy(search_term, argv[argc-1], strlen(argv[argc-1]));

    int i;
    char * name_of_file = NULL;
    for (i = 1; i < argc - 1; i++) {
        name_of_file = (char *)malloc(strlen(argv[i]));
        strncpy(name_of_file, argv[i], strlen(argv[i]));
        print_name_of_file(name_of_file);
        find_in_file(name_of_file, search_term);
        free(name_of_file);
        name_of_file = NULL;
    }
}
