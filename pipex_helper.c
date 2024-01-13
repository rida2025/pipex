/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:12:36 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/12 15:14:07 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		if (ft_strncmp(strs[i], "PATH=", 5) == 0)
			return (strs[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_command(char **paths, char *command)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = NULL;
	tmp2 = NULL;
	i = -1;
	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	while (paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp2 = ft_strjoin(tmp, command);
		free(tmp);
		if (tmp2 && access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
	}
	return (NULL);
}

void	get_info(t_list **info, char **argv, char **paths, int x)
{
	(*info)->allcmd = ft_split(argv[(*info)->i + x], ' ');
	(*info)->cmd = ft_strjoin("", (*info)->allcmd[0]);
	(*info)->cmdpath = get_command(paths, (*info)->cmd);
}

void	clean_and_save(t_list **info, int*fd)
{
	(*info)->lastpipe = fd[0];
	close((*info)->f);
	close(fd[1]);
	(*info)->i += 2;
	unlink((*info)->argv[1]);
	free_everything(*info);
}
