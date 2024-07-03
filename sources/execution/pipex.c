/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/03 04:55:27 by aogbi            ###   ########.fr       */
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

void	execute_command(char **cmd, char **path, int in_fd, int out_fd, char **env)
{
	pid_t pid;
	char *cmd_name;

	pid = fork();
	if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (in_fd != STDIN_FILENO)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
		cmd_name = cmd_path(cmd[0], path);
		if (cmd_name)
			execve(cmd_name, cmd, env);
		exit(EXIT_FAILURE);
	}
}

void  del(void *content)
{
	char **str;
	int i = 0;

	str = (char **)content;
	while(str[i])
	{
		free(str[i]);
        i++;
	}
	free(str);
}

void	pipex(t_list *list, char **env)
{
	char **path;
	int in_fd;
	int out_fd;
	int fd[2];
	t_list *in_list;
	t_list *out_list;

	path = ft_split(find_path_from_env(env), ':');
	while (list->next)
	{
    	in_list = (t_list *)(((t_ogbi *)(list->content))->input_files);
		out_list = (t_list *)(((t_ogbi *)(list->content))->output_files);
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		in_fd = input_file(in_list);
		if (in_fd == 0 && out_fd == -1)
		    in_fd = fd[0];
		output_file(out_list);
		execute_command((((t_ogbi *)(list->content))->cmd), path, in_fd, fd[1], env);
        close(fd[1]);
		out_fd = -1;
		list = list->next;
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	in_list = (t_list *)(((t_ogbi *)(list->content))->input_files);
	out_list = (t_list *)(((t_ogbi *)(list->content))->output_files);
	in_fd = input_file(in_list);
	if (in_fd == 0)
		in_fd = fd[0];
	out_fd = output_file(out_list);
	execute_command((((t_ogbi *)(list->content))->cmd), path, in_fd, out_fd, env);
	del(path);
	while(wait(NULL) > 0);
}

int input_file(t_list *list)
{
	int fd;

	fd = 0;
	while(list)
	{
		fd = open((char *)list->content, O_RDONLY);
		if (fd == -1)
		{
		   	printf("%s: %s\n", strerror(errno), (char *)list->content);
		    exit(EXIT_FAILURE);
		}
		list = list->next;
		if (list)
			close(fd);
	}
    return (fd);
}

int output_file(t_list *list)
{
	int fd;

	fd = 1;
	while(list)
	{
		if(access((char *)list->content, F_OK) < 0);
		else if (access((char *)list->content, W_OK) < 0)
		{
    	    printf("%s: %s\n", strerror(errno), (char *)list->content);
    	    exit(EXIT_FAILURE);
    	}
    	fd = open((char *)list->content, O_WRONLY | O_CREAT, 0666);
    	if (fd == -1)
    	{
    	    printf("%s: %s\n", strerror(errno), (char *)list->content);
    	    exit(EXIT_FAILURE);
    	}
		else
		{
			unlink((char *)list->content);
			fd = open((char *)list->content, O_WRONLY | O_CREAT, 0666);
    		if (fd == -1)
    		{
    		    printf("%s: %s\n", strerror(errno), (char *)list->content);
    		    exit(EXIT_FAILURE);
    		}
		}
		list = list->next;
		if (list)
			close(fd);
	}
    return (fd);
}