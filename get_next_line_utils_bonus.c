/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:00:21 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/12 15:00:32 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (0);
}

int	ft_strlenx(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoinx(char *remain, char *buffer)
{
	char	*str;
	int		s2_len;
	int		i;
	int		j;

	s2_len = ft_strlenx(buffer);
	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlenx(remain) + s2_len + 1) * sizeof(char));
	if (!str)
		return (free(remain), remain = NULL, NULL);
	while (remain[i] != '\0')
	{
		str[i] = remain[i];
		i++;
	}
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[i] = '\0';
	free(remain);
	remain = NULL;
	return (str);
}

char	*ft_strdup(char *str)
{
	char	*new_str;
	int		i;
	int		len;

	len = ft_strlenx(str);
	i = 0;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
