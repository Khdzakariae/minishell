/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/06/29 02:53:02 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_path_from_env(char **env)
{
	int i = 0;

    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i] + 5);
        i++;
    }
    return (NULL);
}

char	*cmd_path(char *cmd, char **path)
{
	int i = 0;
	char *cmd_name;
	char *tmp;

    while (path[i])
    {
		tmp = ft_strjoin(path[i], "/");
		cmd_name = ft_strjoin(tmp, cmd);
		free(tmp);
        if (access(cmd_name, F_OK) == 0)
            return (cmd_name);
		free(cmd_name);
        i++;
    }
    return (NULL);
}

int execute_command(char **cmd, char **path, int in_fd, int out_fd, char **env)
{
    pid_t pid;
	char *cmd_name;
	
	pid = fork();
    if (pid == 0) {
        if (out_fd != STDOUT_FILENO)
            dup2(out_fd, STDOUT_FILENO);
		if (in_fd != STDIN_FILENO)
		    dup2(in_fd, STDIN_FILENO);
		cmd_name = cmd_path(cmd[0], path);
		if (cmd_name)
			execve(cmd_name, cmd, env);
        exit(EXIT_FAILURE);
    }
	else
		waitpid(pid, NULL, 0);
    return pid;
}

void	pipex(t_list *list, int size, char **env, int in_fd, int out_fd)
{
	char **path;
	int fd[2];
	pid_t pid;

	path = ft_split(find_path_from_env(env), ':');
	pipe(fd);
	while (list->next)
	{
		pid = execute_command(list->content, path, in_fd, fd[1], env);
		in_fd = fd[0];
		list = list->next;
	}
	pid = execute_command(list->content, path, fd[0], out_fd, env);
	close(fd[0]);
	close(fd[1]);
}

int main(int argc, char *argv[], char *env[])
{
	t_list    *list;
	int i = 1;

	list = NULL;
	if (argc < 2)
		return 0;
	while(argc - i)
	{
		ft_lstadd_front(&list, ft_lstnew((void *)((char **)ft_split(argv[i], ' '))));
		i++;
	}
    pipex(list, argc - 1, env, STDIN_FILENO, STDOUT_FILENO);
    return 0;
}
