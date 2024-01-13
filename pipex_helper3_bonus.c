/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:25:47 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/13 17:56:05 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	short_here_doc_line(t_list **info, char **argv)
{
	t_list	*tmp;

	tmp = *info;
	tmp->f = open(argv[tmp->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
}

void	short_normal_line(t_list **info, char **argv)
{
	t_list	*tmp;

	tmp = *info;
	tmp->f = open(argv[tmp->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

void	short_fun_midle(t_list **info, int *pipefd)
{
	close((*info)->lastpipe);
	close(pipefd[1]);
	(*info)->lastpipe = pipefd[0];
	(*info)->i += 1;
	free_everything((*info));
}
