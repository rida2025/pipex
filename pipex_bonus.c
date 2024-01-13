/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:44:12 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/13 17:47:30 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc_read(t_list *info)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	if (pipe(fd) < 0)
		return (write(2, "pipe failed\n", 13), -1);
	tmp = ft_strjoin(info->argv[2], "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strcmp(line, tmp) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	free(tmp);
	close(fd[1]);
	info->lastpipe = fd[0];
	return (fd[0]);
}

void	here_doc_cmd(char **argv, char **paths, int *fd, t_list *info)
{
	info->i += 1;
	get_info(&info, argv, paths, 1);
	info->f = here_doc_read(info);
	info->pid = fork();
	if (info->pid == 0)
	{
		if (info->f < 0)
			return (write(2, "open failed\n", 13), exit(1));
		if (!info->allcmd || !info->cmd || !info->cmdpath)
			return (ft_putstr("error in cmd1\n"), exit(1));
		dup2(info->f, 0);
		close(info->f);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execve(info->cmdpath, info->allcmd, info->envp);
		write(2, "error in cmd1\n", 15);
		exit(1);
	}
	waitpid(info->pid, NULL, 0);
	clean_and_save(&info, fd);
}

int	forking(t_list **info, int *fd, int argc)
{
	char	**paths;

	(*info)->i += 1;
	paths = ft_split((*info)->path, ':');
	if ((*info)->here_doc == 1)
		here_doc_cmd((*info)->argv, paths, fd, *info);
	if ((*info)->here_doc == 0)
		first_cmd((*info)->argv, paths, fd, *info);
	while (argc > 5 && (*info)->i < argc - 2)
		midle_cmd((*info)->argv, paths, *info);
	last_cmd((*info)->argv, paths, *info);
	while (wait(NULL) != -1)
		;
	free_strings(paths);
	return (0);
}

void	create_struct(t_list **info, char **strs1, char **strs2, int value)
{
	*info = malloc(sizeof(t_list));
	if (!*info)
		return ;
	(*info)->here_doc = 0;
	(*info)->i = 0;
	(*info)->path = NULL;
	(*info)->f = 0;
	(*info)->pid = 0;
	(*info)->cmd = NULL;
	(*info)->allcmd = NULL;
	(*info)->cmdpath = NULL;
	(*info)->argv = strs1;
	(*info)->envp = strs2;
	(*info)->argc = value;
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_list	*info;

	create_struct(&info, argv, envp, argc);
	if (!info)
		return (1);
	if (argc < 5)
		return (free(info), write(2, "wrong number of arguments\n", 27), 0);
	check_heredoc(info);
	if (pipe(fd) < 0)
		return (free(info), perror("pipe:"), 1);
	info->path = find_path(envp);
	forking(&info, fd, argc);
	free(info);
	return (0);
}
