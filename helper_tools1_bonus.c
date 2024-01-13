/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tools1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:49:45 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/12 15:00:37 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_strings(char **strs)
{
	int	i;

	i = -1;
	while (strs && strs[++i])
		free(strs[i]);
	free(strs);
}

void	free_everything(t_list *info)
{
	if (info->cmd)
		free(info->cmd);
	if (info->allcmd)
		free_strings(info->allcmd);
	if (info->cmdpath)
		free(info->cmdpath);
	info->f = 0;
}
