/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:57:15 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/12 16:47:53 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd1(char **argv, char **paths, t_list *info, int *fd)
{
	get_info(&info, argv, paths, 1);
	info->pid = fork();
	if (info->pid == 0)
	{
		if (!info->allcmd || !info->cmd || !info->cmdpath)
			return (ft_putstr("cmd1 is not a command\n"), exit(1));
		info->f = open(argv[info->i], O_RDONLY);
		if (info->f < 0)
			return (ft_putstr("open fail to open first f\n"), exit(1));
		dup2(info->f, 0);
		close(info->f);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execve(info->cmdpath, info->allcmd, info->envp);
		ft_putstr("error in first cmd\n");
		exit(1);
	}
	free_everything(info);
	close(fd[1]);
	info->i += 2;
}

void	last_cmd1(char **argv, char **paths, t_list *info, int *fd)
{
	info->allcmd = ft_split(argv[info->i], ' ');
	info->cmd = ft_strjoin("", info->allcmd[0]);
	info->cmdpath = get_command(paths, info->cmd);
	info->pid = fork();
	if (info->pid == 0)
	{
		info->f = open(argv[info->i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (!info->allcmd || !info->cmd || !info->cmdpath)
			return (ft_putstr("cmd2 is not a command\n"), exit(1));
		if (info->f < 0)
			return (ft_putstr("open fail to open last f\n"), exit(1));
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(info->f, 1);
		close(info->f);
		execve(info->cmdpath, info->allcmd, info->envp);
		ft_putstr("error in last cmd\n");
		exit(1);
	}
	free_everything(info);
	close(fd[0]);
}

int	forking(t_list **info, int *fd)
{
	char	**paths;

	(*info)->i += 1;
	paths = ft_split((*info)->path, ':');
	first_cmd1((*info)->argv, paths, *info, fd);
	last_cmd1((*info)->argv, paths, *info, fd);
	while (wait(NULL) != -1)
		;
	free_strings(paths);
	return (0);
}

void	create_struct(t_list **info, char **strs1, char **strs2)
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
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_list	*info;

	create_struct(&info, argv, envp);
	if (!info)
		return (1);
	if (argc != 5)
		return (free(info), write(2, "wrong number of arguments\n", 27), 1);
	if (pipe(fd) < 0)
		return (free(info), perror("pipe:"), 1);
	info->path = find_path(envp);
	forking(&info, fd);
	free(info);
	return (0);
}
