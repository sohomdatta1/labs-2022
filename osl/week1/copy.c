#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf(" USAGE: copy [name_of_source] [name_of_destination]\n");
}

int main(int argc, char argv[]) {
    int r_val = 0;
    if ( argc == 3 ) {
        help();
        exit(EXIT_FAILURE);
    }
    int c;
    FILE *in_file, *out_file;
    in_file = fopen(argv[1],"r");
    if ( in_file < 0 ) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    out_file = fopen(argv[2],"w");
    if ( out_file < 0 ) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while((c = fgetc(in_file)) != EOF)
        fputc(c, out_file);
    
    r_val = fclose(in_file);
    if ( r_val < 0 ) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    r_val = fclose(out_file);
    if ( r_val < 0 ) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    exit(0);
}