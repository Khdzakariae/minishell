#include <minishell.h>


void signels_handler()
{
    // signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);

}