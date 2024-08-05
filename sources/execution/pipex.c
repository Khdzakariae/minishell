/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/08/05 02:28:05 by aogbi            ###   ########.fr       */
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
	int i;
	char *cmd_name;
	char *tmp;
	struct stat st;

	if (ft_strchr(cmd, '/'))
	{
    	if (stat(cmd, &st) == 0) 
		{
    	    if (S_ISDIR(st.st_mode)) {
    	        write(2, "Is a directory\n", 16);
    	        exit(126);
    	    }
    	}
		if (access(cmd, X_OK) == 0)
            return (cmd);
		perror(NULL);
		exit(126);
	}
	if (!path)
		return (NULL);	
	i = 0;
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

void set_pwd(t_export *env_list)
{
	char *tmp;
	char **envt;
	int i;
	int j;

	i = find_index_from_env(env_list->env, "PWD", 1);
	j = find_index_from_env(env_list->env, "OLDPWD", 1);
	tmp = getcwd(NULL, 0);
    if (tmp == NULL)
        return(perror("getcwd() error"));
	else if (j < 0)
	{
		envt = array_dup(env_list->env, 1);
		j = count_array_of_str(env_list->env);
		free(env_list->env);
		env_list->env = envt;
	}
	else
		free(env_list->env[j]);
	if (i < 0)
	{
		env_list->env[j] = ft_strjoin("OLDPWD=", tmp);
		envt = array_dup(env_list->env, 1);
		i = count_array_of_str(env_list->env);
		free(env_list->env);
		env_list->env = envt;
		env_list->env[i] = ft_strjoin("PWD=", tmp);
		free(tmp);
	}
	else
	{
		env_list->env[j] = ft_strjoin("OLD", env_list->env[i]);
		free(env_list->env[i]);
		env_list->env[i] = ft_strjoin("PWD=", tmp);
		free(tmp);
	}
}

void	ft_cd(char **cmd, t_export *env_list)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 2)
	{
		if(chdir(cmd[1]))
			perror(cmd[1]);
		else
			set_pwd(env_list);
		return ;
	}
	else if (i == 1)
	{
		if (chdir(find_str_from_env(env_list->env, "HOME")))
			write (2, "cd: HOME not set\n", 17);
	}
	else
        write(2, "cd: too many arguments\n", 24);
	g_stat = 1;
}

void    ft_pwd(char **env)
{
	char cwd[1024];
	char *tmp;

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
	{
		tmp = find_str_from_env(env, "PWD");
		if (tmp)
			printf("%s\n", tmp);
		return ;
		write(2, "PWD not found\n", 15);
		g_stat = 1;
	}
}

void    ft_echo(char **cmd)
{
	int i;
	int j;
	int n;

    i = 1;
	n = 0;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1])
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

int	find_index_from_env(char **env, char *str, int type)
{
	int i;
	int len;
	char *tmp;

	if (type == 1)
		tmp = ft_strjoin(str, "=");
	else
		tmp = ft_strdup(str);
	i = 0;
	len = ft_strlen(tmp);
	if (!env)
		return (-1);
    while (env[i])
    {
        if (ft_strncmp(env[i], tmp, len) == 0)
		{
			free(tmp);
            return (i);
		}
        i++;
    }
	free(tmp);
    return (-1);
}

