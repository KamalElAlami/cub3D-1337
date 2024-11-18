/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:38:08 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/29 05:39:14 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
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
