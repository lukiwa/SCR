#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

int main()
{
    const int shared_fd = open("shared_file.txt", O_RDWR);
    struct stat shared_filename_data;

    fstat(shared_fd, &shared_filename_data);

    char *ptr = mmap(NULL, shared_filename_data.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_fd, 0);
    if (ptr == MAP_FAILED)
    {
        return -1;
    }

    char user_filename[25];
    int user_fd = 0;
    FILE *user_file;
    struct stat user_filename_data;

    int i = 0;
    int c = 0;
    while (true)
    {
        printf("File name: ");
        scanf("%s", user_filename);

        user_fd = open(user_filename, O_RDWR);
        user_file = fdopen(user_fd, "r");
        fstat(user_fd, &user_filename_data);

        ftruncate(shared_fd, user_filename_data.st_size);
        ptr = mmap(NULL, user_filename_data.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_fd, 0);

        while ((c = fgetc(user_file)) != EOF)
        {
            ptr[i++] = c;
        }
        i = 0;
        fclose(user_file);
        close(user_fd);
    }

    return 0;
}