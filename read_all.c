#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 64

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: ./read_all filename\n");
        return 0;
    }
    printf("Reading all characters from a file using C library\n");
    FILE *file = fopen(argv[1], "r"); // fopen *filename with 'r' *mode/permissions
    if (!file){ // if error, fd is null, so !null => true
        printf("Failed to open file, %s", argv[0]);
        return 1;
    }
    bool done_reading = false;
    char readbuf[BUFSIZE];
    while(!done_reading){
        int n_read = fread(readbuf, 1, BUFSIZE - 1, file); // buff, size of what's read, how many to read, fp (file pointer)
        if(n_read == 0){
            done_reading = true;
        }
        readbuf[n_read] = '\0'; // printf needs null terminator
        for(int i = 0; i < n_read; i++){
            printf("%c", readbuf[i]);
        }
    }
    printf("\n");
    fclose(file);

    char *msg = "Reading all characters from a file using systems level calls\n";
    int msg_len = strlen(msg);
    int stdout_fd = fileno(stdout);
    if (!(msg_len = write(stdout_fd, msg, msg_len))){
        perror("Failed to write");
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        perror("Failed to open");
        exit(1);
    }

    int n_read2 = 0;
    char readbuf2[BUFSIZE];

    while(1){
        n_read2 = read(fd, readbuf2, BUFSIZE - 1);
        if(n_read2 == 0){
            break;
        }
        if (!(n_read2 = write(stdout_fd, readbuf2, n_read2))){
            perror("Failed to write");
        }
    }
    write(stdout_fd, "\n", 1);
    close(fd);
}
