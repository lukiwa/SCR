#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{

    pid_t pid;
    int fd[2], image_fd, n;
    const int buffer_size = 256;
    char buffer[buffer_size];

    if (pipe(fd) < 0)
    {
        fprintf(stderr, "Failed creating pipe\n");
        return -1;
    }

    pid = fork();

    if (pid == 0)
    {
        //child
        close(fd[1]);
        close(0);
        dup(fd[0]);
        close(fd[0]);

        execlp("display", "display", "-", NULL);
    }
    else
    {
        //parent
        close(fd[0]);

        if ((image_fd = open(argv[1], O_RDONLY)) < 0)
        {
            fprintf(stderr, "Failed opening file\n");
            return image_fd;
        }

        while ((n = read(image_fd, buffer, buffer_size)) > 0)
        {
            if (write(fd[1], buffer, n) < 0)
            {
                fprintf(stderr, "Failed writing to pipe\n");
                return -1;
            }
        }
        close(image_fd);
    }
}