void	ft_env(char **env, int is_not)
{
	int i;

    i = 0;
	if (!env)
		return ;
	if (is_not == 1)
		is_not = find_index_from_env(env, "_", 1);
	else if (is_not == 2)
		is_not = find_index_from_env(env, "_", 2);
    while (env[i])
    {
		if (is_not < 0 || is_not != i)
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

void ft_unset(char **cmd, t_export *env_list)
{
	int i;
	int index;
	char **tmp;

	i = 1;
	while(cmd[i])
	{
		index = find_index_from_env(env_list->export, cmd[i], 2);
		if(index >= 0)
		{
			tmp = array_remove(env_list->export, index);
			free(env_list->export);
			env_list->export = tmp;
		}
		else
		{
			index = find_index_from_env(env_list->env, cmd[i], 1);
			if(index >= 0)
			{
				tmp = array_remove(env_list->env, index);
				free(env_list->env);
				env_list->env = tmp;
			}
		}
		i++;
	}
}


void add_in_env(char *cmd, t_export *env_list, int j)
{
	int index;
	int len;
	char **tmp;

	cmd[j] = '\0';
	index = find_index_from_env(env_list->export, cmd,2 );
	if (index >= 0)
	{
		tmp = array_remove(env_list->export, index);
		free(env_list->export);
		env_list->export = tmp;
	}
	index = find_index_from_env(env_list->env, cmd, 1);
	cmd[j] = '=';
	if (index < 0)
	{
		len = count_array_of_str(env_list->env);
		tmp = array_dup(env_list->env, 1);
		free(env_list->env);
		env_list->env = tmp;
		env_list->env[len] = ft_strdup(cmd);
	}
	else
	{
		free(env_list->env[index]);
		env_list->env[index] = ft_strdup(cmd);
	}
}

void add_in_export(char *cmd, t_export *env_list)
{
	int len;
	char **tmp;

	len = find_index_from_env(env_list->env, cmd, 1);
	if (len < 0)
		len = find_index_from_env(env_list->export, cmd, 2);
	if (len >= 0)
		return ;
	len = count_array_of_str(env_list->export);
	tmp = array_dup(env_list->export, 1);
	free(env_list->export);
	env_list->export = tmp;
	env_list->export[len] = ft_strdup(cmd);
}

void add_in_variable(char *cmd, int j, t_export *env_list)
{
	char *tmp;
	char **array;
	int index;
	
	cmd[j] = '\0';
	index = find_index_from_env(env_list->export, cmd, 2);
	if (index < 0)
	{
		index = find_index_from_env(env_list->env, cmd, 1);
		if(index >= 0)
		{
			tmp = ft_strjoin(env_list->env[index], cmd + j + 2);
			free(env_list->env[index]);
			env_list->env[index] = tmp;
		}
	}
	else
	{
		array = array_remove(env_list->export, index);
		free(env_list->export);
		env_list->export = array;
		index = -1;
	}
	if (index < 0)
	{
		tmp = ft_strjoin(cmd, cmd + j + 1);
		array = array_dup(env_list->env, 1);
		index = count_array_of_str(env_list->env);
		free(env_list->env);
		env_list->env = array;
		env_list->env[index] = tmp;
	}
}

int find_variable(char *cmd, t_export *env_list)
{
	int j;

	j = 0;
	while(cmd[j])
	{
		if (!((!j && ft_isalpha(cmd[j])) || (j && ft_isalnum(cmd[j])) || cmd[j] == '_'))
		{
			if (j && cmd[j] == '=')
				add_in_env(cmd, env_list, j);
			else if (j && cmd[j] == '+' && !ft_strncmp(cmd + j, "+=", 2))
				add_in_variable(cmd, j, env_list);
			else
			{
				printf("export: `%s': not a valid identifier\n", cmd);
				g_stat = 1;
				return(1);
			}
			break;
		}
		j++;
		if (!cmd[j])
			add_in_export(cmd, env_list);
	}
	return (0);
}

void ft_export(char **cmd, t_export *env_list)
{
	char **tmp;
	int i;

	tmp = NULL;
	if (count_array_of_str(cmd) == 1)
	{
		ft_env(env_list->env, 1);
		ft_env(env_list->export, 2);
	}
	else
	{
		i = 1;
		while(cmd[i])
		{
			if (find_variable(cmd[i], env_list))
				break;
			i++;
		}
	}
}


int ft_execve(char **cmd, t_export *env_list)
{
	if (!cmd || !cmd[0])
	    return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
	    ft_cd(cmd, env_list);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(env_list->env);
	else if (!ft_strcmp(cmd[0], "echo"))
	    ft_echo(cmd);
	else if(!ft_strcmp(cmd[0], "export"))
	    ft_export(cmd, env_list);
	else if(!ft_strcmp(cmd[0], "unset"))
	    ft_unset(cmd, env_list);
	else if(!ft_strcmp(cmd[0], "exit"))
	    exit(0);
	else if (!ft_strcmp(cmd[0], "env"))
	{
		if (cmd[1])
            write(2, "env with options or arguments\n", 31);
		else
	    	ft_env(env_list->env, -1);
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

	if (!content)
		return -1;
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

int command_line(t_list *list, int *fd, int fd_tmp, char **path, t_export *env_list)
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
	    if (((t_ogbi *)(list->content))->i && ft_execve(cmd, env_list))
			exit (0);
		cmd_name = cmd_path(cmd[0], path);
		if (cmd_name)
			execve(cmd_name, cmd, env_list->env);
		write(2, cmd[0], ft_strlen(cmd[0]));
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (0);
}
int cmd_name_is_valid(char *cmd_name, t_export *env_list)
{
	int index;
	char *tmp;
	char **tmp1;

	if (cmd_name)
	{
		index = find_index_from_env(env_list->env, "_", 1);
		if (index > 0)
		{
			tmp = ft_strjoin("_=", cmd_name);
			free(env_list->env[index]);
			env_list->env[index] = tmp;
		}
		else
		{
			tmp1 = array_dup(env_list->env, 1);
			index = count_array_of_str(env_list->env);
			free(env_list->env);
			env_list->env = tmp1;
			env_list->env[index] = ft_strjoin("_=", cmd_name);
		}
	}
	return (1);
}

int last_command(t_list *list, int fd_tmp, char **path, t_export *env_list)
{
	char *cmd_name;
	char **cmd;
	pid_t pid;
	int status;

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
	    if (((t_ogbi *)(list->content))->i && ft_execve(cmd, env_list))
			exit (2);
		cmd_name = cmd_path(cmd[0], path);
		if (cmd_name)
			execve(cmd_name, cmd, env_list->env);
		write(2, cmd[0], ft_strlen(cmd[0]));
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	waitpid(pid, &status, 0);
	ft_status(&status);
	return(0);
}

int is_buldin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
	    return(1);
	else if (!ft_strcmp(cmd, "cd"))
	    return(1);
	else if (!ft_strcmp(cmd, "pwd"))
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

int last_execve(t_list *list, t_export *env_list)
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
		((t_ogbi *)list->content)->i += ft_execve(((t_ogbi *)(list->content))->cmd, env_list);
		fd1 = dup2(fd1, STDIN_FILENO);
		if (fd1 < 0)
			return(error("dup2"));
		fd2 = dup2(fd2, STDOUT_FILENO);
		if (fd2 < 0)
			return(error("dup"));
	}
	return (1);
}

int ft_herdoc_2(int index, t_list *list, char **env)
{
	char *line;
	char *tmp;
	char *tmp1;
	int fd;

	tmp = ft_strdup("/tmp/.Her_Doc_");
	line = ft_strjoin(tmp, ft_itoa(index));
	free(tmp);
	tmp1 = line;
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
		tmp = expand(line, env);
		if (tmp)
		{
			free(line);
			line = tmp;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	((t_red *)list->content)->value = tmp1;
	return(0);
}

int ft_herdoc(t_list *list, char **env)
{
	t_list *tmp;
	int index;

	index = 0;
	while(list)
	{
		tmp = ((t_ogbi *)(list->content))->input_files;
		while(tmp)
		{
			if (((t_red *)tmp->content)->type == HEREDOC)
				if (ft_herdoc_2(index++, tmp, env))
					return (-1);
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (0);
}

int quotes_in_list(t_list *list, char **env)
{
	while(list)
	{
		if (cmd_quote_handler((t_ogbi *)(list->content), env))
		{
			g_stat = 2;
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	pipex(t_list *list, t_export *env_list)
{
	char **path;
	int fd_tmp;
	int i;
	int fd[2];

	ft_herdoc(list, env_list->env);
	if (quotes_in_list(list, env_list->env))
		return 2;
	path = ft_split(find_str_from_env((char **)(env_list->env), "PATH"), ':');
	fd_tmp = STDIN_FILENO;
	i = 0;
	((t_ogbi *)(list->content))->i = i;
	while (list->next)
	{
		if(pipe(fd) == -1)
			return(del(path), error("pipe() failed"));
		if (command_line(list, fd, fd_tmp, path, env_list))
		    return (del(path));
		close(fd[1]);
		if (fd_tmp)
			close(fd_tmp);
		fd_tmp = fd[0];
		list = list->next;
		((t_ogbi *)(list->content))->i = ++i;
	}
	if (!((t_ogbi *)(list->content))->i && last_execve(list, env_list))
		return (del(path));
	else if (last_command(list, fd_tmp,path, env_list) == -1)
		return(del(path));
	cmd_name_is_valid(((t_ogbi *)(list->content))->cmd[0], env_list);
	if (fd_tmp)
		close(fd_tmp);
	del(path);
	while (wait(NULL) > 0);
	return (0);
}


int input_file(t_list *list)
{
	int fd;
	int index;

	index = 0;
	while(list)
	{
		fd = open(((t_red *)list->content)->value, O_RDONLY);
		if (fd == -1)
			return (error(((t_red *)list->content)->value));
		dup2(fd, STDIN_FILENO);
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
