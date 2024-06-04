#include <minishell.h>


int main ()
{
    const char *name = "PATH";
    char *value;
    value = getenv(name);
    while (1)
    {
        char *line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
        execv(value, &line);
        printf("%s\n", line);
    }
    

}



