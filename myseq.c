#include <stdlib.h>
#include <stdio.h>

void myseq(int argc, char** argv){
    
}

void convertlong(long* number, char** argv, char *endptr){

    *number = strtol(argv[0], &endptr, 0);
    printf("ENDPTR: %s\n", endptr);

}

int main(int argc, char **argv){
    long last = 1;
    long first = 1;
    long increment = 1;
    char err;

    argc--;
    argv++;

    if (argc == 0){
        fprintf(stderr, "myseq: missing operand\n");
        exit(EXIT_FAILURE);
    }

    
    convertlong(&last, argv, &err);
    printf("LAST: %ld\n", last);
    printf("ERR: %s\n", err);
    if (err != '\0'){
        fprintf(stderr, "myseq: strtol failed, argv not a number");
    }
    

    myseq(argc, argv);

    exit(EXIT_SUCCESS);
}