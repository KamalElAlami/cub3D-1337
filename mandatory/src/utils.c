/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:57:06 by sarif             #+#    #+#             */
/*   Updated: 2025/01/03 01:15:19 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup_gb(const char *s1)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	res = ft_malloc(sizeof(char) * (len + 1), END);
	if (!res)
		return (NULL);
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_gb(char const *s1, char const *s2)
{
	char	*constr;
	int		sl;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_gb(s2));
	if (!s2)
		return (ft_strdup_gb(s1));
	sl = ft_strlen(s1) + ft_strlen(s2);
	constr = ft_malloc(sizeof(char) * (sl + 1), END);
	if (!constr)
		return (NULL);
	ft_strlcpy(constr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(constr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (constr);
}
