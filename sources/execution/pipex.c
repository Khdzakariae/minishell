/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/05 23:23:24 by aogbi            ###   ########.fr       */
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

    if (access(cmd, F_OK) == 0)
        return (cmd);
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
int	error(char *message)
{
	printf("%s: %s\n", strerror(errno), message);
	return (-1);
}

int	execute_command(char **cmd, char **path, int in_fd, int out_fd, char **env)
{
	pid_t pid;
	char *cmd_name;

	pid = fork();
	if (pid == -1)
    	return (error("fork"));
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
		printf("%s: command not found\n", cmd[0]);
		exit (1);
	}
	return (0);
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

int redirections(t_list *list, int in_fd, char **path, char **env)
{
	int fd[2];
	int in_tmp;
	int out_fd;

	if (pipe(fd) == -1)
		return (error("pipe"));
	in_tmp = input_file((t_list *)(((t_ogbi *)(list->content))->input_files));
	if (in_tmp != 0)
	{
		if (in_fd != 0)
			close(in_fd);
		if (in_tmp == -1)
		    return (-1);
		in_fd = in_tmp;
	}
	out_fd = output_file((t_list *)(((t_ogbi *)(list->content))->output_files));
	if (out_fd == -1)
	    return (-1);
	else if (out_fd == 1)
		out_fd = fd[1];
	execute_command((((t_ogbi *)(list->content))->cmd), path, in_fd, out_fd, env);
	if (in_fd != 0)
		close(in_fd);
	if (out_fd != 1)
		close(out_fd);
	close(fd[1]);
	return (fd[0]);
}

int last_command(t_list *list, int in_fd, char **path, char **env)
{
	int in_tmp;
	int out_fd;

	in_tmp = input_file((t_list *)(((t_ogbi *)(list->content))->input_files));
	if (in_tmp != 0)
	{
		if (in_fd != 0)
		    close(in_fd);
		if (in_tmp == -1)
		    return (0);
		in_fd = in_tmp;
	}
	out_fd = output_file((t_list *)(((t_ogbi *)(list->content))->output_files));
	if (out_fd == -1)
	    return (-1);
	execute_command((((t_ogbi *)(list->content))->cmd), path, in_fd, out_fd, env);
	if (in_tmp != 0)
		close(in_fd);
	if (out_fd != 1)
		close(out_fd);
	return(0);
}

int	pipex(t_list *list, char **env)
{
	char **path;
	int in_fd;

	path = ft_split(find_path_from_env(env), ':');
	in_fd = 0;
	
	while (list->next)
	{
		in_fd = redirections(list, in_fd, path, env);
		if (in_fd == -1)
		return (0);
		list = list->next;
	}
	last_command(list, in_fd, path, env);
	del(path);
	while(wait(NULL) > 0);
	return (0);
}

int ft_herdoc(int index, t_list *list)
{
	char *line;
	char *tmp;
	int fd;

	tmp = ft_strdup("/tmp/.Her_Doc_");
	line = ft_strjoin(tmp, ft_itoa(index));
	free(tmp);
	tmp = line;
	fd = open(line ,  O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		return (error((char *)list->content));
	while(1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, ((t_red *)list->content)->value) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return(fd);
}

int input_file(t_list *list)
{
	int fd;
	int index;

	fd = 0;
	index = 0;
	while(list)
	{
		if (((t_red *)list->content)->type == ENTREE)
		{
			fd = open(((t_red *)list->content)->value, O_RDONLY);
			if (fd == -1)
				return (error((char *)list->content));
			list = list->next;
		}
		else
			fd = ft_herdoc(index++, list);
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
		if (((t_red *)list->content)->type == SORTIE)
		{
			fd = open(((t_red *)list->content)->value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    		if (fd == -1)
				return (error(((t_red *)list->content)->value));
		}
		else
		{
			fd = open(((t_red *)list->content)->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
    		if (fd == -1)
				return (error(((t_red *)list->content)->value));
		}
		list = list->next;
		if (list)
			close(fd);
	}
    return (fd);
}
