/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:20 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/11 16:03:52 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *path, char **cmd)
{
	char	*full_path;
	char	*cmd_name;
	int		fd;

	if (!(cmd_name = ft_strjoin("/", cmd[0])))
		return (NULL);
	if (!(full_path = ft_strjoin(path, cmd_name)))
	{
		free (cmd_name);
		return (NULL);
	}
	if ((fd = open(full_path, O_RDONLY)) != -1)
	{
		close(fd);
		free(cmd_name);
		return (full_path);
	}
	free(full_path);
	free(cmd_name);
	return (NULL);
}

char	*parse_path(char **cmd, t_list *env)
{
	t_list	*tmp;
	char	**splitted_path;
	int		i;
	char	*true_path;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if ((t_env*)tmp->content && !ft_strcmp(((t_env*)tmp->content)->name, "PATH"))
		{
			splitted_path = ft_split(((t_env*)tmp->content)->value, ':');
			i = 0;
			while (splitted_path[i])
			{
				if ((true_path = check_path(splitted_path[i++], cmd)))
				{
					ft_free_strstr(splitted_path);
					return (true_path);
				}
			}
			ft_free_strstr(splitted_path);
			break ;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int		is_it_path(char **cmd, char **true_path)
{
	int			stat_res;
	struct stat	file_stat;
	int			three_points;

	three_points = ft_strncmp("../", cmd[0], 3);
	if (!three_points || !ft_strncmp("./", cmd[0], 2) || cmd[0][0] == '/')
	{
		if (!three_points || cmd[0][0] == '/')
		{
			stat_res = stat(cmd[0], &file_stat);
			three_points = 0;
		}
		else
		{
			stat_res = stat(cmd[0], &file_stat);
			three_points = 2;
		}
		if (stat_res == -1)
			error_no_file_or_dir(cmd[0]);
		else if (S_ISDIR(file_stat.st_mode))
			error_is_a_dir(cmd[0]);
		else if (!(file_stat.st_mode & S_IXUSR))
			error_perm_denied(cmd[0]);
		*true_path = &cmd[0][three_points];
		return (1);
	}
	return (0);
}

void	run_command(char *line, char **cmd, t_list **env)
{
	int		pid;
	char	*true_path;
	int		is_path;

	errno = 0;
	is_path = 0;
	if (check_builtins(line, cmd, env))
        return ;
	else if ((is_path = is_it_path(cmd, &true_path)))
		;
	else if (!(true_path = parse_path(cmd, *env)))
	{
		error_cmd_not_found(cmd[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		my_exit(line, cmd, *env); // с каким значением?
	if (pid == 0)
	{
		if (execve(true_path, cmd, env_to_strstr(*env)) == -1)
			my_exit(line, cmd, *env); // с каким значением?
	}
	else
	{
		if (!is_path)
			free(true_path);
		// else
		// 	close(file);
		wait(NULL);
	}
}
