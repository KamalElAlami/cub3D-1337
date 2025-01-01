/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:19:10 by kael-ala          #+#    #+#             */
/*   Updated: 2024/12/31 12:44:46 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free2darray(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		if (s[i])
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (count);
}

static char	**spl_stuck(char const *s, char c, char **strs)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		j = i;
		while (s[i] && !(s[i] == c))
			i++;
		if (i > j)
		{
			strs[k] = ft_substr(s, j, i - j);
			if (!strs[k])
				return (free2darray(strs));
			k++;
		}
	}
	strs[k] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)ft_malloc(sizeof(char *) * (count_words(s, c) + 1), END);
	if (!strs)
		return (NULL);
	strs = spl_stuck(s, c, strs);
	return (strs);
}
