/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:50:25 by mel-jira          #+#    #+#             */
/*   Updated: 2024/01/04 14:51:32 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	*ft_cpystr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strlen(s);
	if (len > size - start)
	{
		len = size - start;
		str = (char *)malloc((size - start) * sizeof(char) + 1);
	}
	else
		str = (char *)malloc(len * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str = (char *)malloc(1);
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	str = ft_cpystr(s, start, len);
	return (str);
}
