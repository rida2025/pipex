/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_replace_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:34:54 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/13 20:16:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_setstring(char *str, char *info)
{
	free(str);
	str = (info + ft_strlen(str + 1) + 1);
	if (!str)
		exit(1);
	str = ft_strjoin(str, "\n");
	return (str);
}

char	*check_and_replace(t_list *info, char *str)
{
	int		i;

	i = -1;
	if (str[0] == '$')
	{
		while (info->envp && info->envp[++i])
		{
			if (ft_strncmp((str + 1), info->envp[i], (ft_strlen(str) - 2)) == 0)
				str = ft_setstring(str, info->envp[i]);
		}
	}
	return (str);
}
