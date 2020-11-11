#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <ucontext.h>

uint64_t i = 0;
const int block_for_n_iterations = 30;

void sig_handler(int signal_number)
{
    static int iteration = 0;
    static bool is_blocked = false;

    switch (signal_number)
    {
    case SIGALRM:
        fprintf(stderr, "Koncze prace\n");
        _exit(SIGALRM);

    case SIGTERM:
        fprintf(stderr, "Kontynuuje dzialanie\n");
        return;
    case SIGUSR1:
        if (is_blocked)
        {
            if (i - iteration > block_for_n_iterations)
            {
                is_blocked = false;
            }
            else
            {
                fprintf(stderr, "Obslug zablokowana\n");
            }
        }

        if (!is_blocked)
        {
            fprintf(stderr, "Robie cos\n");
            iteration = i;
            fprintf(stderr, "Blokuje na %d iteracji\n", block_for_n_iterations);
            is_blocked = true;
        }
        break;

    default:
        fprintf(stderr, "Inny sygnal");
        break;
    }
}

int main()
{

    signal(SIGALRM, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, SIG_IGN);

    while (true)
    {
        ++i;
        // fprintf(stderr, "Main\n");
        sleep(1);
    }

    return 0;
}
