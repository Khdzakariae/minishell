/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/31 09:15:14 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_stat;

char	*find_str_from_env(char **env, char *str)
{
	int i;
	int len;
	char *tmp;

	tmp = ft_strjoin(str, "=");
	i = 0;
	len = ft_strlen(tmp);
    while (env[i])
    {
        if (ft_strncmp(env[i], tmp, len) == 0)
		{
			free(tmp);
            return (env[i] + len);
		}
        i++;
    }
	free(tmp);
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
		{
			perror(cmd[1]);
			return ;
		}
	}
	else if (i == 1)
		chdir(getenv("HOME"));
	else
	{
        write(2, "cd: too many arguments\n", 24);
		return ;
	}
}

void    ft_pwd(void)
{
	char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
	{
        perror("getcwd() error");
		return ;
	}
}

void    ft_echo(char **cmd)
{
	int i;
	int j;
	int n;

    i = 1;
	n = 0;
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while(cmd[i][j] == 'n')
			j++;
		if (!cmd[i][j])
			n = 1;
		else
			break;
		i++;
	}
    while (cmd[i])
    {
        write(1 ,cmd[i], ft_strlen(cmd[i]));
        i++;
		if (cmd[i])
			write(1, " ", 1);
    }
	if (!n)
    	write(1, "\n", 1);
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
int count_array_of_str(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}


char **ft_export(char **cmd, char **env)
{
	char **tmp;

	tmp = NULL;
	if (count_array_of_str(cmd) == 1)
		;
	printf("hello world!\n");
}

void ft_unset(char **cmd, char **env)
{
	printf("fuck off\n");
}

int ft_execve(char **cmd, char **env)
{
	if (cmd_quote_handler(cmd, env))
		return (1);
	if (!cmd || !cmd[0])
	    return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
	    ft_cd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
	    ft_echo(cmd);
	else if(!ft_strcmp(cmd[0], "export"))
	    env = ft_export(cmd, env);
	else if(!ft_strcmp(cmd[0], "unset"))
	    ft_unset(cmd, env);
	else if(!ft_strcmp(cmd[0], "exit"))
	    exit(0);
	else if (!ft_strcmp(cmd[0], "env"))
	{
		if (cmd[1])
		{
            write(2, "env with options or arguments\n", 31);
            exit (1);
        }
	    ft_env(env);
	}
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

int  del(void *content)
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
	return (-1);
}

int redirections(t_list *list)
{
	if(input_file((t_list *)(((t_ogbi *)(list->content))->input_files)))
		return(-1);
	if(output_file((t_list *)(((t_ogbi *)(list->content))->output_files)))
	    return(-1);
	return(0);
}

