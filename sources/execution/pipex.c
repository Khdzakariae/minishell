/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/12 16:39:39 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_stat;

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

void	ft_cd(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 2)
	{
		if(chdir(cmd[1]))
		perror(cmd[1]);
	}
	else if (i == 1)
		chdir(getenv("HOME"));
	else
        printf("cd: too many arguments\n");
}

void    ft_pwd(void)
{
	char cwd[1024];

    if (getcwd(cwd, sizeof(cwd))!= NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
}

void    ft_echo(char **cmd)
{
	int i;
	int n;

    i = 1;
	n = 0;
	if (cmd[i] && !ft_strcmp(cmd[i], "-n"))
	{
		n = 1;
		i++;
	}
    while (cmd[i])
    {
        printf("%s ", cmd[i]);
        i++;
    }
	if (!n)
    	printf("\n");
}

void	ft_env(char **env)
{
	int i;

    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

void convert_variable(char **cmd)
{
	int i;
	char *value;
	
	i = 0;
	while(cmd[i])
	{
		if (cmd[i][0] == '$')
        {
			if (!ft_strcmp(cmd[i], "$?"))
			{
				free(cmd[i]);
				cmd[i] = ft_itoa(g_stat);
			}
			else
			{
            	value = getenv(cmd[i] + 1);
				free(cmd[i]);
				cmd[i] = ft_strdup(value);
			}
        }
        i++;
	}
}


int ft_execve(char **cmd, char **env)
{
	convert_variable(cmd);
	if (!cmd)
	    return (0);
	else if (!ft_strcmp(cmd[0], "cd"))
	    ft_cd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
	    ft_echo(cmd);
	// else if(!ft_strcmp(cmd[0], "export"))
	//     ft_export(cmd);
	// else if(!ft_strcmp(cmd[0], "unset"))
	//     ft_unset(cmd);
	else if(!ft_strcmp(cmd[0], "exit"))
	    ;
	else if (!ft_strcmp(cmd[0], "env"))
	    ft_env(env);
	else
		return (0);
	return (1);
}

int    ft_status(int *status)
{
	if (WIFEXITED(*status))
		g_stat = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		g_stat = WTERMSIG(*status) + 128;
	return (1);
}

int	execute_command(char **cmd, char **path, int in_fd, int out_fd, char **env)
{
	char *cmd_name;
	pid_t pid;

    if (ft_execve(cmd, env))
		return (0);
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
		write(2, cmd[0], sizeof(cmd_name));
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (1);
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
	if (execute_command((((t_ogbi *)(list->content))->cmd), path, in_fd, out_fd, env) < 0)
	    return (-1);
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
	if (execute_command((((t_ogbi *)(list->content))->cmd), path, in_fd, out_fd, env) < 0)
	    return (-1);
	if (in_tmp != 0)
		close(in_fd);
	if (out_fd != 1)
		close(out_fd);
	return(0);
}

int	pipex(t_list *list, char **env)
{
	char **path;
	int valid;
	int status;
	int in_fd;

	path = ft_split(find_path_from_env(env), ':');
	in_fd = 0;
	valid = 1;
	while (list->next)
	{
		in_fd = redirections(list, in_fd, path, env);
		if (in_fd == -1)
		{
			valid = in_fd;
			break;
		}
		list = list->next;
	}
	if (valid > 0)
		valid = last_command(list, in_fd, path, env);
	del(path);
	while (wait(&status) > 0);
	ft_status(&status);
	return (valid);
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
	fd = open(line , O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		return (error(line));
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
				return (error(((t_red *)list->content)->value));
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
