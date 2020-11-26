#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    pid_t pid;
    int fd[2];
    const int buffer_length = 200;
    int status = 0, file_fd = 0, n = 0;

    if (pipe(fd) < 0)
    {
        fprintf(stderr, "Creating pipe failed\n");
        return -1;
    }

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return pid;
    }

    else if (pid == 0)
    {
        //child
        const int data_pack_size = 5;
        char buffer[buffer_length];

        while (read(fd[0], buffer, data_pack_size) > 1)
        {
            write(1, "#", 1);
            write(1, buffer, data_pack_size);
            write(1, "#", 1);
            write(1, "\n", 1);
        }

        close(fd[0]);
        exit(0);
    }
    else
    {
        //parent

        char to_send_buffer[buffer_length];

        if ((file_fd = open(argv[1], O_RDONLY)) < 0)
        {
            fprintf(stderr, "Opening file failed\n");
            return file_fd;
        }

        while ((n = read(file_fd, to_send_buffer, buffer_length)) > 0)
        {
            if (write(fd[1], to_send_buffer, n) < 0)
            {
                fprintf(stderr, "Writing to pipe failed\n");
                return -1;
            }
        }
        close(file_fd);
        close(fd[1]);
        wait(&status);
    }

    return (status);
}
