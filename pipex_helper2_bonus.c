/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:54 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/13 17:51:37 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(char **argv, char **paths, int *fd, t_list *info)
{
	get_info(&info, argv, paths, 1);
	info->f = open(argv[info->i], O_RDONLY);
	if (info->f < 0)
		ft_putstr("open failed to open first file\n");
	info->pid = fork();
	if (info->pid == 0)
	{
		if (!info->allcmd || !info->cmd || !info->cmdpath)
			return (ft_putstr("start no such cmd\n"), exit(1));
		if (dup2(info->f, 0) < 0)
			exit(1);
		close(info->f);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execve(info->cmdpath, info->allcmd, info->envp);
		perror("pipex_bonus");
		exit(1);
	}
	info->lastpipe = fd[0];
	close(info->f);
	close(fd[1]);
	info->i += 2;
	free_everything(info);
}

void	midle_cmd(char **argv, char **paths, t_list *info)
{
	int		pipefd[2];

	get_info(&info, argv, paths, 0);
	if (pipe(pipefd) < 0)
		return (perror("pipe:"));
	info->pid = fork();
	if (info->pid == -1)
		return (perror("fork failed:"), exit(11));
	if (info->pid == 0)
	{
		if (!info->allcmd || !info->cmd || !info->cmdpath)
			return (ft_putstr("midle no such cmd\n"), exit(1));
		dup2(info->lastpipe, pipefd[0]);
		close(info->lastpipe);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve(info->cmdpath, info->allcmd, info->envp);
		perror("pipex_bonus");
		exit(1);
	}
	short_fun_midle(&info, pipefd);
}

void	check_heredoc(t_list *info)
{
	if (ft_strcmp(info->argv[1], "here_doc") == 0)
		info->here_doc = 1;
}

void	last_cmd(char **argv, char **paths, t_list *info)
{
	info->allcmd = ft_split(argv[info->argc - 2], ' ');
	info->cmd = ft_strjoin("", info->allcmd[0]);
	info->cmdpath = get_command(paths, info->cmd);
	info->pid = fork();
	if (info->pid == 0)
	{
		if (info->here_doc == 1)
			short_here_doc_line(&info, argv);
		if (info->here_doc == 0)
			short_normal_line(&info, argv);
		if (!info->allcmd || !info->cmd || !info->cmdpath)
			return (ft_putstr("last no such cmd\n"), exit(1));
		if (info->f < 0)
			return (ft_putstr("open fail to open last f\n"), exit(1));
		dup2(info->lastpipe, 0);
		close(info->lastpipe);
		dup2(info->f, 1);
		close(info->f);
		execve(info->cmdpath, info->allcmd, info->envp);
		perror("pipex_bonus");
		exit(1);
	}
	close(info->lastpipe);
	free_everything(info);
}
