#include <minishell.h>

void handle_sigint()
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void signels_handler()
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}