int command_line(t_list *list, int *fd, int fd_tmp, char **path, char **env)
{
	char *cmd_name;
	char **cmd;
	pid_t pid;

	cmd = ((t_ogbi *)(list->content))->cmd;
	pid = fork();
	if (pid == -1)
    	return (error("fork"));
    else if (pid == 0)
    {
		close(fd[0]);
		if (fd_tmp)
		    dup2(fd_tmp, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		if (redirections(list) < 0)
		    exit (1);
	    if (ft_execve(cmd, env))
			exit (0);
		cmd_name = cmd_path(cmd[0], path);
		if (cmd_name)
			execve(cmd_name, cmd, env);
		write(2, cmd[0], ft_strlen(cmd[0]));
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (0);
}

int last_command(t_list *list, int fd_tmp, char **path, char **env)
{
	char *cmd_name;
	char **cmd;
	pid_t pid;

    cmd = ((t_ogbi *)(list->content))->cmd;
	pid = fork();
	if (pid == -1)
    	return (error("fork"));
    else if (pid == 0)
    {
		if (fd_tmp)
			dup2(fd_tmp, STDIN_FILENO);
		if (redirections(list))
		    exit (1);
	    if (((t_ogbi *)(list->content))->i && ft_execve(cmd, env))
			exit (0);
		cmd_name = cmd_path(cmd[0], path);
		if (cmd_name)
			execve(cmd_name, cmd, env);
		write(2, cmd[0], ft_strlen(cmd[0]));
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return(0);
}

int is_buldin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
	    return(1);
	else if (!ft_strcmp(cmd, "pwd"))
		return(1);
	else if (!ft_strcmp(cmd, "echo"))
	    return(1);
	else if(!ft_strcmp(cmd, "export"))
	    return(1);
	else if(!ft_strcmp(cmd, "unset"))
	    return(1);
	else if(!ft_strcmp(cmd, "exit"))
	    return(1);
	else if (!ft_strcmp(cmd, "env"))
		return(1);
	return (0);
}

int last_execve(t_list *list, char **env)
{
	int fd1;
	int fd2;

	if (((t_ogbi *)(list->content))->cmd && !is_buldin(((t_ogbi *)(list->content))->cmd[0]))
		return (0);
	if (!((t_ogbi *)(list->content))->i)
	{
		fd1 = dup(STDIN_FILENO);
		if (fd1 < 0)
			return(error("dup"));
		fd2 = dup(STDOUT_FILENO);
		if (fd2 < 0)
			return(error("dup"));
		redirections(list);
		((t_ogbi *)(list->content))->i = ft_execve(((t_ogbi *)(list->content))->cmd, env);
		fd1 = dup2(fd1, STDIN_FILENO);
		if (fd1 < 0)
			return(error("dup2"));
		fd2 = dup2(fd2, STDOUT_FILENO);
		if (fd2 < 0)
			return(error("dup"));
	}
	return (0);
}

int	pipex(t_list *list, char **env)
{
	char **path;
	int status;
	int fd_tmp;
	int i;
	int fd[2];

	path = ft_split(find_str_from_env(env, "PATH"), ':');
	fd_tmp = STDIN_FILENO;
	i = 0;
	((t_ogbi *)(list->content))->i = i;
	while (list->next)
	{
		if(pipe(fd) == -1)
		{
			del(path);
			return(error("pipe() failed"));
		}
		if (command_line(list, fd, fd_tmp, path, env))
		    return (del(path));
		close(fd[1]);
		if (fd_tmp)
			close(fd_tmp);
		fd_tmp = fd[0];
		list = list->next;
		((t_ogbi *)(list->content))->i = ++i;
	}
	if (last_execve(list, env) || (!((t_ogbi *)(list->content))->i && last_command(list, fd_tmp,path, env) == -1))
		return(del(path));
	if (fd_tmp)
		close(fd_tmp);
	del(path);
	while (wait(&status) > 0);
	ft_status(&status);
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
	fd = open(line , O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		free(line);
		return (error(line));
	}
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
	if (fd == -1)
	    return (error("open"));
	dup2(fd, STDIN_FILENO);
	return(0);
}

int input_file(t_list *list)
{
	int fd;
	int index;

	index = 0;
	while(list)
	{
		if (((t_red *)list->content)->type == ENTREE)
		{
			fd = open(((t_red *)list->content)->value, O_RDONLY);
			if (fd == -1)
				return (error(((t_red *)list->content)->value));
			dup2(fd, STDIN_FILENO);
		}
		else
			fd = ft_herdoc(index++, list);
		list = list->next;
		if (list)
			close(fd);
	}
    return (0);
}

int output_file(t_list *list)
{
	int fd;

	while(list)
	{
		if (((t_red *)list->content)->type == SORTIE)
		{
			fd = open(((t_red *)list->content)->value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    		if (fd == -1)
				return (error(((t_red *)list->content)->value));
			dup2(fd, STDOUT_FILENO);
		}
		else
		{
			fd = open(((t_red *)list->content)->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
    		if (fd == -1)
				return (error(((t_red *)list->content)->value));
			dup2(fd, STDOUT_FILENO);
		}
		list = list->next;
		if (list)
			close(fd);
	}
    return (0);
}
