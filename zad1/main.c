#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int fd[2];
    const int buffer_length = 200;
    int status = 0;
    FILE *file;
    pipe(fd);

    int fork_status = fork();
    if (fork_status < 0)
    {
        fprintf(stderr, "fork failed\n");
        return fork_status;
    }

    else if (fork_status == 0)
    {
        //child
        char to_send_buffer[buffer_length];
        file = fopen(argv[1], "r");

        while (fscanf(file, "%s", to_send_buffer) == 1)
        {
            write(fd[1], to_send_buffer, strlen(to_send_buffer));
        }

        fclose(file);
        exit(0);
    }
    else
    {
        //parent
        const int data_pack_size = 5;
        char buffer[buffer_length];

        close(fd[1]);
        while (read(fd[0], buffer, data_pack_size) > 0)
        {   
            write(1, "#", 1);
            write(1, buffer, data_pack_size);
            write(1, "#", 1);
            write(1, "\n", 1);
        
        }
    }

    wait(&status);
    return (status);
}